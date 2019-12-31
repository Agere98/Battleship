using System;
using System.Net.Sockets;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Navigation;

namespace BattleshipClient {

    public enum GameState { Default, InProgress, Completed, Cancelled }

    /// <summary>
    /// Interaction logic for GamePage.xaml
    /// </summary>
    public partial class GamePage : PageFunction<GameState> {

        public GamePage() {
            InitializeComponent();
        }

        private void BackButton_Click(object sender, RoutedEventArgs e) {
            OnReturn(new ReturnEventArgs<GameState>(GameState.Completed));
        }
    }
}
