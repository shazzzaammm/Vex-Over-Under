### Description
This program is the only program that 4303X is using this year. The main branch will always be the current version on our robot, and any other branch is used for testing new features without ruining our regular program.

### Autons
We have a lot of autons planned for this year. We are only likely to use four in matches. Two for elimination matches and two for qualification matches. The goal of the qual autons are to get the AWP, and the goal of the elim autons are to get as many points as possible while preventing the enemy alliance from getting as many themselves. We will also have a skills auton. The plan is to match load until we cant anymore, then push all of them into the goal. 

### User Control
We use a tank drive with 8 motors, 2 of which are PTO motors. The pto motors are allocated to the catapult and the intake. We have 3 total sensors, rotation, optic, and inertial. The rotation sensor is used to automatically charge the catapult. The optic sensor is used to automatically shoot the catapult when there is a triball loaded. The inertial sensor is used for our chassis PID.

### Ports
Left Side = (1, -2, -4, 10),
Right Side = (3, 5, -6, -9),
Catapult = -9,
Intake = 10,
IMU = 21,
Rotation Sensor = 11,
Optic Sensor = 19,
PTO Piston = H,
Wing Pistons = A + B

### Controls

#### T_Controls
B = Toggle Wings
A = Shoot Catapult
X = Toggle Auto Shooting Catapult
Y = 
UP = 
DOWN = 
LEFT = Toggle Outtake
RIGHT = Toggle Intake
L1 = Hold Outtake
L2 = Toggle PTO
R1 = Hold Intake
R2 = Reverse Chassis

#### G_Controls
B = Toggle Wings
A = Toggle PTO
X = Toggle Auto Shooting Catapult
Y = Shoot Catapult
UP = 
DOWN = Reverse Chassis
LEFT = 
RIGHT = 
L1 = Toggle Intake
L2 = Toggle Outtake
R1 = Hold Intake
R2 = Hold Outtake

#### K_Controls
B = Toggle PTO
A = Toggle Wings
X = Shoot Catapult
Y = Toggle Auto Shooting Catapult
UP = 
DOWN = Reverse Chassis
LEFT = 
RIGHT = 
L1 = Toggle Outtake
L2 = Toggle Intake
R1 = Hold Outtake
R2 = Hold Intake