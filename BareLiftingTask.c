int clawSpeed;
task clawSpeedTask(){
	while(true){
		int startPosition = SensorValue(claw);
		wait1Msec(50);
		int difference = SensorValue(claw) - startPosition;
		clawSpeed = difference*20;
	}
}
task lifting(){
	// set the speeds
	int liftSpeed = 125;
	int brakeSpeed = 20;
	//slave the motors
	slaveMotor(rightLift2, rightLift);
	slaveMotor(leftLift2, leftLift);
	//set the claw speed
	int clawSpeed = 125;
	//slave the motors
	slaveMotor(claw2,claw);

	//limits
	int highLimit = 2200;
	int lowLimit = 0;
	int midPoint = 1700;


	//while loop
	while(true){
		//UP CONDITION
		if(vexRT[Btn5U] == 1){
			if(SensorValue(lift) < highLimit){
				motor[rightLift] = liftSpeed;
				motor[leftLift] = liftSpeed;
			}
		}
		//DOWN CONDITION
		else if(vexRT[Btn5D] == 1){
			if(SensorValue(liftLimit) == 0){
				motor[rightLift] = -liftSpeed;
				motor[leftLift] = -liftSpeed;
			}
			else{
				motor[rightLift] = 0;
				motor[leftLift] = 0;
			}
		}
		//BRAKE CONDITION
		else{
			//IF THE SWITCH IS TRIGGERED = TURN OFF MOTORS AND RESET LIFT POTENTIOMETER
			if(SensorValue(liftLimit) == 1){
				motor[rightLift] = 0;
				motor[leftLift] = 0;
				SensorValue(lift) = 0;
			}
			//IF LESS THAN MIDPOINT
			else if(SensorValue(lift)>lowLimit && SensorValue(lift)<midPoint){
				//SET THE BRAKE
				motor[rightLift] = brakeSpeed;
				motor[leftLift] = brakeSpeed;

			}
			//IF GREATER THAN MIDPOINT
			else if(SensorValue(lift)>lowLimit && SensorValue(lift)>midPoint){
				//SET REVERSE-HALF BRAKE
				motor[rightLift] = -brakeSpeed/2;
				motor[leftLift] = -brakeSpeed/2;
			}
		}

		//LAUNCHING
		if(vexRT[Btn8D] == 1){
			motor[rightLift] = 127;
			motor[leftLift] = 127;
			motor[claw] = 50;
			waitUntil(SensorValue(lift)>800);
			motor[claw] = 0;
			//check if claw is greater than the position
			startTask(openClawT);
			//reset the motor
			motor[claw] = 10;
			wait1Msec(100);
			motor[claw] = 0;
			waitUntil(SensorValue(lift)>1200);
			motor[rightLift] = 0;
			motor[leftLift] = 0;
		}

		int requiredSpeed = 50;
		//CLAW
		if(vexRT[Btn6U] == 1){
			if(clawSpeed>requiredSpeed){
				motor[claw] = clawSpeed;
			}
			else{
				motor[claw] = clawSpeed-45;
			}
		}
		else if(vexRT[Btn6D] == 1){
			motor[claw] = -clawSpeed;
		}
		else{
			motor[claw] = 5;
		}

	}
}
