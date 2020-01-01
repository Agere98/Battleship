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
            client.MessageReceived += Client_MessageReceived;
            PageFrame.Navigate(new MenuPage(client));
        }

        private void Client_MessageReceived(object sender, GameClient.MessageReceivedEventArgs e) {
            ParseServerMessage(e.Message);
        }

        private void ParseServerMessage(string message) {
            if (message == "start") {
                PageFrame.Navigate(new GamePage(client));
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e) {
            client.MessageReceived -= Client_MessageReceived;
        }
    }
}
