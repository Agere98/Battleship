using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace BattleshipClient {

    /// <summary>
    /// A board that allows to select individual tiles
    /// </summary>
    public class OpponentBoard : Board {

        /// <summary>
        /// Occurs when a tile was clicked
        /// </summary>
        public event EventHandler<TileSelectedEventArgs> TileSelected;

        /// <summary>
        /// Creates an opponent board
        /// </summary>
        /// <param name="height">Number of rows</param>
        /// <param name="width">Number of columns</param>
        public OpponentBoard(int height, int width)
            : base(height, width) {
            RegisterCallbacks();
        }

        public override void SetTile(int row, int column, Tile content) {
            base.SetTile(row, column, content);
            var image = new Image();
            object source = null;
            switch (content) {
                case Tile.Empty:
                    source = resources["Tile_Empty"];
                    break;
                case Tile.Hit:
                    source = resources["Tile_Hit"];
                    break;
                case Tile.Miss:
                    source = resources["Tile_Miss"];
                    break;
                default:
                    break;
            }
            image.Source = source as ImageSource;
            board[row, column].button.Content = image;
        }

        private void RegisterCallbacks() {
            for (int i = 0; i < Height; i++) {
                for (int j = 0; j < Width; j++) {
                    Button button = board[i, j].button;
                    button.Click += new RoutedEventHandler(Tile_Click);
                }
            }
        }

        private void Tile_Click(object sender, RoutedEventArgs e) {
            if (!IsActive || !(sender is Button button)) return;
            int row = Grid.GetRow(button);
            int column = Grid.GetColumn(button);
            TileSelected(this, new TileSelectedEventArgs { Row = row, Column = column });
        }

        public class TileSelectedEventArgs : EventArgs {
            public int Row { get; set; }
            public int Column { get; set; }
        }
    }
}
