#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <csignal>
#include <math.h>
#include <future>
#include <atomic>
#include <string>
#include <functional>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
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

void control_thread(int pipe, double output_freq) {

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
        write(pipe, &angles, sizeof(angles));

        // Wait for a certain af time to achieve a constant updating frequency
        std::this_thread::sleep_for(std::chrono::nanoseconds(int(1.0 / output_freq * 1e9)));
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
    
    if (access("/tmp/AnglesPipe", F_OK) == -1) {
        if (mkfifo("/tmp/AnglesPipe", 0666) == -1) {
            std::cout << "Error creating named pipe" << std::endl;
            return 1;
        }
    }

    int pipe = open("/tmp/AnglesPipe", O_RDWR);
    if (pipe == -1) {
        std::cout << "Error opening named pipe" << std::endl;
        return 1;
    }

    // Control application runtime
    std::thread control_t(&control_thread, pipe, control_output_freq);

    // ASOA service runtime
    rtps_init();

    char hardware_name[] = "Linux";
    Runtime::init(hardware_name);

    const char name[] = "FZDGUI";
    auto *fzd_gui_service = new FZDGUIService(name, service_ptask_hz);
    Runtime::get()->publishService(fzd_gui_service);

    std::cout << "FZD GUI Service started..." << std::endl;

    while (true) {
        Runtime::get()->loop();
        usleep(1000000);
    }

    control_t.join();
    close(pipe);
    unlink("/tmp/AnglesPipe");

    return 0;
};

