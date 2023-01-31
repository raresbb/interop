import 'package:flutter/material.dart';
import 'package:angle_visualizer/wheel.dart';

class VehicleFrame extends StatelessWidget {
  final double angleFL;
  final double angleFR;
  final double angleRL;
  final double angleRR;

  static const double vehicleXMargin = 100;
  static const double vehicleYMargin = 100;
  static const double vehicleWidth = 200;

  const VehicleFrame({
    Key? key,
    required this.angleFL,
    required this.angleFR,
    required this.angleRL,
    required this.angleRR,
  }) : super(key: key);


  @override
  Widget build(BuildContext context) {
    return LayoutBuilder(
      builder: (context, constraints) {
        // Calculate the dimensions of the VehicleFrame widget based on the constraints provided by the LayoutBuilder
        final double width = constraints.maxWidth;
        final double height = constraints.maxHeight;
        final double middlePoint = constraints.maxWidth / 2;

        return Container(
          width: width,
          height: height,
          color: Colors.white,
          child: Stack(
            children: [
              Positioned(
                top: vehicleYMargin,
                left: vehicleXMargin,
                child: Wheel(
                  key: const Key('fl'),
                  angle: angleFL,
                ),
              ),
              Positioned(
                top: vehicleYMargin,
                right: vehicleXMargin,
                child: Wheel(
                  key: const Key('fr'),
                  angle: angleFR,
                ),
              ),
              Positioned(
                bottom: vehicleYMargin,
                left: vehicleXMargin,
                child: Wheel(
                  key: const Key('rl'),
                  angle: angleRL,
                  frontAxis: false,
                ),
              ),
              Positioned(
                bottom: vehicleYMargin,
                right: vehicleXMargin,
                child: Wheel(
                  key: const Key('rr'),
                  angle: angleRR,
                  frontAxis: false,
                ),
              ),
              // front axles
              Positioned(
                top: vehicleYMargin + 150,
                left: vehicleXMargin + 40,
                right: vehicleXMargin + 80,
                child: Container(
                  height: 8,
                  decoration: BoxDecoration(
                    color: Colors.black,
                    borderRadius: BorderRadius.circular(4),
                  ),
                ),
              ),
              // rear axles
              Positioned(
                bottom: vehicleYMargin + 150,
                left: vehicleXMargin + 40,
                right: vehicleXMargin + 80,
                child: Container(
                  height: 8,
                  decoration: BoxDecoration(
                    color: Colors.black,
                    borderRadius: BorderRadius.circular(4),
                  ),
                ),
              ),
              // center line
              Positioned(
                top: vehicleYMargin + 150,
                bottom: vehicleYMargin + 150,
                left: middlePoint,
                child: Container(
                  width: 8,
                  color: Colors.black,
                ),
              ),
            ],
          ),
        );
      },
    );
  }
}