using System;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Collections.Generic;

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
        private IList<Action<string>> messageListeners;

        public GameClient() {
            messageListeners = new List<Action<string>>();
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
            var endPoint = new IPEndPoint(host.AddressList[0], serverPort);
            client = new Socket(SocketType.Stream, ProtocolType.Tcp);
            await client.ConnectAsync(endPoint);
            networkStream = new NetworkStream(client);
            reader = new StreamReader(networkStream);
            writer = new StreamWriter(networkStream);
            writer.AutoFlush = true;
        }

        /// <summary>
        /// Closes the client connection
        /// </summary>
        /// <returns></returns>
        public Task DisconnectAsync() {
            return Task.Run(() => {
                reader.Close();
                writer.Close();
                networkStream.Close();
                client.Shutdown(SocketShutdown.Both);
                client.Close();
            });
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
        /// Registers a listener action to exexute on receive message events when ListenAsync is called
        /// </summary>
        /// <param name="listener">An action to execute when a message is received</param>
        public void AddMessageListener(Action<string> listener) {
            messageListeners.Add(listener);
        }

        /// <summary>
        /// Removes a listener from receive event subscriber list
        /// </summary>
        /// <param name="listener">An action to remove from subscriber list</param>
        public void RemoveMessageListener(Action<string> listener) {
            messageListeners.Remove(listener);
        }

        /// <summary>
        /// Asynchronously reads incoming messages and notifies registered message listeners on reveive
        /// </summary>
        /// <returns></returns>
        public async Task ListenAsync() {
            while (client.Connected) {
                string message = await ReadAsync();
                foreach (var listener in messageListeners) {
                    listener(message);
                }
            }
        }
    }
}
