#!/bin/bash

# path variables
flutter_root_folder=$(pwd)

# Start Flutter
cd $flutter_root_folder || (echo "Flutter root folder not found!" && exit 1)

# Select Linux device automatically
device_id=$(flutter devices | grep "Linux" | awk '{print $1}')
if [ -z "$device_id" ]; then
  echo "No Linux device found!"
  exit 1
fi

gnome-terminal --tab --title="Flutter App" -- flutter run -d $device_id
