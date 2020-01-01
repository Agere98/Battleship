using System;
using System.Globalization;
using System.Windows.Data;

namespace BattleshipClient {

    /// <summary>
    /// Helper class to set aspect ratio of the grid containing game boards
    /// </summary>
    internal class BoardGridSizeConverter : IValueConverter {

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture) {
            var width = (double)value;
            return width / 2.2;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture) {
            return null;
        }
    }
}
