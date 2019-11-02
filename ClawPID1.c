#pragma config(Sensor, in1,    lift,           sensorPotentiometer)
#pragma config(Sensor, in4,    clawRight,      sensorPotentiometer)
#pragma config(Sensor, in6,    clawLeft,       sensorPotentiometer)
#pragma config(Sensor, in8,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  liftLimit,      sensorTouch)
#pragma config(Motor,  port1,           rightDrive,    tmotorVex393HighSpeed_HBridge, openLoop, reversed, driveRight)
#pragma config(Motor,  port2,           rightDrive2,   tmotorVex393HighSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port3,           rightClaw,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           rightLift2,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           leftLift,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           leftLift2,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           rightLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           leftClaw,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           leftDrive2,    tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port10,          leftDrive,     tmotorVex393HighSpeed_HBridge, openLoop, driveLeft)

int clawSpeed;
int clawSet;

static float  pid_Kp = 0.3;

float rightpidError;
float rightpidDrive;

float leftpidError;
float leftpidDrive;

int errorTolerance = 450;
int mxPower = 127;

task clawSpeedTask(){
	int startValueRight = SensorValue(clawRight);
	int startValueLeft = SensorValue(clawLeft);
	wait1Msec(50);
	int rightDifference = SensorValue(clawRight) - startValueRight;
	int leftDifference = SensorValue(clawLeft) - startValueLeft;
	int ticksPerSecond = (rightDifference+leftDifference)/2*20;
	clawSpeed = ticksPerSecond;
}

task clawing(){
	int highLimit = 4000;
	int lowLimit = 400;
	int increment = 50;
	int waittime = 10;
	clawSet = lowLimit;
	while(true){
		//CLAW
		if(vexRT[Btn6U] == 1){

			if(clawSet<=(highLimit-increment)){
				clawSet+=increment;
				wait1Msec(waittime);
			}
			else{
				clawSet = clawSet;
			}
		}
		else if(vexRT[Btn6D] == 1){
			if(clawSet>=(lowLimit+increment)){
				clawSet-=increment;
				wait1Msec(waittime);
			}
			else{
				clawSet = clawSet;
			}
		}
		else{
			clawSet = clawSet;
		}
	}
}

task rightClawTask(){
	float  pidSensorCurrentValue;
	float  pidDriveTemp;
	while(true){
		// Read the sensor value and scale
		pidSensorCurrentValue = SensorValue(clawRight);

		// calculate error
		rightpidError =  clawSet - pidSensorCurrentValue;

		//tolerance
		if(abs( rightpidError)<errorTolerance){
			rightpidError = 0;
		}

		// calculate drive
		pidDriveTemp = (pid_Kp * rightpidError);

		// limit drive
		if( pidDriveTemp > mxPower )
			rightpidDrive = mxPower;
		else if( pidDriveTemp < (-mxPower) )
			rightpidDrive = (-mxPower);
		else
			rightpidDrive = pidDriveTemp;

		// send to motor
		motor(rightClaw) = rightpidDrive;

		// Don't hog cpu
		wait1Msec( 25 );
	}

}

task leftClawTask(){
	float  pidSensorCurrentValue;
	float  pidDriveTemp;
	while(true){
		// Read the sensor value and scale
		pidSensorCurrentValue = SensorValue(clawLeft);

		// calculate error
		leftpidError =  clawSet - pidSensorCurrentValue;

		//tolerance
		if(abs(leftpidError)<errorTolerance){
			leftpidError = 0;
		}

		// calculate drive
		pidDriveTemp = (pid_Kp * leftpidError);

		// limit drive
		if( pidDriveTemp > mxPower )
			leftpidDrive = mxPower;
		else if( pidDriveTemp < (-mxPower) )
			leftpidDrive = (-mxPower);
		else
			leftpidDrive = pidDriveTemp;

		// send to motor
		motor(leftClaw) = leftpidDrive;

		// Don't hog cpu
		wait1Msec( 25 );
	}
}
task main()
{
	startTask(clawing);
	startTask(rightClawTask);
	startTask(leftClawTask);
	while(true){
		continue;
	}

}
