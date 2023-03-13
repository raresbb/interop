#!/bin/bash

#
# Configuration
#

# The name of the network interface which is used by ptp4l and phc2sys to synchronize time
ETHERNET_INTERFACE_NAME="enp0s31f6"

#
#
#

fzd_gui_BIN=src/fzd_gui
fzd_gui_PROCESS_NAME=fzd_gui

# Close the running manual control process
if pidof $fzd_gui_PROCESS_NAME >/dev/null; then
  echo -e "Killing active manual control process."
  killall $fzd_gui_PROCESS_NAME
fi

# Start FZD GUI
if [ -f $fzd_gui_BIN ]; then
  gnome-terminal --tab --title="FZD GUI" -- /bin/bash -c "./${fzd_gui_BIN}; /bin/bash"
else
  echo "Manual Control binary not found! Missing file: ./${fzd_gui_BIN}"
  exit
fi

# Start time sync via PTP
if ! command -v ptp4l &>/dev/null; then
  echo "Package 'ptp4l' could not be found. Install it with sudo apt install linuxptp"
  exit
fi
if ! command -v phc2sys &>/dev/null; then
  echo "Package 'phc2sys' could not be found. Install it with sudo apt install linuxptp"
  exit
fi
gnome-terminal --tab --title="ptp4l" -- /bin/bash -c "sudo ptp4l -i ${ETHERNET_INTERFACE_NAME} -2 -s -m -S; /bin/bash"
gnome-terminal --tab --title="phc2sys" -- /bin/bash -c "sudo phc2sys -s ${ETHERNET_INTERFACE_NAME} -c CLOCK_REALTIME -S 1.0 -w -m; /bin/bash"

# Start new ASOA Orchestrator when manual control service is running
echo -n "Waiting for processes: $fzd_gui_PROCESS_NAME"
while
  true
  echo -n "."
do
  if pidof $fzd_gui_PROCESS_NAME >/dev/null; then
    echo -e "\nFZD GUI Service running!\nStarting Orchestrator..."
    sleep 1
    cd ./scripts || (echo "FZD GUI scripts directory not found!" && exit 1)
    gnome-terminal --tab --title="ASOA Orchestrator" -- asoa_orchestrator
    break
  fi
  sleep 1
done
cd ..
