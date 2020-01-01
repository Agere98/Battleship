using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace BattleshipClient {

    /// <summary>
    /// A board that allows ships to be placed on it
    /// </summary>
    public class PlayerBoard : Board {

        private readonly IList<int> shipSizes;
        private readonly IList<Ship> ships;
        private Ship nextShip;

        /// <summary>
        /// Occurs when all the ships are placed on board
        /// </summary>
        public event EventHandler<ShipsPlacedEventArgs> ShipsPlaced;

        /// <summary>
        /// Creates a player board
        /// </summary>
        /// <param name="height">Number of rows</param>
        /// <param name="width">Number of columns</param>
        /// <param name="shipSizes">Sizes of ships to be placed on this board</param>
        public PlayerBoard(int height, int width, IList<int> shipSizes = null)
            : base(height, width) {
            this.shipSizes = shipSizes ?? new List<int>();
            ships = new List<Ship>();
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
                    source = resources["Tile_ShipHit"];
                    break;
                case Tile.Miss:
                    source = resources["Tile_Miss"];
                    break;
                case Tile.Ship:
                    source = resources["Tile_Ship"];
                    break;
                default:
                    break;
            }
            image.Source = source as ImageSource;
            board[row, column].button.Content = image;
        }

        protected override void Activate() {
            if (ships.Count == shipSizes.Count)
                return;
            nextShip.Size = shipSizes[ships.Count];
        }

        private void PlaceShip(Ship ship) {
            if (!IsValid(ship)) return;
            RemoveHighlight(ship);
            if (ship.Orientation == Ship.ShipOrientation.Horizontal) {
                int end = ship.Column + ship.Size;
                for (int j = ship.Column; j < end && j < Width; j++) {
                    SetTile(ship.Row, j, Tile.Ship);
                    board[ship.Row, j].button.IsEnabled = false;
                }
            }
            if (ship.Orientation == Ship.ShipOrientation.Vertical) {
                int end = ship.Row + ship.Size;
                for (int i = ship.Row; i < end && i < Height; i++) {
                    SetTile(i, ship.Column, Tile.Ship);
                    board[i, ship.Column].button.IsEnabled = false;
                }
            }
            ships.Add(ship);
            if (ships.Count == shipSizes.Count) {
                IsActive = false;
                ShipsPlaced(this, new ShipsPlacedEventArgs { Ships = ships });
            }
            else {
                IsActive = true;
            }
        }

        private bool IsValid(Ship ship) {
            if ((ship.Orientation == Ship.ShipOrientation.Horizontal && ship.Column + ship.Size > Width)
                || (ship.Orientation == Ship.ShipOrientation.Vertical && ship.Row + ship.Size > Height)) {
                return false;
            }
            foreach (var other in ships) {
                if (Ship.Overlap(ship, other)) return false;
            }
            return true;
        }

        private void AddHighlight(Ship ship) {
            SolidColorBrush highlightBrush;
            if (IsValid(ship)) {
                highlightBrush = resources["TileHighlight"] as SolidColorBrush;
            }
            else {
                highlightBrush = resources["TileErrorHighlight"] as SolidColorBrush;
            }
            SetBackground(ship, highlightBrush);
        }

        private void RemoveHighlight(Ship ship) {
            var tileBrush = resources["TileBackground"] as SolidColorBrush;
            SetBackground(ship, tileBrush);
        }

        private void SetBackground(Ship ship, Brush background) {
            if (ship.Orientation == Ship.ShipOrientation.Horizontal) {
                int end = ship.Column + ship.Size;
                for (int j = ship.Column; j < end && j < Width; j++) {
                    board[ship.Row, j].button.Background = background;
                }
            }
            if (ship.Orientation == Ship.ShipOrientation.Vertical) {
                int end = ship.Row + ship.Size;
                for (int i = ship.Row; i < end && i < Height; i++) {
                    board[i, ship.Column].button.Background = background;
                }
            }
        }

        private void RegisterCallbacks() {
            for (int i = 0; i < Height; i++) {
                for (int j = 0; j < Width; j++) {
                    Button button = board[i, j].button;
                    button.Click += new RoutedEventHandler(Tile_Click);
                    button.MouseRightButtonDown += new MouseButtonEventHandler(Tile_MouseRightButtonDown);
                    button.MouseEnter += new MouseEventHandler(Tile_MouseEnter);
                    button.MouseLeave += new MouseEventHandler(Tile_MouseLeave);
                }
            }
        }

        private void Tile_Click(object sender, RoutedEventArgs e) {
            if (IsActive) {
                PlaceShip(nextShip);
            }
        }

        private void Tile_MouseRightButtonDown(object sender, MouseEventArgs e) {
            RemoveHighlight(nextShip);
            if (nextShip.Orientation == Ship.ShipOrientation.Horizontal) {
                nextShip.Orientation = Ship.ShipOrientation.Vertical;
            }
            else if (nextShip.Orientation == Ship.ShipOrientation.Vertical) {
                nextShip.Orientation = Ship.ShipOrientation.Horizontal;
            }
            AddHighlight(nextShip);
        }

        private void Tile_MouseEnter(object sender, MouseEventArgs e) {
            if (!IsActive) return;
            if (!(sender is Button button)) return;
            nextShip.Row = Grid.GetRow(button);
            nextShip.Column = Grid.GetColumn(button);
            AddHighlight(nextShip);
        }

        private void Tile_MouseLeave(object sender, MouseEventArgs e) {
            if (!IsActive) return;
            RemoveHighlight(nextShip);
        }

        public class ShipsPlacedEventArgs : EventArgs {
            public IList<Ship> Ships { get; set; }
        }
    }
}
