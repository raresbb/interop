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
#include <csignal>

std::mt19937 generator(std::random_device{}());
std::atomic<bool> stop_thread{false};

struct Angles {
    double angle_FR;
    double angle_FL;
    double angle_RR;
    double angle_RL;
};

void updateAngles(int pipe) {
    std::uniform_real_distribution<double> distribution(-90.0, 90.0);
    auto random = std::bind(distribution, generator);
    while (!stop_thread) {
        Angles angles;
        angles.angle_FR = random();
        angles.angle_FL = random();
        angles.angle_RR = random();
        angles.angle_RL = random();
        write(pipe, &angles, sizeof(angles));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "angle_FR: " << angles.angle_FR << std::endl;
        std::cout << "angle_FL: " << angles.angle_FL << std::endl;
        std::cout << "angle_RR: " << angles.angle_RR << std::endl;
        std::cout << "angle_RL: " << angles.angle_RL << std::endl;
        std::cout << "---------------" << std::endl;
        
    }
}

int main() {
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

    std::thread t(updateAngles, pipe);


    // when ctrl+c is pressed, stop the thread
    std::signal(SIGINT, [](int) {
        stop_thread = true;
    });

    t.join();
    close(pipe);
    unlink("/tmp/AnglesPipe");

    return 0;
}


/*
  void _readAngleData() async {
    final File pipe = File("/tmp/AnglesPipe");
    final RandomAccessFile randomAccessFile = await pipe.open(mode: FileMode.read);
    final ByteData data = (await randomAccessFile.read(16)) as ByteData;
    _angles = AngleData(
      angleFR: data.getFloat64(0),
      angleFL: data.getFloat64(8),
      angleRR: data.getFloat64(16),
      angleRL: data.getFloat64(24),
    );
    setState(() {});
  }
  */