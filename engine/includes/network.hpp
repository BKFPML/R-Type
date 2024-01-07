/**
 * @file network.hpp
 * @brief Network class
 * @date 07-01-2024
 */

#include <string>
#include <vector>

/**
 * @brief Virtual receive class
*/
class Receiver {
public:
    virtual ~Receiver() = default;

    virtual void receive() = 0;
    virtual std::vector<std::string> get_received_data() = 0;
    virtual void clear_received_data() = 0;
    virtual void clear_received_data(int index) = 0;
    virtual void clear_last_received_data() = 0;
    virtual void clear_first_received_data() = 0;
};

/**
 * @brief Virtual send class
*/
class Sender {
public:
    virtual ~Sender() = default;
    virtual void send(std::string in) = 0;
    virtual void send(std::vector<std::string> in) = 0;
};
