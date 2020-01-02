using System;
using System.Net.Sockets;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace BattleshipClient {

    /// <summary>
    /// Interaction logic for MenuPage.xaml
    /// </summary>
    public partial class MenuPage : Page {

        public enum MenuState { Default, Connecting, Connected, Matchmaking }

        private MenuState state;
        private bool showConnectPanel = false;
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
                        ConnectPanel.Visibility = Visibility.Collapsed;
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

        public MenuPage(GameClient client) {
            InitializeComponent();
            State = MenuState.Default;
            this.client = client;
        }

        private void Page_Loaded(object sender, RoutedEventArgs e) {
            if (State != MenuState.Default) {
                State = MenuState.Connected;
            }
        }

        private void SetConnectPanel() {
            if (showConnectPanel) {
                ConnectPanel.Visibility = Visibility.Visible;
            }
            else {
                if (!ServerAddressBox.IsKeyboardFocusWithin) {
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
                await client.ListenAsync();
            }
            catch (ArgumentException) {
                State = MenuState.Default;
                StatusLabel.Content = "Invalid hostname";
            }
            catch (SocketException) {
                State = MenuState.Default;
                StatusLabel.Content = $"Could not connect to {hostname}";
            }
            catch (ObjectDisposedException) {
                State = MenuState.Default;
            }
            catch (System.IO.IOException) {
                State = MenuState.Default;
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
            if (State == MenuState.Default) {
                Connect();
            }
            else if (State == MenuState.Connected) {
                Play();
            }
        }

        private void PlayButton_MouseEnter(object sender, MouseEventArgs e) {
            if (State == MenuState.Default) {
                showConnectPanel = true;
                SetConnectPanel();
            }
        }

        private void PlayButton_MouseLeave(object sender, MouseEventArgs e) {
            showConnectPanel = false;
            SetConnectPanel();
        }

        private void ConnectPanel_MouseEnter(object sender, MouseEventArgs e) {
            showConnectPanel = true;
            SetConnectPanel();
        }

        private void ConnectPanel_MouseLeave(object sender, MouseEventArgs e) {
            showConnectPanel = false;
            SetConnectPanel();
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e) {
            if (State == MenuState.Connected) {
                Disconnect();
            }
            else if (State == MenuState.Matchmaking) {
                Leave();
            }
        }

        private void ServerAddressBox_KeyDown(object sender, KeyEventArgs e) {
            if (e.Key == Key.Return) {
                Keyboard.ClearFocus();
                SetConnectPanel();
                Connect();
            }
            if (e.Key == Key.Escape) {
                Keyboard.ClearFocus();
                SetConnectPanel();
            }
        }

        private void ExitButton_Click(object sender, RoutedEventArgs e) {
            if (state == MenuState.Connected) {
                Disconnect();
            }
            Window.GetWindow(this)?.Close();
        }
    }
}
