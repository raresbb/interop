# FZD GUI - Steering Angles Visualizer

This repository contains a GUI application, which provides an easy way to visualize the current steering angles of Unicar vehicles.

# Usage

Define your **network interface name** responsible for receiving PTP signals and synchronizing the system time with the vehicle.
This is done by changing a variable called `ETHERNET_INTERFACE_NAME` at the very top of [run.sh](run.sh). Afterwards, run this bash script by typing `./run.sh` from project root.

# Dependencies and Requirements

## System Requirements

### Ubuntu

- Version used during development: [18.04 LTS (Bionic Beaver)](https://old-releases.ubuntu.com/releases/18.04.5/)
<!---
### Xbox Gamepad

The gamepad used during development and testing was the Xbox Elite Series 2 Controller.

Ubuntu 18.04 comes with a kernel module as gamepad driver preinstalled. This driver should be sufficient.
However, if you run into compatibility issues try updating to the most recent version from [here](https://github.com/paroj/xpad)
or try installing a different driver (for example [this one](https://github.com/medusalix/xone)).

If you run the module [gamepad.py](include/core/gamepad.py) (Our gamepad API) as `__main__` you can have a look at your current axis and button mappings in the terminal.
This provides a fast debugging tool.
-->
### Packages

Start a terminal and run `sudo apt update`. Now proceed with the following commands:

- GCC Compiler `sudo apt install build-essential`
- Git `sudo apt install git`
- [CMake](https://cmake.org/install/) `sudo snap install cmake --classic`
  
  This installs a more recent version than `sudo apt install cmake` would do. The required minimum version for this project is 3.19.


- ASOA and dependencies
    1. Install `asoa_core.deb` and `asoa_orchestrator.deb`
    2. OpenSSL (required by ASOA)
       `sudo apt install libssl-dev`
    3. Boost Python (required by ASOA Orchestrator)
       `sudo apt install libboost-python-dev`
    4. [Fast DDS](https://github.com/eProsima/Fast-DDS) (formerly Fast RTPS) (required by ASOA Core)
        1. Asio and tinyxml2 libraries `sudo apt install libasio-dev libtinyxml2-dev`
        2. Create a temporary directory and start terminal inside. Run the following commands in this terminal.
        3. [Fast CDR](https://github.com/eProsima/Fast-CDR)
           ```shell
           git clone https://github.com/eProsima/Fast-CDR.git
           mkdir Fast-CDR/build && cd Fast-CDR/build
           cmake ..
           sudo cmake --build . --target install
           cd ../..  # Back to temporary directory root
           ```
        4. [Foonathan memory](https://github.com/foonathan/memory)
           ```shell
           git clone https://github.com/eProsima/foonathan_memory_vendor.git
           mkdir foonathan_memory_vendor/build && cd foonathan_memory_vendor/build
           cmake ..
           sudo cmake --build . --target install
           cd ../..  # Back to temporary directory root
           ```
        5. Once all dependencies are installed, compile and install Fast DDS
           ```shell
           git clone https://github.com/eProsima/Fast-DDS.git -b 2.3.0  # Currently required version of ASOA Core
           mkdir Fast-DDS/build && cd Fast-DDS/build
           cmake ..
           sudo cmake --build . --target install
           cd ../..  # Back to temporary directory root
           ```
           If you're not able to successfully install Fast DDS manually from source, another option is to download the latest
           release [from eProsimas website](https://eprosima.com/index.php/downloads-all) and do the following:
            - Extract the downloaded file.
            - Open terminal inside extracted directory.
            - Run install script `sudo ./install.sh`

           Note that you have to register yourself on the website before being able to download, though.

# Cloning and Installing

## Cloning
- Besides the FZD GUI service, there is one other service required. Therefore, it is necessary to create a parent folder <name_parent_folder> and **clone** both services inside it. The repositories for each service can be found under the following links:
   1. [cm-asoa-service](https://git.rwth-aachen.de/fzd/unicar-agil/dienste-repositories/cm-asoa-service)
   1. [fzd_gui](https://git.rwth-aachen.de/fzd/unicar-agil/dienste-repositories/manual_control)

- E.g. cloning:
   ```
      git clone --recursive https://git.rwth-aachen.de/fzd/unicar-agil/dienste-repositories/manual_control.git
   ```
- Before cloning [cm-asoa-service](https://git.rwth-aachen.de/fzd/unicar-agil/dienste-repositories/cm-asoa-service) make sure to check its README as it might contain additional submodules or dependencies.

- In the end, the folder structure should look as follows:
   ```
   <name_parent_folder>
   ├── cm-asoa-service
   └── fzd_gui
   ```

- **<font color="red"> The parent folder structure and names of the subfolders are important for the testing process.</font>**

## Installation

- The **FZD GUI** repository contains an installation setup script. Therefore, open a terminal **inside the project root** and run `./install.sh`. This script will install all required dependencies and build the project.

- Install [cm-asoa-service](https://git.rwth-aachen.de/fzd/unicar-agil/dienste-repositories/cm-asoa-service) as described in its respective README as it might have additional dependencies to be installed.

- Install Dart and Flutter:
Install Dart manually:
1. Download the Dart SDK for ARM Linux from the official Dart website: https://dart.dev/tools/sdk/archive
2. Extract the contents of the downloaded archive to a directory on the Raspberry Pi, for example `/opt/dart-sdk`.
3. Add the bin directory of the Dart SDK to the PATH environment variable by adding the following line to your `.bashrc` file:
   ```
      export PATH="$PATH:/opt/dart-sdk/bin"
   ```
4. Save the file and run the command source `~/.bashrc` to apply the changes.
5. Verify that Dart is installed by running the command `dart --version`.
Open a terminal **inside the project root** and run `./install_flutter.sh`.

# Testing

The **FZD GUI** repository contains a testing setup script, which will start all required services and applications. Follow the steps below to test the project:

1. Open a terminal **inside the project root** and run `./test.sh`.
2. There should be a total of 5 terminal tabs open by now and several programs should have started.
   - The main tab, where you executed the testing script.
   - CarMaker tab, which hosts the CarMaker application.
   - FZD GUI tab, which hosts the GUI displaying the current steering angles
   - ASOA Orchestrator tab, where you can orchestrate all the available ASOA services.
   - Flutter App tab, which hosts the Flutter application.
3. If there didn't occur any errors, you can procees with setting up CarMaker for simulation.
4. File -> Open -> Select `empty_testarea_UNICAR` -> OK
5. File -> IPGMovie
6. Application -> Start & Connect
7. Inside the ASOA Orchestrator tab, make sure the necessary services are registered with `ls` and then run `mk SIL`
8. Make sure `realtime` is selected under the Simulation - Performance field.)
9. Start Simulation by clicking on the green `Start` button.
10. The simulation should start and the steering angles should be displayed in the FZD GUI tab.
