/**
 * @file network.hpp
 * @brief Network class
 * @date 27-12-2023
 */
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

using boost::asio::ip::address;
using boost::asio::ip::udp;


#define IPADDRESS "127.0.0.1" // "192.168.1.64"
#define UDP_PORT 13152

/**
 * @brief Network Class 
*/
class Network {
    public: 
        /**
         * @brief Receive Class
        */
        class Receive {
            public:
                Receive(int port) : _udp_port(port) {}

                boost::asio::io_service io_service;
                udp::socket socket{io_service};
                boost::array<char, 1024> recv_buffer;
                udp::endpoint remote_endpoint;

                int count = 0;

                /**
                 * @brief Handle the receive and store the received IPs
                 * 
                 * @param error 
                 * @param bytes_transferred 
                 */
                void handle_receive(const boost::system::error_code &error, size_t bytes_transferred)
                {
                    if (error)
                    {
                        std::cout << "Receive failed: " << error.message() << "\n";
                        return;
                    }

                    std::string received = std::string(recv_buffer.begin(), recv_buffer.begin() + bytes_transferred);
                    std::cout << "Received : " << received << "\n";

                    std::istringstream iss(received);
                    std::string mot;
                    std::vector<std::string> mots;

                    while (std::getline(iss, mot, ' ')) {
                        mots.push_back(mot);
                    }

                    if (mots[0] == "new") {
                        std::cout << "New player\n";
                        received_ips.push_back(mots[1]);
                    }

                    if (++count > 0)
                    {
                        std::cout << "Count: " << count << "\n";
                        wait();
                    }
                }
                /**
                 * @brief Get the received IPs
                 * 
                 * @return std::vector<std::string> 
                 */
                const std::vector<std::string>& getReceivedIPs() const {
                    return received_ips;
                }

                /**
                 * @brief Clear the received IPs
                */
                const void clearReceivedIPs() {
                    received_ips.clear();
                }

                /**
                 * @brief Get the IP object
                 * 
                 * @return int 
                 */
                int getIP() const {
                    return _udp_port;
                }

                /**
                 * @brief Wait for a message
                */
                void wait()
                {
                    socket.async_receive_from(boost::asio::buffer(recv_buffer),
                                            remote_endpoint,
                                            boost::bind(&Receive::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                }

                /**
                 * @brief Receiver function
                */
                void receiver()
                {
                    socket.open(udp::v4());
                    socket.bind(udp::endpoint(address::from_string(IPADDRESS), _udp_port));

                    wait();

                    std::cout << "Receiving\n";
                    while (true) {
                        io_service.run();
                        io_service.reset(); // Réinitialiser le service pour le relancer
                    }
                    std::cout << "Receiver exit\n";
                }
            private:
                int _udp_port;
                std::vector<std::string> received_ips;

        };
        /**
         * @brief Receive Class
        */
        class Sender {
            public:
                Sender(int port) : _port(port) {}
                
                /**
                 * @brief Send a string to the server
                 * 
                 * @param in string to send
                 */
                void send(std::string in)
                {
                    boost::asio::io_service io_service;
                    udp::socket socket(io_service);
                    udp::endpoint remote_endpoint = udp::endpoint(address::from_string(IPADDRESS), _port);
                    socket.open(udp::v4());

                    boost::system::error_code err;
                    auto sent = socket.send_to(boost::asio::buffer(in), remote_endpoint, 0, err);
                    socket.close();
                    std::cout << "Sent Payload --- " << in << "\n";
                }
            private:
                int _port;
        };
};