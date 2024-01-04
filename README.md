![4303X logo](yixes.png "yixes!!!!")

### Description

This program is the only program that 4303X is using this year. The main branch will always be the current version on our robot, and any other branch is used for testing new features without ruining our regular program (though usually we just ruin it anyways because merging isnt fun :c).

### Autons

We have a lot of autons planned for this year. We are only likely to use four in matches. Two for elimination matches and two for qualification matches. The goal of the qual autons are to get the AWP, and the goal of the elim autons are to get as many points as possible while preventing the enemy alliance from getting as many themselves. We will also have a skills auton. The plan is to match load until we cant anymore, then push all of them into the goal (so original).

### User Control

We use a tank drive with 8 motors, 2 of which are PTO motors. The pto motors are allocated to the flywheel and the intake. Our only sensor is the inertial sensor, which is used for our chassis PID. Our lift, PTO, and wings are all powered by pneumatic pistons.

### Ports

| Subsystem  | Port(s)         |
| ---------- | --------------- |
| Left Side  | 9, -10, -12, 11 |
| Right Side | -5, 4, 3, 2     |
| Flywheel   | 2               |
| Intake     | 11              |
| IMU        | 7               |
| PTO        | ?               |
| Wings      | ?               |
| Lift       | ?               |

### Controls

1. T_Controls

   - B = Toggle Wings
   - A = Hold Flywheel
   - X = Toggle Flywheel
   - Y =
   - UP = Toggle Lift
   - DOWN =
   - LEFT = Toggle Outtake
   - RIGHT = Toggle Intake
   - L1 = Hold Outtake
   - L2 = Toggle PTO
   - R1 = Hold Intake
   - R2 = Reverse Chassis

2. G_Controls

   - B = Toggle Wings
   - A = Toggle PTO
   - X = Toggle Flywheel
   - Y = Hold Flywheel
   - UP = Toggle Lift
   - DOWN = Reverse Chassis
   - LEFT =
   - RIGHT =
   - L1 = Toggle Intake
   - L2 = Toggle Outtake
   - R1 = Hold Intake
   - R2 = Hold Outtake

3. K_Controls
   - B = Toggle PTO
   - A = Toggle Wings
   - X = Hold Flywheel
   - Y = Toggle Flywheel
   - UP = Toggle Lift
   - DOWN = Reverse Chassis
   - LEFT =
   - RIGHT =
   - L1 = Toggle Outtake
   - L2 = Toggle Intake
   - R1 = Hold Outtake
   - R2 = Hold Intake
