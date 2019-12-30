using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace BattleshipClient {

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window {

        private async Task DelayAsync() {
            await Task.Delay(3000);
        }

        public enum MenuState { Default, Connecting, Connected, Matchmaking }

        private MenuState state;
        private string hostname;

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
                        SetCancelButton("Cancel");
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
            State = MenuState.Connecting;
            // Temporary dummy code
            await DelayAsync();
            if (hostname != "qqq") {
                State = MenuState.Default;
                StatusLabel.Content = $"Could not connect to {hostname}";
            }
            else {
                State = MenuState.Connected;
            }
        }

        private async void Disconnect() {
            State = MenuState.Default;
            // Temporary dummy code
            await DelayAsync();
        }

        private async void Play() {
            State = MenuState.Matchmaking;
            // Temporary dummy code
            await DelayAsync();
        }

        private async void Leave() {
            State = MenuState.Connected;
            // Temporary dummy code
            await DelayAsync();
        }

        private async void PlayButton_Click(object sender, RoutedEventArgs e) {
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
