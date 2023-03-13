import 'dart:async';
import 'dart:io';
import 'package:flutter/material.dart';
import 'package:angle_visualizer/vehicle.dart';

class AngleData {
  double angleFR;
  double angleFL;
  double angleRR;
  double angleRL;

  AngleData({
    required this.angleFR, 
    required this.angleFL, 
    required this.angleRR, 
    required this.angleRL
    });
}

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        primarySwatch: Colors.green,
      ),
      home: const RootPage(),
    );
  }
}

class RootPage extends StatefulWidget {  

  const RootPage({Key? key}) : super(key: key);

  @override
  State<RootPage> createState() => _RootPageState();
}

class _RootPageState extends State<RootPage> {
  late AngleData _angles;

  _RootPageState() {
    _angles = AngleData(angleFR: 0.0, angleFL: 0.0, angleRR: 0.0, angleRL: 0.0);
  }

  @override
  void initState() {
    super.initState();
    _readAngleData();
  }

// read angle data from server socket
  Future<void> _readAngleData() async {
    // Bind to the specified IP address and port
    var server = await ServerSocket.bind('127.0.0.1', 1234);
    print('Listening on ${server.address.address}:${server.port}');

    // Continuously listen for incoming connections
    server.listen((socket) {

      // Read incoming data from the socket
      socket.listen((data) {
        var values = String.fromCharCodes(data).split(',');
          setState(() {
            _angles = AngleData(
              angleFR: double.parse(values[0]),
              angleFL: double.parse(values[1]),
              angleRR: double.parse(values[2]),
              angleRL: double.parse(values[3]),
            );
          });
      }, onError: (error) {
        print('Error: $error');
      }, onDone: () {
      });
    }, onError: (error) {
      print('Error: $error');
    });
  }
    
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      // positioned in the center 
      body: Center(
        // child is the vehicle frame
        child: ConstrainedBox(
          constraints: const BoxConstraints(minWidth: 200, minHeight: 400),
          child: VehicleFrame(
            angleFL: _angles.angleFL,
            angleFR: _angles.angleFR,
            angleRL: _angles.angleRL,
            angleRR: _angles.angleRR,
          ),
        ),
      ),
    );
  }
}
