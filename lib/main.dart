import 'dart:ffi';
import 'dart:io';
import 'package:flutter/material.dart';
import 'package:ffi/ffi.dart';
import 'package:provider/provider.dart';


class FFIBridge {
    final _startUpdates = DynamicLibrary.open(
      Platform.isWindows ? 'api.dll' : 'libapi.so').
        lookupFunction<Void Function(Pointer<NativeFunction<Void Function(Double, Double, Double, Double)>>), 
      void Function(Pointer<NativeFunction<Void Function(Double, Double, Double, Double)>>)>('startUpdates');

  final _stopAngles = DynamicLibrary.open(
    Platform.isWindows ? 'api.dll' : 'libapi.so').
      lookupFunction<Void Function(), void Function()>('stopUpdates');

  void startUpdates(BuildContext context) {
    final _callback = Pointer.fromFunction<Void Function(Double, Double, Double, Double)>(callback, context);
    _startUpdates(_callback);
  }

  void stopUpdates() {
    _stopAngles();
  }
  void callback(double angleFR, double angleFL, double angleRR, double angleRL, BuildContext context) {
    final anglesModel = Provider.of<AnglesModel>(context, listen: false);
    anglesModel.updateAngles([angleFR, angleFL, angleRR, angleRL]);
  }
  
}


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

void main() {
  final ffiBridge = FFIBridge();
  ffiBridge.startUpdates(context);
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









