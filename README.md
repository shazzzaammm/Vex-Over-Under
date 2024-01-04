![4303X logo](yixes.png "yixes!!!!")

### Description

This program is the only program that 4303X is using this year. The main branch will always be the current version on our robot, and any other branch is used for testing new features without ruining our regular program (though usually we just ruin it anyways because merging isnt fun :c).

### Autons

We have a lot of autons planned for this year, but are only likely to use 2 or 3. One of them will be the gremlin (5203G) same_awp_auto, one will be a "steal" auton on the opposite side, and one will be an awp on the opposite side. The gremlin auto should score us We will also have a skills auton. The plan is to match load until we cant anymore, then push all of them into the goal (so original).

### User Control

We use a tank drive with 8 motors, 2 of which are PTO motors. The pto motors are allocated to the flywheel and the intake. Our only sensor is the inertial sensor, which is used for our chassis PID. Our lift, PTO, and wings are all powered by pneumatic pistons.

### Ports

| Subsystem  | Port(s) |
| ---------- | ------- |
| Left Side  | ?,?,?,? |
| Right Side | ?,?,?,? |
| Flywheel   | ?       |
| Intake     | ?       |
| IMU        | ?       |
| PTO        | ?       |
| Wings      | ?       |
| Lift       | ?       |

### Controls

1. T_Controls

| Button | Function        |
| ------ | --------------- |
| B      | Toggle Wings    |
| A      | Hold Flywheel   |
| X      | Toggle Flywheel |
| Y      |                 |
| UP     | Toggle Lift     |
| DOWN   |                 |
| LEFT   | Toggle Outtake  |
| RIGHT  | Toggle Intake   |
| L1     | Hold Outtake    |
| L2     | Toggle PTO      |
| R1     | Hold Intake     |
| R2     | Reverse Chassis |

2. G_Controls

| Button | Function        |
| ------ | --------------- |
| B      | Toggle Wings    |
| A      | Toggle PTO      |
| X      | Toggle Flywheel |
| Y      | Hold Flywheel   |
| UP     | Toggle Lift     |
| DOWN   | Reverse Chassis |
| LEFT   |                 |
| RIGHT  |                 |
| L1     | Toggle Intake   |
| L2     | Toggle Outtake  |
| R1     | Hold Intake     |
| R2     | Hold Outtake    |

3. K_Controls

| Button | Function        |
| ------ | --------------- |
| B      | Toggle PTO    |
| A      | Toggle Wings      |
| X      | Hold Flywheel |
| Y      | Toggle Flywheel   |
| UP     | Toggle Lift     |
| DOWN   | Reverse Chassis |
| LEFT   |                 |
| RIGHT  |                 |
| L1     | Toggle Outtake   |
| L2     | Toggle Intake  |
| R1     | Hold Outtake     |
| R2     | Hold Intake    |