using System;
using System.Net.Sockets;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Navigation;

namespace BattleshipClient {

    public enum GameState { Default, InProgress, Completed, Cancelled }

    /// <summary>
    /// Interaction logic for GamePage.xaml
    /// </summary>
    public partial class GamePage : PageFunction<GameState> {

        private readonly GameClient client;

        public GamePage(GameClient client) {
            InitializeComponent();
            this.client = client;
            PlayerBoard.Content = new Board(10, 10).GetGrid();
            OpponentBard.Content = new Board(10, 10).GetGrid();
        }

        private void LeaveButton_Click(object sender, RoutedEventArgs e) {
            OnReturn(new ReturnEventArgs<GameState>(GameState.Completed));
        }
    }
}
