#ifdef WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT extern "C" __attribute__((visibility("default"))) __attribute__((used))
#endif

#include <iostream>
#include <thread>
#include <random>
#include <atomic>
#include <csignal>
#include <functional>
#include <csignal>


std::mt19937 generator(std::random_device{}());
std::atomic<bool> stop_thread{false};

double angle_FR = 0.0;
double angle_FL = 0.0;
double angle_RR = 0.0;
double angle_RL = 0.0;

EXPORT double getAngleFR() {
    return angle_FR;
}

EXPORT double getAngleFL() {
    return angle_FL;
}

EXPORT double getAngleRR() {
    return angle_RR;
}

EXPORT double getAngleRL() {
    return angle_RL;
}

void updateAngles() {
    std::uniform_real_distribution<double> distribution(-90.0, 90.0);
    auto random = std::bind(distribution, generator);
    while (!stop_thread) {
        angle_FR = random();
        angle_FL = random();
        angle_RR = random();
        angle_RL = random();
        
        std::cout << "angle_FR: " << angle_FR << std::endl;
        std::cout << "angle_FL: " << angle_FL << std::endl;
        std::cout << "angle_RR: " << angle_RR << std::endl;
        std::cout << "angle_RL: " << angle_RL << std::endl;
        std::cout << "---------------" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}


int main() {
    std::thread t(updateAngles);

    std::signal(SIGINT, [](int) {
        stop_thread = true;
    });

    t.join();

    return 0;
}