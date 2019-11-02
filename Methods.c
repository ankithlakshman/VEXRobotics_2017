bool flag = false;
//autonomous methods
void resetGyro(){
	SensorValue[in8] = 0;
	wait1Msec(250);
}
void correct(){
	wait1Msec(250);
	//slave motors
	slaveMotor(rightBack, rightDrive);
	slaveMotor(leftBack, leftDrive);
	if(SensorValue[in8]>0){
		while(SensorValue[in8]>0){
			motor[leftDrive] = 90;
			motor[rightDrive] = -90;
		}
		motor[leftDrive] = 0;
		motor[rightDrive] = 0;
	}
	else if(SensorValue[in8]<0){
		while(SensorValue[in8]<0){
			motor[leftDrive] = -90;
			motor[rightDrive] = 90;
		}
		motor[leftDrive] = 0;
		motor[rightDrive] = 0;
	}

}
void moveForward(int count){
	//slave motors
	slaveMotor(rightDrive2, rightDrive);
	slaveMotor(leftDrive2, leftDrive);
	//reset encoders
	SensorValue(rightEncoder) = 0;
	SensorValue(leftEncoder) = 0;
	//keep moving until reach count
	while(SensorValue(rightEncoder)<count || SensorValue(leftEncoder)<count){
		motor[rightDrive] = 100;
		motor[leftDrive] = 100;
	}
	//brief brake to eliminate drift
	motor[rightDrive] = -5;
	motor[leftDrive] = -5;
	wait1Msec(100);
	//zero out the motors
	motor[rightDrive] = 0;
	motor[leftDrive] = 0;
}
//-----------------------------------------------------------------
void moveBackward(int count){
	//slave motors
	slaveMotor(rightBack, rightDrive);
	slaveMotor(left, leftDrive);
	//reset encoders
	SensorValue(rightEncoder) = 0;
	SensorValue(leftEncoder) = 0;
	//keep moving until reach count
	while(SensorValue(rightEncoder)>-count || SensorValue(leftEncoder)>-count){
		motor[rightDrive] = -100;
		motor[leftDrive] = -100;
	}
	//brief brake to eliminate drift
	motor[rightDrive] = 5;
	motor[leftDrive] = 5;
	wait1Msec(100);
	//zero out the motors
	motor[rightDrive] = 0;
	motor[leftDrive] = 0;
}
//-----------------------------------------------------------------
void rotateRight(int degree){
	//slave motors
	slaveMotor(rightDrive2, rightDrive);
	slaveMotor(leftDrive2, leftDrive);
	//clear the Gyro
	SensorValue[in8] = 0;
	//move motors until reach degree
	while(abs(SensorValue[in8]) < degree){
		motor[rightDrive] = -100;
		motor[leftDrive] = 100;
	}
	//Brief brake to eliminate some drift
	motor[rightDrive] = 10;
	motor[leftDrive] = -10;
	wait1Msec(100);
}
//-----------------------------------------------------------------
void rotateLeft(int degree){
	//slave motors
	slaveMotor(rightDrive2, rightDrive);
	slaveMotor(leftDrive2, leftDrive);
	//clear the Gyro
	SensorValue[in8] = 0;
	//move motors until reach degree
	while(abs(SensorValue[in8]) < degree){
		motor[rightDrive] = 100;
		motor[leftDrive] = -100;
	}
	//Brief brake to eliminate some drift
	motor[rightDrive] = -10;
	motor[leftDrive] = 10;
	wait1Msec(100);
}
//-----------------------------------------------------------------
void upLift(int count){
	//slave the motors
	slaveMotor(rightLift2, rightLift);
	slaveMotor(leftLift2, leftLift);
	while(SensorValue(lift) < count){
		motor[rightLift] = 125;
		motor[leftLift] = 125;
	}
	//brake the motors
	motor[rightLift] = 15;
	motor[leftLift] = 15;
}
//-----------------------------------------------------------------
void downLift(int count){
	//slave the motors
	slaveMotor(rightLift2, rightLift);
	slaveMotor(leftLift2, leftLift);
	//calculate the end position
	int startPosition = SensorValue(lift);
	int endPosition = startPosition-count;
	//move the motors until reach the end positon
	while(SensorValue(lift) > endPosition){
		motor[rightLift] = -127;
		motor[leftLift] = -127;
	}
	//reset the motors
	motor[rightLift] = 0;
	motor[leftLift] = 0;
}
void downLiftMax(){
	//slave the motors
	slaveMotor(rightLift2, rightLift);
	slaveMotor(leftLift2, leftLift);

		motor[rightLift] = -127;
		motor[leftLift] = -127;
		waitUntil(SensorValue(liftLimit) == 1);

	//reset the motors
	motor[rightLift] = 0;
	motor[leftLift] = 0;
}
//-----------------------------------------------------------------
void closeClaw(int position){
	//slave the motors
	slaveMotor(claw2,claw);
	//reset the motor
	motor[claw] = 0;
	//check if the claw is less than the position
	if(SensorValue(claw)< position){
		//move the claw towards the position
		while(SensorValue(claw)< position){
			motor[claw] = 127;
		}
	}
	//reset claw motor
	motor[claw] = -10;
	wait1Msec(100);
	motor[claw] = 0;
}
//-----------------------------------------------------------------
void openClaw(int count){
	//slave the motors
	slaveMotor(claw2,claw);
	//reset the motor
	motor[claw] = 0;
	//check if claw is greater than the position
	if(SensorValue(claw)> count){
		//move claw towards the position
		while(SensorValue(claw)> count){
			motor[claw] = -120;
		}
	}
	//reset the motor
	motor[claw] = 10;
	wait1Msec(100);
	motor[claw] = 0;
}
task openClawT(){
	//slave the motors
	slaveMotor(claw2,claw);

	if(SensorValue(claw)> 2800){
		//move claw towards the position
		while(SensorValue(claw)> 2800){
			motor[claw] = -120;
		}
	}
	motor[claw] = 0;
	stopTask(openClawT);
}
void brakeLift(){
	slaveMotor(rightLift2, rightLift);
	slaveMotor(leftLift2, leftLift);
	motor[rightLift] = -20;
	motor[leftLift] = -20;
}
void launch(){
	//slave motors
	slaveMotor(rightLift2, rightLift);
	slaveMotor(leftLift2, leftLift);
	//680
	motor[rightLift] = 127;
	motor[leftLift] = 127;
	motor[claw] = 50;
	waitUntil(SensorValue(lift)>800);
	motor[claw] = 0;
	//check if claw is greater than the position
	startTask(openClawT);
	waitUntil(SensorValue(lift)>1300);
	motor[rightLift] = 0;
	motor[leftLift] = 0;
	wait1Msec(250);
}
task launchT(){
	flag = false;
	//slave motors
	slaveMotor(rightLift2, rightLift);
	slaveMotor(leftLift2, leftLift);
	//680
	motor[rightLift] = 127;
	motor[leftLift] = 127;
	motor[claw] = 50;
	waitUntil(SensorValue(lift)>800);
	motor[claw] = 0;
	//check if claw is greater than the position
	startTask(openClawT);
	waitUntil(SensorValue(lift)>1300);
	motor[rightLift] = 0;
	motor[leftLift] = 0;
	wait1Msec(250);
	flag = true;
}
void specialMove(int count){
	slaveMotor(rightDrive2, rightDrive);
	slaveMotor(leftDrive2, leftDrive);
	//reset encoders
	SensorValue(rightEncoder) = 0;
	SensorValue(leftEncoder) = 0;

	motor[rightDrive] = -100;
	motor[leftDrive] = -100;

	if(count>500){
		int index = -(count-500);
		waitUntil(SensorValue(rightEncoder)<index || SensorValue(leftEncoder)<index);
		startTask(launchT);
	}
	else{
		startTask(launchT);
	}



	waitUntil(SensorValue(rightEncoder)<-count || SensorValue(leftEncoder)<-count);

	motor[rightDrive] = 0;
	motor[leftDrive] = 0;
	waitUntil(flag);
}
