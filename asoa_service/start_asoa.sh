#!/bin/bash

fzd_gui_PROCESS_NAME=fzd_gui

function shutdown() {
  echo "Killing ASOA services..."
  killall asoa_orchestrator
  killall $fzd_gui_PROCESS_NAME
}

echo "--- TEST SETUP START --- Only compatible with standard linux console!"

# path variables
cm_asoa_service_path=$(cd .. && pwd)/cm-asoa-service
fzd_gui_src_path=$(pwd)/src
fzd_gui_scripts_path=$(pwd)/scripts
#flutter_root_folder=$(pwd)

# Start CarMaker if not already running
if pidof "HIL.exe" >/dev/null
then
  echo "Using current CarMaker instance."
else
  echo "Creating new CarMaker instance. NOTE: Remember to connect Cisco Anyconnect VPN Client! Otherwise, CarMaker will not boot."
  cd $cm_asoa_service_path || (echo "CarMaker ASOA directory not found!" && exit 1)
  gnome-terminal --tab --title=CarMaker -- ./CMStart.sh
fi

# Start FZD GUI Service
cd $fzd_gui_src_path || (echo "FZD GUI executable directory not found!" && exit 1)
gnome-terminal --tab --title="FZD GUI" -- ./$fzd_gui_PROCESS_NAME


# Start new ASOA Orchestrator when services are running
echo -n "Waiting for processes: $fzd_gui_PROCESS_NAME "
while true
echo -n "."
do
  if pidof $fzd_gui_PROCESS_NAME >/dev/null 
  then
    echo -e "\nASOA Services running!\nStarting Orchestrator..."
    sleep 1
    cd $fzd_gui_scripts_path || (echo "FZD GUI scripts directory not found!" && exit 1)
    gnome-terminal --tab --title="ASOA Orchestrator" -- asoa_orchestrator
    break
  fi
  sleep 1
done

# Start Flutter
#cd $flutter_root_folder || (echo "Flutter root folder not found!" && exit 1)
#gnome-terminal --tab --title="Flutter App" -- flutter run

# Initialise trap to call shutdown function when signal 2 (SIGINT) is received
trap "shutdown; exit" SIGINT

echo "--- TEST SETUP DONE ---"
echo "Press Ctrl+C to abort"
while true; do
  true
done
