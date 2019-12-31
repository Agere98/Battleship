using System.Windows;

namespace BattleshipClient {

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window {

        private readonly GameClient client;

        public MainWindow() {
            InitializeComponent();
            client = new GameClient();
            client.AddMessageListener(ParseServerMessage);
            PageFrame.Navigate(new MenuPage(client));
        }

        private void ParseServerMessage(string message) {
            if (message == "start") {
                PageFrame.Navigate(new GamePage(client));
            }
        }
    }
}
