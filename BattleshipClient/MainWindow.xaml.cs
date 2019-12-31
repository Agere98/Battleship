using System.Windows;

namespace BattleshipClient {

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window {

        public MainWindow() {
            InitializeComponent();
            PageFrame.Navigate(new MenuPage(new GameClient()));
        }
    }
}
