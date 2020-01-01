using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace BattleshipClient {

    public class Board {

        public int Height { get; private set; }
        public int Width { get; private set; }

        private Resources resources;

        public Board(int height, int width) {
            Height = height;
            Width = width;
            resources = new Resources();
            resources.InitializeComponent();
        }

        public Grid GetGrid() {
            var background = resources["BoardBackground"] as SolidColorBrush;
            var tile_empty = resources["Tile_Empty"] as ImageSource;

            Grid grid = new Grid {
                Background = background,
                ShowGridLines = true
            };
            for (int i = 0; i < Height; i++) {
                var row = new RowDefinition();
                grid.RowDefinitions.Add(row);
            }
            for (int j = 0; j < Width; j++) {
                var column = new ColumnDefinition();
                grid.ColumnDefinitions.Add(column);
            }
            for (int i = 0; i < Height; i++) {
                for (int j = 0; j < Width; j++) {
                    Image image = new Image();
                    image.Source = tile_empty;
                    Grid.SetRow(image, i);
                    Grid.SetColumn(image, j);
                    grid.Children.Add(image);
                }
            }
            return grid;
        }
    }
}
