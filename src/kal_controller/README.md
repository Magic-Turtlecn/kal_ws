# KAL CONTROLLER

Simple controller implementation for the Kognitive Automobile Labor

## How does it work?

This package implements the lateral controller introduced in [Verhaltensgenerierung für Fahrzeuge](https://www.mrt.kit.edu/lehre_WS_Verhaltensgenerierung_Fahrzeuge.php).
See the lecture slides for details on how this controller works.

For longitudinal control, the controller will simply return the speed implied by the time stamps of the given trajectory.

## Usage

Instantiate the Controller class and define the controller parameters using `setParameters`.
Get a control command (speed + steering angle) using the `getControlCommand` function.

Check the unit tests for exemplary usage.