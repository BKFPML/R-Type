/**
 * @file network.hpp
 * @brief Network class
 * @date 07-01-2024
 */

#include <string>
#include <vector>

/**
 * @brief Interface for a receiver
*/
class IReceiver {
public:
    virtual ~IReceiver() = default;

    virtual void receive() = 0;
    virtual std::vector<std::string> get_received_data() = 0;
    virtual void clear_received_data() = 0;
    virtual bool is_port_bound() = 0;
    virtual void clear_received_data(int index) = 0;
    virtual void clear_last_received_data() = 0;
    virtual void clear_first_received_data() = 0;
};

/**
 * @brief Interface for a sender
*/
class ISender {
public:
    virtual ~ISender() = default;
    virtual void send(std::string in) = 0;
    virtual void send(std::vector<std::string> in) = 0;
    virtual int get_port() = 0;
    virtual std::string get_ip() = 0;
};
