using System;
using System.Net.Sockets;
using System.Windows;
using System.Windows.Input;

namespace BattleshipClient {

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window {

        public enum MenuState { Default, Connecting, Connected, Matchmaking }

        private MenuState state;
        private string hostname;
        private readonly GameClient client;

        public MenuState State {
            get => state;
            private set {
                state = value;
                switch (state) {
                    case MenuState.Default:
                        PlayButton.Content = "CONNECT";
                        StatusLabel.Content = "Not connected";
                        SetCancelButton(null);
                        break;
                    case MenuState.Connecting:
                        StatusLabel.Content = $"Connecting to {hostname}...";
                        break;
                    case MenuState.Connected:
                        PlayButton.Content = "PLAY";
                        StatusLabel.Content = $"Connected to {hostname}";
                        SetCancelButton("Disconnect");
                        break;
                    case MenuState.Matchmaking:
                        StatusLabel.Content = "Searching for an opponent...";
                        SetCancelButton("Cancel");
                        break;
                    default:
                        break;
                }
            }
        }

        public MainWindow() {
            InitializeComponent();
            State = MenuState.Default;
            client = new GameClient();
        }

        private void SetConnectPanel(bool active) {
            if (active) {
                ConnectPanel.Visibility = Visibility.Visible;
            }
            else {
                if (!ServerAddressBox.IsFocused) {
                    ConnectPanel.Visibility = Visibility.Collapsed;
                }
            }
        }

        private void SetCancelButton(object content) {
            if (content == null) {
                CancelButton.IsEnabled = false;
                CancelButton.Visibility = Visibility.Collapsed;
            }
            else {
                CancelButton.Content = content;
                CancelButton.Visibility = Visibility.Visible;
                CancelButton.IsEnabled = true;
            }
        }

        private async void Connect() {
            hostname = ServerAddressBox.Text;
            if (hostname.Trim() == "") {
                StatusLabel.Content = "Invalid hostname";
                return;
            }
            State = MenuState.Connecting;
            try {
                await client.ConnectAsync(hostname);
                State = MenuState.Connected;
            }
            catch (ArgumentException) {
                State = MenuState.Default;
                StatusLabel.Content = "Invalid hostname";
            }
            catch (SocketException) {
                State = MenuState.Default;
                StatusLabel.Content = $"Could not connect to {hostname}";
            }
        }

        private async void Disconnect() {
            State = MenuState.Default;
            await client.DisconnectAsync();
        }

        private async void Play() {
            State = MenuState.Matchmaking;
            await client.WriteAsync("match");
        }

        private async void Leave() {
            State = MenuState.Connected;
            await client.WriteAsync("leave");
        }

        private void PlayButton_Click(object sender, RoutedEventArgs e) {
            SetConnectPanel(false);
            if (State == MenuState.Default) {
                Connect();
            }
            else if (State == MenuState.Connected) {
                Play();
            }
        }

        private void PlayButton_MouseEnter(object sender, MouseEventArgs e) {
            if (State == MenuState.Default) {
                SetConnectPanel(true);
            }
        }

        private void PlayButton_MouseLeave(object sender, MouseEventArgs e) {
            SetConnectPanel(false);
        }

        private void ConnectPanel_MouseEnter(object sender, MouseEventArgs e) {
            SetConnectPanel(true);
        }

        private void ConnectPanel_MouseLeave(object sender, MouseEventArgs e) {
            SetConnectPanel(false);
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e) {
            if (State == MenuState.Connected) {
                Disconnect();
            }
            else if (State == MenuState.Matchmaking) {
                Leave();
            }
        }

        private void ExitButton_Click(object sender, RoutedEventArgs e) {
            Close();
        }
    }
}
