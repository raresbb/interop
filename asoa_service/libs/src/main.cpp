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

struct Angles {
    double angle_FR;
    double angle_FL;
    double angle_RR;
    double angle_RL;
};

// In the GNUC Library, sig_atomic_t is a typedef for int, which is atomic on all systems that are supported by the GNUC Library
volatile sig_atomic_t do_shutdown = 0;

void sigint_handler(int) {
    if (do_shutdown == 0) {
        do_shutdown = 1;
    } else {
        std::exit(EXIT_SUCCESS);
    }
}

void control_thread(int sock, double output_freq) {

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

        Angles angles;
        angles.angle_FR = dyn_stateFR.wheel_angle_deg * M_PI / 180.0;
        angles.angle_FL = dyn_stateFL.wheel_angle_deg * M_PI / 180.0;
        angles.angle_RR = dyn_stateRR.wheel_angle_deg * M_PI / 180.0;
        angles.angle_RL = dyn_stateRL.wheel_angle_deg * M_PI / 180.0;
        
        // Send the current state to the GUI
        /*
        int result = send(sock, &angles, sizeof(angles), 0);
        if (result == -1) {
            std::cerr << "send failed: " << std::strerror(errno) << std::endl;
        }
        */
        // TO BE DELETED - START
        std::cout << "Values: " << angles.angle_FR  << ", " << angles.angle_FL << ", " << angles.angle_RR << ", " << angles.angle_RL << std::endl;

        // Pack the values into a string in the format "val1,val2,val3,val4"
        std::ostringstream ss;
        ss << angles.angle_FR << "," << angles.angle_FL << "," << angles.angle_RR << "," << angles.angle_RL;
        std::string values_str = ss.str();
        
        // If connection is successful, send the values to the server and close the socket
        int result = send(sock, values_str.c_str(), values_str.length(), 0);
        if (result == -1) {
            std::cerr << "send failed: " << std::strerror(errno) << std::endl;
        }
        close(sock);

        // TO BE DELETED - END

        // Wait for a certain af time to achieve a constant updating frequency
        //std::this_thread::sleep_for(std::chrono::nanoseconds(int(1.0 / output_freq * 1e9)));
        // sleep for 100 ms
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
    double control_output_freq = ini_reader.GetReal("Update Frequencies", "control_output_hz", -1);
    double service_ptask_hz = ini_reader.GetReal("Update Frequencies", "service_ptask_hz", -1);
    
    // Resolve the IP address and port
    const char* ip = "192.168.1.4"; // Replace with your desired IP address
    const char* port = "1234"; // Replace with your desired port
    addrinfo hints = {};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    addrinfo* addr;
    int result = getaddrinfo(ip, port, &hints, &addr);
    if (result != 0) {
        std::cerr << "getaddrinfo failed: " << gai_strerror(result) << std::endl;
        return 1;
    }

    // Create the socket
    int sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if (sock == -1) {
        std::cerr << "socket failed: " << std::strerror(errno) << std::endl;
        freeaddrinfo(addr);
        return 1;
    }

    // Connect to the server
    result = connect(sock, addr->ai_addr, (int)addr->ai_addrlen);
    if (result == -1 && errno != EINPROGRESS) {
        std::cerr << "connect failed: " << std::strerror(errno) << std::endl;
        close(sock);
        freeaddrinfo(addr);
        return 1;
    }

    // Wait for the connection to be established or until a timeout occurs
    fd_set write_fds;
    FD_ZERO(&write_fds);
    FD_SET(sock, &write_fds);
    timeval timeout = {};
    timeout.tv_sec = 5; // 5 second timeout
    result = select(sock + 1, NULL, &write_fds, NULL, &timeout);
    if (result == -1) {
        std::cerr << "select failed: " << std::strerror(errno) << std::endl;
        close(sock);
        freeaddrinfo(addr);
        return 1;
    }
    else if (result == 0) {
        std::cerr << "connect timed out" << std::endl;
        close(sock);
        freeaddrinfo(addr);
        return 1;
    }

    // Control application runtime
    std::thread control_t(&control_thread, sock, control_output_freq);

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
    close(sock);
    freeaddrinfo(addr);

    return 0;
};

