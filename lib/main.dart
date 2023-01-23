import 'dart:ffi';
import 'dart:io';
import 'dart:typed_data';
import 'package:flutter/material.dart';
import 'package:ffi/ffi.dart';
import 'package:provider/provider.dart';


class AnglesModel with ChangeNotifier {
  double angleFR = 0.0;
  double angleFL = 0.0;
  double angleRR = 0.0;
  double angleRL = 0.0;

  void updateAngles(List<double> angles) {
    angleFR = angles[0];
    angleFL = angles[1];
    angleRR = angles[2];
    angleRL = angles[3];
    notifyListeners();
  }
}

class AnglesReader {
  final _pipe = File('/tmp/AnglesPipe');
  final BuildContext _context;

  AnglesReader(this._context);

  void start() {
    _pipe.openRead().listen((data) {
      final byteData = Uint8List.fromList(data).buffer;
      final doubleList = byteData.asFloat64List();
      updateAngles([doubleList[0], doubleList[1], doubleList[2], doubleList[3]]);
    });
  }

  void updateAngles(List<double> angles) {
    final anglesModel = Provider.of<AnglesModel>(_context, listen: false);
    anglesModel.updateAngles(angles);
  }
}


void main() {
  runApp(
    ChangeNotifierProvider(
      create: (context) => AnglesModel(),
      child: const MyApp(),
    ),
  );
}


class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

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
  final String title;

  const MyHomePage({Key? key, required this.title}) : super(key: key);

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  @override
  Widget build(BuildContext context) {
    final anglesModel = Provider.of<AnglesModel>(context);
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Text('AngleFR: ${anglesModel.angleFR}', style: const TextStyle(fontSize: 40)),
            Text('AngleFL: ${anglesModel.angleFL}', style: const TextStyle(fontSize: 40)),
            Text('AngleRR: ${anglesModel.angleRR}', style: const TextStyle(fontSize: 40)),
            Text('AngleRL: ${anglesModel.angleRL}', style: const TextStyle(fontSize: 40)),
          ],
        ),
      ),
    );
  }
}









