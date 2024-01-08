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

#define IPADDRESS "0.0.0.0"

/**
 * @brief Boost Network Class
 */
class UDPBoostNetwork {
public:
    /**
     * @brief Send Class
     */
    class UDPSender : public Sender {
    public:
        UDPSender(int port_to_send, std::string ip = IPADDRESS) : _udp_port(port_to_send), _ip(ip) {}

        /**
         * @brief Send a message with UDP
         * 
         * @param message 
         */
        void send(std::string message) override {
            boost::asio::io_context io_context;
            boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0));
            boost::asio::ip::udp::resolver resolver(io_context);
            boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), "0.0.0.0", std::to_string(_udp_port));
            boost::asio::ip::udp::endpoint receiver_endpoint = *resolver.resolve(query);
            
            socket.send_to(boost::asio::buffer(message), receiver_endpoint);

            std::cout << "Sent: " << message << std::endl;
        }

        /**
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
    private:
        int _udp_port;
        std::string _ip;
    };
        
    /**
     * @brief Receive Class
    */
    class UDPReceiver : public Receiver {
    public:
        UDPReceiver(int port, std::string ip = IPADDRESS) : _udp_port(port), _ip(ip) {}

        /**
         * @brief Receive a message with UDP
         * 
         * @return std::string 
         */
        void receive() override {
            std::cout << "Listening on port: " << _udp_port << std::endl;
            boost::asio::io_context io_context;
            boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), _udp_port));
            boost::array<char, 1024> recv_buffer;
            boost::asio::ip::udp::endpoint remote_endpoint;
            boost::system::error_code error;
            std::string received;

            while (true) {
                size_t received_bytes = socket.receive_from(boost::asio::buffer(recv_buffer), remote_endpoint, 0, error);
                if (error && error != boost::asio::error::message_size) {
                    throw boost::system::system_error(error);
                }
                received = std::string(recv_buffer.begin(), recv_buffer.begin() + received_bytes);
                std::cout << "Received data from: " << remote_endpoint.address() << std::endl;
                std::cout << "Received data: " << received << std::endl;
                if (split(received, " ")[0] == "quit" && split(received, " ")[1] == std::to_string(_udp_port)) {
                    break;
                }
                received_data.push_back(received);
            }
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
            return received_data;
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
        int _udp_port;
        std::string _ip;
        std::vector<std::string> received_data;
    };
};