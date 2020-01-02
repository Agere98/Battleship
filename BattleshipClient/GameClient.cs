using System;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Linq;

namespace BattleshipClient {

    /// <summary>
    /// Client-side communication logic
    /// </summary>
    public class GameClient {

        const int serverPort = 2680;

        private Socket client;
        private NetworkStream networkStream;
        private StreamReader reader;
        private StreamWriter writer;

        /// <summary>
        /// Occurs when ListenAsync is running and a message is received from remote host
        /// </summary>
        public event EventHandler<MessageReceivedEventArgs> MessageReceived;

        /// <summary>
        /// Gets a value that indicates whether a client is connected to a remote host
        /// </summary>
        public bool Connected {
            get => client.Connected;
        }

        /// <summary>
        /// Resolves a hostname and establishes a connection to a remote host
        /// </summary>
        /// <param name="hostname">The host name or IP address to connect to</param>
        /// <returns></returns>
        public async Task ConnectAsync(string hostname) {
            var host = await Task.Run(() => {
                return Dns.GetHostEntry(hostname);
            });
            var endPoint = new IPEndPoint(
                host.AddressList.FirstOrDefault(a => a.AddressFamily == AddressFamily.InterNetwork),
                serverPort);
            client = new Socket(SocketType.Stream, ProtocolType.Tcp);
            await client.ConnectAsync(endPoint);
            networkStream = new NetworkStream(client);
            reader = new StreamReader(networkStream);
            writer = new StreamWriter(networkStream) {
                AutoFlush = true,
                NewLine = "\n"
            };
        }

        /// <summary>
        /// Closes the client connection
        /// </summary>
        public void Disconnect() {
            if (client.Connected) {
                reader.Close();
                writer.Close();
                networkStream.Close();
                client.Shutdown(SocketShutdown.Both);
                client.Close();
            }
        }

        /// <summary>
        /// Reads a line from client socket
        /// </summary>
        /// <returns>A string containing a single line received from a remote host</returns>
        public Task<string> ReadAsync() {
            return reader.ReadLineAsync();
        }

        /// <summary>
        /// Writes a string to client socket, followed by a line delimeter
        /// </summary>
        /// <param name="message">A message string to send</param>
        /// <returns></returns>
        public Task WriteAsync(string message) {
            return writer.WriteLineAsync(message);
        }

        /// <summary>
        /// Asynchronously reads incoming messages and notifies MessageReceived event subscribers
        /// when a message is received
        /// </summary>
        /// <returns></returns>
        public async Task ListenAsync() {
            while (client.Connected) {
                string message = await ReadAsync();
                MessageReceived(this, new MessageReceivedEventArgs { Message = message });
                if (message == null) {
                    break;
                }
            }
        }

        public class MessageReceivedEventArgs : EventArgs {
            /// <summary>
            /// Message string or null if connection has been closed
            /// </summary>
            public string Message { get; set; }
        }
    }
}
