# testffi

A new Flutter project.

## Getting Started

This project is a starting point for a Flutter application.

A few resources to get you started if this is your first Flutter project:

- [Lab: Write your first Flutter app](https://flutter.dev/docs/get-started/codelab)
- [Cookbook: Useful Flutter samples](https://flutter.dev/docs/cookbook)

For help getting started with Flutter, view our
[online documentation](https://flutter.dev/docs), which offers tutorials,
samples, guidance on mobile development, and a full API reference.

## Commands for dart

dart pub get      -> downloading dependencies
flutter run       -> runs the app from terminal
flutter run --hot -> enables hot reloading. This means that after the initial build, you can make code changes and see them reflected in the running app without having to rebuild the entire app.

## Other plan

class Angles
private:
  FR
  FL
  RR
  RL
public:
  set Angles() {}
  
  EXPORT
  get Angles() {}

## Inter Process Communication (IPC)

Pipe

Socket

JSON: Serializing data as JSON and passing it between the two languages can be a simple and effective way to share data. This is a popular option when the data being passed is relatively small and the data structure is not too complex.

Shared Memory: This is a low-level method that allows you to create a shared memory segment that can be accessed by both Dart and C++. This method can be faster than JSON because it does not involve serialization and deserialization.

Isolates: Dart supports the concept of isolates, which are separate threads of execution that can run in parallel. You can use isolates to run your C++ code in parallel with your Dart code, which can be a good option if your C++ code is computationally intensive.

FFI: Foreign Function Interface (FFI) allows you to call C-style functions directly from Dart. It's good option if you have existing C/C++ libraries that you want to use in your Dart code.