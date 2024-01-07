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

        void send(std::string message) override;
        void send(std::vector<std::string> messages) override;

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

        void receive() override;

        std::vector<std::string> get_received_data() override {
            return received_data;
        }

        void clear_received_data() override {
            received_data.clear();
        }

        void clear_received_data(int index) override {
            received_data.erase(received_data.begin() + index);
        }

        void clear_first_received_data() override {
            received_data.erase(received_data.begin());
        }

        void clear_last_received_data() override {
            received_data.pop_back();
        }

    private:
        int _udp_port;
        std::string _ip;
        std::vector<std::string> received_data;
    };
};