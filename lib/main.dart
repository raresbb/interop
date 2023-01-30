import 'dart:io';
import 'dart:typed_data';
import 'dart:async';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'dart:convert';

int i = 1;
int counter = 0;

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
  StreamSubscription? _subscription;

  AnglesReader(this._context);

  void start() {
    int i = 1;
    try {
      _subscription = _pipe.openRead().asBroadcastStream().listen((data) {
        File('/tmp/AnglesPipe').readAsBytes().then((data) {
          final byteData = Uint8List.fromList(data);
          final doubleList = byteData.buffer.asFloat64List().sublist(0, 4);
          print(doubleList);
        });
        print('the function started was called ${i} times');
        try {
          final byteData = Uint8List.fromList(data).buffer;
          final doubleList = byteData.asFloat64List();
          print(doubleList.length);
          updateAngles([doubleList[0], doubleList[1], doubleList[2], doubleList[3]]);
          
        } catch (e) {
          print(e);
        }
        i = i + 1;
      });
    } catch (e) {
      print("Pipe not available, please restart the FLUTTER GUI");
    }
  }

  void stop() {
    _subscription?.cancel();
  }

  void updateAngles(List<double> angles) {
    final anglesModel = Provider.of<AnglesModel>(_context, listen: false);
    anglesModel.updateAngles(angles);
    // update counter 
    counter = counter + 1;
    print ('counter: ${counter}');
  }
}

void main() {
  runApp(
    ChangeNotifierProvider.value(
      value: AnglesModel(),
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
  late AnglesReader _anglesReader;
  @override
  void initState() {
    super.initState();
    _anglesReader = AnglesReader(context);
    _anglesReader.start();
  }

  @override
  void dispose() {
     _anglesReader.stop();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
        child: Consumer<AnglesModel>(
          builder: (context, anglesModel, child) {
            return Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: <Widget>[
                Text('AngleFR: ${anglesModel.angleFR}', style: const TextStyle(fontSize: 40)),
                Text('AngleFL: ${anglesModel.angleFL}', style: const TextStyle(fontSize: 40)),
                Text('AngleRR: ${anglesModel.angleRR}', style: const TextStyle(fontSize: 40)),
                Text('AngleRL: ${anglesModel.angleRL}', style: const TextStyle(fontSize: 40)),
              ],
            );
          },
        ),
      ),
    );
  }
}
