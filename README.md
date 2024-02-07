![4303X logo](yixes.png "yixes!!!!")

### Description

This program is the only program that 4303X is using this year. The main branch will always be the current version on our robot, and any other branch is used for testing new features without ruining our regular program (though usually we just ruin it anyways because merging isnt fun :c).

### Autons

We have multiple autons in the works, but we are only likely to end up using two or three in matches. We will have a far side 6 ball auton (similar to korvex), a close side 1 ball awp that ends with us touching the endgame bar (similar to exobits), and a close side bowl setup auton that lets us bowl three or four triballs as soon as matches start (similar to hope robotics). We will also have a skills auton. The plan is to match load until we cant anymore, push them all in the goal, and hang (like robokauz).

### User Control

We use a tank drive with 8 motors, 2 of which are PTO motors. The pto motors are allocated to the slapper and the intake. We have three sensors, each one used very often. Our inertial sensor is used for our chassis pid, our optic sensor is used to automatically detect triballs when we are match loading, and our rotation sensor ensures that our slapper is always charged and ready to shoot. Our endgame, PTO, and wings are all powered by pneumatic pistons.

### Ports

| Subsystem  | Port(s)          |
| ---------- | ---------------- |
| Left Side  | 7, 8, -2, 1      |
| Right Side | -18, 17, 20, -19 |
| Slapper    | -19              |
| Intake     | 1                |
| IMU        | 16               |
| Optic      | 5                |
| Rotation   | 10               |
| PTO        | B                |
| Wings      | A                |
| Endgame    | C                |

### Controls

- T_Controls

  | Function        | Button(s)         |
  | --------------- | ----------------- |
  | Hold Intake     | R1                |
  | Hold Outtake    | L1                |
  | Toggle Intake   | RIGHT             |
  | Toggle Outtake  | LEFT              |
  | Toggle Wings    | B                 |
  | Toggle PTO      | R2                |
  | Toggle Slapper  | X                 |
  | Hold Slapper    | A                 |
  | Reverse Chassis | L2                |
  | Toggle Endgame  | R1 + R2 + L1 + L2 |

- G_Controls

  | Function        | Button(s)         |
  | --------------- | ----------------- |
  | Hold Intake     | L1                |
  | Hold Outtake    | L2                |
  | Toggle Intake   | R1                |
  | Toggle Outtake  | R2                |
  | Toggle Wings    | A                 |
  | Toggle PTO      | B                 |
  | Toggle Slapper  | X                 |
  | Hold Slapper    | Y                 |
  | Reverse Chassis | DOWN              |
  | Toggle Endgame  | R1 + R2 + L1 + L2 |

- K_Controls

  | Function        | Button(s)         |
  | --------------- | ----------------- |
  | Hold Intake     | R2                |
  | Hold Outtake    | R1                |
  | Toggle Intake   | L2                |
  | Toggle Outtake  | L1                |
  | Toggle Wings    | B                 |
  | Toggle PTO      | A                 |
  | Toggle Slapper  | Y                 |
  | Hold Slapper    | X                 |
  | Reverse Chassis | DOWN              |
  | Toggle Endgame  | R1 + R2 + L1 + L2 |

- A_Controls

  | Function        | Button(s)         |
  | --------------- | ----------------- |
  | Hold Intake     | LEFT              |
  | Hold Outtake    | RIGHT             |
  | Toggle Intake   | R2                |
  | Toggle Outtake  | R1                |
  | Toggle Wings    | L2 or L1          |
  | Toggle PTO      | A                 |
  | Toggle Slapper  | X                 |
  | Hold Slapper    | Y                 |
  | Reverse Chassis | DOWN              |
  | Toggle Endgame  | R1 + R2 + L1 + L2 |
