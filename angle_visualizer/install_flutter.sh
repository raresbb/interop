#!/bin/bash

# Get the current Dart SDK version
current_version="$(dart --version | grep -oP 'version: \K\d+\.\d+\.\d+')"

# Download the latest version of the Dart SDK
latest_version="$(curl -s https://storage.googleapis.com/dart-archive/channels/stable/release/latest/VERSION | awk '{ print $2 }')"
wget "https://storage.googleapis.com/dart-archive/channels/stable/release/$latest_version/sdk/dartsdk-linux-arm-release.zip"

# Extract the downloaded archive to /opt/dart-sdk
sudo mkdir /opt/dart-sdk
sudo unzip dartsdk-linux-arm-release.zip -d /opt/dart-sdk
sudo chown -R $USER:$USER /opt/dart-sdk
rm dartsdk-linux-arm-release.zip

# Update the system PATH to include the new Dart SDK location
echo "export PATH=\"\$PATH:/opt/dart-sdk/bin\"" >> ~/.bashrc
source ~/.bashrc

# Install Flutter
sudo apt-get update
sudo apt-get install git curl unzip xz-utils zip libglu1-mesa
git clone https://github.com/flutter/flutter.git
export PATH="$PATH:`pwd`/flutter/bin"
flutter precache

# Install dependencies for the Dart package
dart pub get
