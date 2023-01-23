import 'dart:ffi';
import 'dart:io';
import 'package:flutter/material.dart';
import 'package:ffi/ffi.dart';

class FFIBridge {
  static bool initialize() {
    nativeApiLib = Platform.isMacOS || Platform.isIOS
        ? DynamicLibrary.process() // macos and ios
        : (DynamicLibrary.open(Platform.isWindows // windows
            ? 'api.dll'
            : 'libapi.so')); // android and linux

    final _getAngleFR = nativeApiLib.lookup<
        NativeFunction<Double Function()>>('getAngleFR');
    getAngleFR = _getAngleFR.asFunction<double Function()>();

    final _getAngleFL = nativeApiLib.lookup<
        NativeFunction<Double Function()>>('getAngleFL');
    getAngleFL = _getAngleFL.asFunction<double Function()>();

    final _getAngleRR = nativeApiLib.lookup<
        NativeFunction<Double Function()>>('getAngleRR');
    getAngleRR = _getAngleRR.asFunction<double Function()>();

    final _getAngleRL = nativeApiLib.lookup<
        NativeFunction<Double Function()>>('getAngleRL');
    getAngleRL = _getAngleRL.asFunction<double Function()>();

    return true;
  }

  static late DynamicLibrary nativeApiLib;
  static late Function getAngleFR;
  static late Function getAngleFL;
  static late Function getAngleRR;
  static late Function getAngleRL;

}

void main() {
  FFIBridge.initialize();
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(

        primarySwatch: Colors.blue,
      ),
      home: const MyHomePage(title: 'Flutter Demo Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({Key? key, required this.title}) : super(key: key);

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}


class _MyHomePageState extends State<MyHomePage> {

  @override
  Widget build(BuildContext context) {

    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Text('AngleFR: ${FFIBridge.getAngleFR()}', style: const TextStyle(fontSize: 40)),
            Text('AngleFL: ${FFIBridge.getAngleFL()}', style: const TextStyle(fontSize: 40)),
            Text('AngleRR: ${FFIBridge.getAngleRR()}', style: const TextStyle(fontSize: 40)),
            Text('AngleRL: ${FFIBridge.getAngleRL()}', style: const TextStyle(fontSize: 40)),
          ],
        ),
      ),
    );
  }
} 








