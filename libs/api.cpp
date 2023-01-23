#ifdef WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT extern "C" __attribute__((visibility("default"))) __attribute__((used))
#endif

#include <cstring>
#include <ctype.h>
#include <thread>
#include <random>
#include <functional>
#include <atomic>

std::atomic<bool> stop_thread{false};
std::function<void(double, double, double, double)> callback;

double angle_FR = 0.0;
double angle_FL = 0.0;
double angle_RR = 0.0;
double angle_RL = 0.0;

std::mt19937 generator(std::random_device{}());
std::uniform_real_distribution<double> distribution(0.0, 90.0);

void updateAnglesThread() {
    while (!stop_thread) {
        angle_FR = distribution(generator);
        angle_FL = distribution(generator);
        angle_RR = distribution(generator);
        angle_RL = distribution(generator);
        if (callback) {
            callback(angle_FR, angle_FL, angle_RR, angle_RL);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

EXPORT
void startUpdates(std::function<void(double, double, double, double)> cb) {
    callback = cb;
    std::thread t(updateAnglesThread);
    t.detach();
}

EXPORT
void stopUpdates() {
    stop_thread = true;
}
