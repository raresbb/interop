#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include <math.h>
#include <future>
#include <atomic>
#include <functional>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <asoa/core/runtime.hpp>
#include "include/asoa_service/service.hpp"
#include "extern/inih/INIReader.h"
#include <mutex>

struct Angles {
    double angle_FR;
    double angle_FL;
    double angle_RR;
    double angle_RL;
};

// declare a mutex to protect the socket
std::mutex sock_mutex;

// In the GNUC Library, sig_atomic_t is a typedef for int, which is atomic on all systems that are supported by the GNUC Library
volatile sig_atomic_t do_shutdown = 0;
void sigint_handler(int) {
    if (do_shutdown == 0) {
        do_shutdown = 1;
    } else {
        std::exit(EXIT_SUCCESS);
    }
}

void control_thread(int sock, const addrinfo* addr, const double& output_freq) {

    // Init variables
    fzd_gui::dyn_state dyn_stateFL{};
    fzd_gui::dyn_state dyn_stateFR{};
    fzd_gui::dyn_state dyn_stateRL{};
    fzd_gui::dyn_state dyn_stateRR{};

    while (!do_shutdown) {
        // Reveive the current state
        fzd_gui_interface::rx_dyn_stateFL(dyn_stateFL);
        fzd_gui_interface::rx_dyn_stateFR(dyn_stateFR);
        fzd_gui_interface::rx_dyn_stateRL(dyn_stateRL);
        fzd_gui_interface::rx_dyn_stateRR(dyn_stateRR);

        const Angles angles{
            .angle_FR = dyn_stateFR.wheel_angle_deg * M_PI / 180.0,
            .angle_FL = dyn_stateFL.wheel_angle_deg * M_PI / 180.0,
            .angle_RR = dyn_stateRR.wheel_angle_deg * M_PI / 180.0,
            .angle_RL = dyn_stateRL.wheel_angle_deg * M_PI / 180.0
        };
        
        // TO BE DELETED - START
        std::cout << "Values: " << angles.angle_FR  << ", " << angles.angle_FL << ", " << angles.angle_RR << ", " << angles.angle_RL << std::endl;
        // TO BE DELETED - END

        // Pack the values into a string in the format "val1,val2,val3,val4"
        std::ostringstream ss;
        ss << angles.angle_FR << "," << angles.angle_FL << "," << angles.angle_RR << "," << angles.angle_RL;
        std::string values_str = ss.str();
        
        // Lock the mutex before accessing the socket
        std::unique_lock<std::mutex> lock(sock_mutex);

        // Connect to the server
        int result = connect(sock, addr->ai_addr, (int)addr->ai_addrlen);
        if (result == -1 && errno != EINPROGRESS) {
            std::cerr << "connect failed: " << std::strerror(errno) << std::endl;
            // Release the lock before returning
            lock.unlock();
            close(sock);
            return;
        }

        result = send(sock, values_str.c_str(), values_str.length(), 0);
        if (result == -1) {
            std::cerr << "send failed: " << std::strerror(errno) << std::endl;
        }
        // Release the lock before closing the socket
        lock.unlock();
        close(sock);

        // Lock the mutex before creating a new socket
        lock.lock();

        // Create a new socket for the next iteration
        sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (sock == -1) {
            std::cerr << "socket failed: " << std::strerror(errno) << std::endl;
            // Release the lock before returning
            lock.unlock();
            return;
        }

        // Release the lock after creating the new socket
        lock.unlock();

        // Wait for a certain af time to achieve a constant updating frequency
        std::this_thread::sleep_for(std::chrono::milliseconds(int(1.0 / output_freq * 1e3)));
    }

    std::cout << "Control thread terminated successfully!" << std::endl;
    std::cout << "Press Ctrl+C to terminate the service." << std::endl;
}

int main() {
    // setup signal handler
    signal(SIGINT, sigint_handler);

    std::string config_file_path = std::string(fzd_gui_ROOT_DIR) + "/config/config.ini";
    INIReader ini_reader(config_file_path);
    if (ini_reader.ParseError() < 0) {
        throw std::runtime_error("Can't load configuration file " + config_file_path);
    }
    const double angle_update_freq = ini_reader.GetReal("Update Frequencies", "angle_update_rate_hz", -1);
    const double service_ptask_hz = ini_reader.GetReal("Update Frequencies", "service_ptask_hz", -1);
    
    // Resolve the IP address and port
    const std::string ip = ini_reader.Get("IP Address", "ip_address", ""); // change this to the IP address of your receiver
    const std::string port = ini_reader.Get("IP Address", "port", ""); // Replace with your desired port
    addrinfo hints = {};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    addrinfo* addr;
    int addrinfo_result = getaddrinfo(ip.c_str(), port.c_str(), &hints, &addr);

    if (addrinfo_result != 0) {
        std::cerr << "getaddrinfo failed: " << gai_strerror(addrinfo_result) << std::endl;
        return 1;
    }

     // Lock the mutex before creating the socket
    std::unique_lock<std::mutex> lock(sock_mutex);

    // Create the socket
    int sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if (sock == -1) {
        std::cerr << "socket failed: " << std::strerror(errno) << std::endl;
        freeaddrinfo(addr);
        // Release the lock before returning
        lock.unlock();
        return 1;
    }

    // Release the lock after creating the socket
    lock.unlock();

    // Control application runtime
    std::thread control_t(&control_thread, sock, addr, std::ref(angle_update_freq));

    // ASOA service runtime
    auto asoa_driver = asoa_init();

    // return in case of an error
    if(asoa_driver == nullptr) {
        std::cout << "Failed to initialize RTPS protocol." << std::endl;
        return -1;
    }

    char hardware_name[] = "Linux";
    std::cout << "Hello, I am the " << hardware_name << "." << std::endl;
    // make sure the hardware name equals the name specified in the configuration
    if(strcmp(asoa_driver->hardware_name, "nosec") == 0 || strcmp(asoa_driver->hardware_name, hardware_name) != 0) {
        std::cout << "WARNING: Hardware name does not match the name provided in the security configuration.";
    }

    Runtime::init(hardware_name);

    const char service_name[] = "FZDGUI";
    auto *fzd_gui_service = new FZDGUIService(service_name, service_ptask_hz);
    Runtime::get()->publishService(fzd_gui_service);

    std::cout << "FZD GUI Service started..." << std::endl;

    Runtime::get()->loop();

    // clean up after all services have been terminated
    Runtime::get()->destroy();
    asoa_destroy();
    std::cout << "Runtime destroyed." << std::endl;

    control_t.join();
    lock.unlock();
    close(sock);
    freeaddrinfo(addr);

    return 0;
};