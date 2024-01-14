/**
 * @file boost.hpp
 * @brief Boost class header file
 * @date 30-12-2023
 */
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include "../network.hpp"
/**
 * @brief Boost Network Class
 */
class UDPBoostNetwork {
    public:
        /**
         * @brief Send Class
         */
        class UDPSender : public ISender {
        public:
            UDPSender(int port_to_send, std::string ip) : _udp_port(port_to_send), _ip(ip) {}
            /**
             * @brief Send a message with UDP
             * 
             * @param message 
             */
            void send(std::string message) override {
                boost::asio::io_context io_context;
                boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0));
                boost::asio::ip::udp::resolver resolver(io_context);
                // std::cout << "Sent: " << message << " to "<< _ip <<":"<<_udp_port << std::endl;
                boost::asio::ip::udp::endpoint receiver_endpoint(boost::asio::ip::address::from_string(_ip), _udp_port);
                socket.connect(receiver_endpoint);
                socket.send(boost::asio::buffer(message, message.size()));
                socket.close();
            }
            /**
             * @brief Get the port object
             * 
             * @return int 
             */
            std::string getLocalIPAddress() {
                try {
                    boost::asio::io_service netService;
                    boost::asio::ip::udp::resolver resolver(netService);
                    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), "google.com", "");
                    boost::asio::ip::udp::resolver::iterator endpoints = resolver.resolve(query);
                    boost::asio::ip::udp::endpoint ep = *endpoints;
                    boost::asio::ip::udp::socket socket(netService);
                    socket.connect(ep);
                    boost::asio::ip::address addr = socket.local_endpoint().address();
                    return addr.to_string();
                } catch (std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
                return "";
            }
            /**
             * 
             * @brief Send a vector of messages with UDP
             * 
             * @param messages 
             */
            void send(std::vector<std::string> messages) override {
                for (const auto& message : messages) {
                    send(message);
                }
            }
            /**
             * @brief Get the port object
             * 
             * @return int 
             */
            int get_port() override {
                return _udp_port;
            }
            /**
             * @brief Get the ip object
             * 
             * @return std::string 
             */
            std::string get_ip() override {
                return _ip;
            }
        private:
            int _udp_port;
            std::string _ip;
        };
    
        /**
         * @brief Receive Class
        */
        class UDPReceiver : public IReceiver {
        public:
            UDPReceiver(int port, std::string ip) : _udp_port(port), _ip(ip), _isRunning(true) {}
            UDPReceiver(int port) : _udp_port(port), _ip(getLocalIPAddress()), _isRunning(true) {}
            /**
             * @brief Receive a message with UDP
             * 
             * @return std::string 
             */
            void receive() override {
                std::cout << "Listening on port: " << _udp_port << std::endl;
                boost::asio::io_context io_context;
                boost::array<char, 1024> recv_buffer;
                std::cout << "Server Ip: " << _ip << " Port: " << _udp_port << std::endl;
                receiver_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(_ip), _udp_port);
                boost::asio::ip::udp::socket socket(io_context, receiver_endpoint);
                asyncReceive(socket, recv_buffer);
                while (_isRunning) {
                    try {
                        io_context.run();
                    } catch (const std::exception& e) {
                        std::cerr << e.what() << std::endl;
                    }
                }
                if (socket.is_open()) {
                    socket.close();
                }
            }

            /**
             * @brief Get the ip object
             *
             * @return int
             */
            std::string getLocalIPAddress() {
                try {
                    boost::asio::io_service netService;
                    boost::asio::ip::udp::resolver resolver(netService);
                    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), "google.com", "");
                    boost::asio::ip::udp::resolver::iterator endpoints = resolver.resolve(query);
                    boost::asio::ip::udp::endpoint ep = *endpoints;
                    boost::asio::ip::udp::socket socket(netService);
                    socket.connect(ep);
                    boost::asio::ip::address addr = socket.local_endpoint().address();
                    return addr.to_string();
                } catch (std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
                return "";
            }
            /**
             * @brief Split a string
             * 
             * @param str 
             * @param token 
             * @return std::vector<std::string> 
             */
            std::vector<std::string> split(const std::string& str, const std::string& delim)
            {
                std::vector<std::string> tokens;
                size_t prev = 0, pos = 0;
                do {
                    pos = str.find(delim, prev);
                    if (pos == std::string::npos)
                        pos = str.length();
                    std::string token = str.substr(prev, pos - prev);
                    if (!token.empty())
                        tokens.push_back(token);
                    prev = pos + delim.length();
                } while (pos < str.length() && prev < str.length());
                return tokens;
            }
            /**
             * @brief Get the port object
             * 
             * @return int 
             */
            bool is_port_bound() override {
                boost::asio::io_context io_context;
                boost::asio::ip::tcp::acceptor acceptor(io_context);
                try {
                    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), _udp_port);
                    acceptor.open(endpoint.protocol());
                    acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
                    acceptor.bind(endpoint);
                    return false;  // Port is not bound
                } catch (const boost::system::system_error& e) {
                    if (e.code() == boost::asio::error::address_in_use) {
                        // Port is already bound
                        return true;
                    } else {
                        // Handle other errors if needed
                        throw e;
                    }
                }
            }
            /**
             * @brief Get the received data object
             * 
             * @return std::vector<std::string> 
             */
            std::vector<std::string> get_received_data() override {
                try {
                    return received_data;
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
                return {};
            }
            /**
             * @brief set the running object
             *
             * @param running
             */
            void set_running(bool running) override {
                _isRunning = running;
            }
            
            /**
             * @brief Clear the received data object
             * 
             */
            void clear_received_data() override {
                received_data.clear();
            }
            /**
             * @brief Clear the received data object
             * 
             * @param index 
             */
            void clear_received_data(int index) override {
                received_data.erase(received_data.begin() + index);
            }
            /**
             * @brief Clear the first received data object
             * 
             */
            void clear_first_received_data() override {
                received_data.erase(received_data.begin());
            }
            /**
             * @brief Clear the last received data object
             * 
             */
            void clear_last_received_data() override {
                received_data.pop_back();
            }
            
        private:
            bool _isRunning;
            int _udp_port;
            std::string _ip;
            std::vector<std::string> received_data;
            boost::asio::ip::udp::endpoint receiver_endpoint;  // Declaration here
            /**
             * @brief Asynchronous receive
             * 
             * @param socket 
             * @param recv_buffer 
             */
            void asyncReceive(boost::asio::ip::udp::socket& socket, boost::array<char, 1024>& recv_buffer) {
                if (!_isRunning) {
                    if (socket.is_open()) {
                        socket.close();
                    }
                    return;
                }
                socket.async_receive_from(
                    boost::asio::buffer(recv_buffer),
                    receiver_endpoint,
                    boost::bind(&UDPReceiver::handleReceive, this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred,
                                boost::ref(socket),
                                boost::ref(recv_buffer)));
            }
            /**
             * @brief Handle the received message
             * 
             * @param error 
             * @param bytes_transferred 
             * @param socket 
             * @param recv_buffer 
             */
            void handleReceive(const boost::system::error_code& error, std::size_t len, boost::asio::ip::udp::socket& socket, boost::array<char, 1024>& recv_buffer) {
                if (error && error != boost::asio::error::message_size)
                    throw boost::system::system_error(error);

                if (!_isRunning) {
                    if (socket.is_open()) {
                        socket.close();
                    }
                    return;
                }

                try {
                    std::string message(recv_buffer.begin(), recv_buffer.begin() + len);
                    // std::cout << "Received: " << message << std::endl;
                    received_data.push_back(message);
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }

                asyncReceive(socket, recv_buffer);
            }
        };
};