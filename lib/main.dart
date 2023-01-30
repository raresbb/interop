import 'dart:io';
import 'dart:typed_data';
import 'package:flutter/material.dart';

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
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: const MyHomePage(title: 'Flutter Demo Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  final String title;

  const MyHomePage({Key? key, required this.title}) : super(key: key);

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  late AngleData _angles;

  // initialize _angles with NaN
  _MyHomePageState() {
    _angles = AngleData(
      angleFR: double.nan,
      angleFL: double.nan,
      angleRR: double.nan,
      angleRL: double.nan,
    );
  }

  @override
  void initState() {
    super.initState();
    _readAngleData();
  }

  // read angle data from pipe
  Future<void> _readAngleData() async {
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
  }

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
          if (_angles != null)
            Text('AngleFR: ${_angles.angleFR}', style: const TextStyle(fontSize: 40)),
          if (_angles != null)
            Text('AngleFL: ${_angles.angleFL}', style: const TextStyle(fontSize: 40)),
          if (_angles != null)
            Text('AngleRR: ${_angles.angleRR}', style: const TextStyle(fontSize: 40)),
          if (_angles != null)
            Text('AngleRL: ${_angles.angleRL}', style: const TextStyle(fontSize: 40)),
        ],
      ),
    ),
  );
  }
}


/*
import 'dart:io';
import 'dart:typed_data';

class Angles {
  double angleFR;
  double angleFL;
  double angleRR;
  double angleRL;

  Angles({required this.angleFR, required this.angleFL, required this.angleRR, required this.angleRL});
}

Future<void> readAngles() async {
  var file = File('/tmp/AnglesPipe');
  var randomAccessFile = await file.open(mode: FileMode.read);
  var data = Uint8List(32);

  while (true) {
    await randomAccessFile.readInto(data);
    var buffer = data.buffer;
    var angles = Angles(
        angleFR: buffer.asFloat64List()[0],
        angleFL: buffer.asFloat64List()[1],
        angleRR: buffer.asFloat64List()[2],
        angleRL: buffer.asFloat64List()[3]);
    print('angle_FR: ${angles.angleFR}');
    print('angle_FL: ${angles.angleFL}');
    print('angle_RR: ${angles.angleRR}');
    print('angle_RL: ${angles.angleRL}');
    print('---------------');
  }
}

void main() {
  readAngles();
}
*/