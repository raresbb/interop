import 'dart:async';
import 'dart:io';
import 'dart:typed_data';
import 'package:flutter/material.dart';
import 'package:angle_visualizer/vehicle.dart';

class AngleData {
  double angleFR;
  double angleFL;
  double angleRR;
  double angleRL;

  AngleData({required this.angleFR, required this.angleFL, required this.angleRR, required this.angleRL});
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

  // read angle data from pipe
  Future<void> _readAngleData() async {
  Timer.periodic(const Duration(seconds: 1), (_) async {
    try {
      var file = File('/tmp/AnglesPipe');
      var randomAccessFile = await file.open(mode: FileMode.read);
      var data = Uint8List(32);

      while (true) {
        await randomAccessFile.readInto(data);
        var buffer = data.buffer;
        setState(() {
          _angles = AngleData(
            angleFR: buffer.asFloat64List()[0],
            angleFL: buffer.asFloat64List()[1],
            angleRR: buffer.asFloat64List()[2],
            angleRL: buffer.asFloat64List()[3],
          );
        });
      }
    } catch (e) {
      print(e);
    }
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
