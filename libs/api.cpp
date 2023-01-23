#include <iostream>
#include <thread>
#include <random>
#include <atomic>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <functional>
#include <sys/types.h>
#include <sys/stat.h>

std::mt19937 generator(std::random_device{}());
std::atomic<bool> stop_thread{false};

struct Angles {
    double angle_FR;
    double angle_FL;
    double angle_RR;
    double angle_RL;
};

// function that updates the angles struct
void updateAngles(Angles* angles) {
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);
    auto random = std::bind(distribution, generator);
    while (!stop_thread) {
        angles->angle_FR = random();
        angles->angle_FL = random();
        angles->angle_RR = random();
        angles->angle_RL = random();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    // create a named pipe
    if (mkfifo("/tmp/AnglesPipe", 0666) == -1) {
        std::cout << "Error creating named pipe" << std::endl;
        return 1;
    }

    Angles angles;
    // start the thread that updates the angles struct
    std::thread t(updateAngles, &angles);

    int pipe;
    // open the pipe for writing
    pipe = open("/tmp/AnglesPipe", O_WRONLY);
    if (pipe == -1) {
        std::cout << "Error opening named pipe" << std::endl;
        return 1;
    }

    while (!stop_thread) {
        // write the angles struct to the pipe
        write(pipe, &angles, sizeof(angles));
    }

    // close the pipe
    close(pipe);

    t.join();
    return 0;
}