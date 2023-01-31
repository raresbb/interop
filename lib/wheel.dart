import 'package:flutter/material.dart';
import 'dart:math';

class Wheel extends StatefulWidget {
  final double angle;
  final bool frontAxis;
  final double gaugeMargin;

  const Wheel({
    Key? key,
    required this.angle,
    this.frontAxis = true,
    this.gaugeMargin = 10,
  }) : super(key: key);
  @override
  State<Wheel> createState() => _WheelState();
}

class _WheelState extends State<Wheel> {
  @override
  Widget build(BuildContext context) {
    return SizedBox(
      width: 80,
      height: 200,
      child: Stack(
        children: [
          // image of the tire
          Positioned(
            left: 0,
            bottom: widget.frontAxis ? 0 : 100,
            width: 40,
            height: 100,
            child: Transform.rotate(
              angle: -widget.angle,
              child: Image.asset('images/tire.png'),
            ),
          ),
          // reference line
          Positioned(
            left: 18.5,
            bottom: widget.frontAxis 
                ? widget.gaugeMargin + 100
                : widget.gaugeMargin + 30,
            child: Container(
              width: 3,
              height: 50,
              color: Colors.black,
            ),
          ),
          // angle line
          Positioned(
            bottom: widget.frontAxis
                ? widget.gaugeMargin + 100
                : widget.gaugeMargin + 30,
            left: 18.5,
            child: Transform.rotate(
              angle: -widget.angle,
              origin: widget.frontAxis 
                  ? Offset(1.5, 50 + widget.gaugeMargin + 50 / 2)
                  : Offset(1.5, -(50 + widget.gaugeMargin + 50 / 2)),
              child: Container(
                width: 3,
                height: 50,
                color: Colors.black,
              ),
            ),
          ),
          // arc
          Positioned(
            left: 18.5,
            bottom: widget.frontAxis
                ? widget.gaugeMargin + 120  
                : widget.gaugeMargin + 120,
            child: CustomPaint(
              painter: GaugePainter(
                angle: widget.angle,
                gaugeMargin: widget.gaugeMargin,
                frontAxis: widget.frontAxis,
              ),
            ),
          ),
          // label
          Positioned(
            bottom: widget.frontAxis
                ? widget.gaugeMargin + 160
                : widget.gaugeMargin + 0,
            left: 0,
            child: SizedBox(
              width: 60,
              height: 20,
              child: Text(
                '${(widget.angle * 180 / pi * 10).round() / 10}°',
                style: const TextStyle(
                  color: Colors.black,
                  fontSize: 20,
                ),
              ),
            ),
          ),
        ],
      ),
    );
  }
}

class GaugePainter extends CustomPainter {
  final double angle;
  final double gaugeMargin;
  final bool frontAxis;

  GaugePainter({
    required this.angle,
    required this.gaugeMargin,
    this.frontAxis = true,
  });

  @override
  void paint(Canvas canvas, Size size) {
    final paint = Paint()
      ..color = Colors.red
      ..strokeWidth = 10
      ..strokeCap = StrokeCap.butt
      ..style = PaintingStyle.stroke;

    var circleRadius = 50 + gaugeMargin + 50 / 2;
    var rect = frontAxis
                ? Rect.fromLTWH(-85, -5, 2*circleRadius, 2*circleRadius)
                : Rect.fromLTWH(-85, -105, 2*circleRadius, 2*circleRadius);
    double startAngle = frontAxis ? -90 * pi / 180 : 90 * pi / 180;
    double sweepAngle = -angle;

    
    canvas.drawArc(rect, startAngle, sweepAngle, false, paint);
  }

  @override
  bool shouldRepaint(CustomPainter oldDelegate) {
    return true;
  }
}
