using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Navigation;

namespace BattleshipClient {

    public enum GameState { Default, InProgress, Completed, Cancelled }

    /// <summary>
    /// Interaction logic for GamePage.xaml
    /// </summary>
    public partial class GamePage : PageFunction<GameState> {

        private readonly GameClient client;
        private readonly PlayerBoard playerBoard;
        private readonly OpponentBoard opponentBoard;
        private GameState state;
        private (int Row, int Column) selectedTile;

        public GamePage(GameClient client) {
            InitializeComponent();
            this.client = client;
            client.MessageReceived += Client_MessageReceived;
            playerBoard = new PlayerBoard(10, 10, new List<int> { 5, 4, 3, 3, 2 });
            playerBoard.ShipsPlaced += PlayerBoard_ShipsPlaced;
            playerBoard.IsActive = true;
            PlayerBoard.Content = playerBoard.GetGrid();
            opponentBoard = new OpponentBoard(10, 10);
            opponentBoard.TileSelected += OpponentBoard_TileSelected;
            OpponentBard.Content = opponentBoard.GetGrid();
            state = GameState.InProgress;
        }

        private void Client_MessageReceived(object sender, GameClient.MessageReceivedEventArgs e) {
            ParseServerMessage(e.Message);
        }

        private async void OpponentBoard_TileSelected(object sender, OpponentBoard.TileSelectedEventArgs e) {
            selectedTile = (e.Row, e.Column);
            GameStatusLabel.Content = "Waiting for opponent";
            opponentBoard.IsActive = false;
            await client.WriteAsync($"fire {e.Column} {e.Row}");
        }

        private async void PlayerBoard_ShipsPlaced(object sender, PlayerBoard.ShipsPlacedEventArgs e) {
            GameStatusLabel.Content = "Waiting for opponent";
            HintLabel.Content = "";
            var ships = e.Ships;
            StringBuilder command = new StringBuilder("ships ");
            foreach (var ship in ships) {
                command.Append(ship.Column).Append(" ");
                command.Append(ship.Row).Append(" ");
                var orientation = (ship.Orientation == Ship.ShipOrientation.Horizontal) ? "h" : "v";
                command.Append(orientation).Append(" ");
            }
            if (client.Connected) {
                await client.WriteAsync(command.ToString());
            }
        }

        private void LeaveButton_Click(object sender, RoutedEventArgs e) {
            if (client.Connected) {
                client.WriteAsync("leave");
            }
            Close();
            if (state == GameState.InProgress) {
                state = GameState.Cancelled;
            }
            OnReturn(new ReturnEventArgs<GameState>(state));
        }

        private void ParseServerMessage(string message) {
            if (message == null) {
                ErrorPanel.Visibility = Visibility.Visible;
                ErrorLabel.Content = "Connection lost";
                return;
            }
            if (message == "turn") {
                GameStatusLabel.Content = "Your turn";
                opponentBoard.IsActive = true;
            }
            if (message == "miss") {
                opponentBoard.SetTile(selectedTile.Row, selectedTile.Column, Board.Tile.Miss);
            }
            if (message == "hit") {
                opponentBoard.SetTile(selectedTile.Row, selectedTile.Column, Board.Tile.Hit);
            }
            if (message == "sunk") {
                opponentBoard.SetTile(selectedTile.Row, selectedTile.Column, Board.Tile.Hit);
            }
            if (message == "win") {
                GameStatusLabel.Content = "Victory!";
                state = GameState.Completed;
            }
            if (message == "lose") {
                GameStatusLabel.Content = "Defeat";
                state = GameState.Completed;
            }
            if (message == "draw") {
                GameStatusLabel.Content = "Draw";
                state = GameState.Completed;
            }
            if (message == "opponent left") {
                GameStatusLabel.Content = "Opponent left";
                playerBoard.IsActive = false;
                opponentBoard.IsActive = false;
                state = GameState.Cancelled;
            }
            if (message.StartsWith("fire ")) {
                var command = message.Split(' ');
                if (command.Length < 3) return;
                if (!int.TryParse(command[1], out int column)) return;
                if (!int.TryParse(command[2], out int row)) return;
                EnemyFire(row, column);
            }
            if (message == "Invalid command") {
                ErrorPanel.Visibility = Visibility.Visible;
            }
        }

        private void EnemyFire(int row, int column) {
            var tile = playerBoard.GetTile(row, column);
            if (tile == Board.Tile.Empty) {
                playerBoard.SetTile(row, column, Board.Tile.Miss);
            }
            if (tile == Board.Tile.Ship) {
                playerBoard.SetTile(row, column, Board.Tile.Hit);
            }
        }

        private void Close() {
            playerBoard.ShipsPlaced -= PlayerBoard_ShipsPlaced;
            opponentBoard.TileSelected -= OpponentBoard_TileSelected;
            client.MessageReceived -= Client_MessageReceived;
        }
    }
}
