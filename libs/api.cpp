#include <iostream>
#include <thread>
#include <random>
#include <atomic>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <functional>
#include <cstring>

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
    std::uniform_real_distribution<double> distribution(-90.0, 90.0);
    auto random = std::bind(distribution, generator);
    while (!stop_thread) {
        angles->angle_FR = random();
        angles->angle_FL = random();
        angles->angle_RR = random();
        angles->angle_RL = random();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // print all angles, one on each row
        std::cout << "angle_FR: " << angles->angle_FR << std::endl;
        std::cout << "angle_FL: " << angles->angle_FL << std::endl;
        std::cout << "angle_RR: " << angles->angle_RR << std::endl;
        std::cout << "angle_RL: " << angles->angle_RL << std::endl;
        std::cout << "-----------------" << std::endl;
    }
}

int main() {
    Angles angles;
    // start the thread that updates the angles struct
    std::thread t(updateAngles, &angles);

    // create a shared memory object
    int shm_fd = shm_open("/shm_angles", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        std::cout << "Error creating shared memory object" << std::endl;
        return 1;
    }

    // configure the size of the shared memory object
    if (ftruncate(shm_fd, sizeof(angles)) == -1) {
        std::cout << "Error configuring size of shared memory object" << std::endl;
        return 1;
    }

    // memory map the shared memory object
    void* ptr = mmap(0, sizeof(angles), PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        std::cout << "Error memory mapping shared memory object" << std::endl;
        return 1;
    }

    while (!stop_thread) {
        // write the angles struct to the shared memory object
        memcpy(ptr, &angles, sizeof(angles));
    }

    // unmap the shared memory object
    if (munmap(ptr, sizeof(angles)) == -1) {
        std::cout << "Error unmapping shared memory object" << std::endl;
    }

    // close the shared memory object
    close(shm_fd);

    t.join();
    return 0;
}
