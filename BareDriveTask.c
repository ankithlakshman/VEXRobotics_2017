task drive (){

	int threshold = 60;
	int highSpeed = 125;
	int stoptime = 20;
	int speedIncrement = 25;
	int speedValueLeft;
	int speedValueRight;

	//slave motors
	slaveMotor(rightDrive2, rightDrive);
	slaveMotor(leftDrive2, leftDrive);

	while(true){

		//left side
		if(vexRT[Ch3] > threshold){
			if(speedValueLeft <= highSpeed){
				speedValueLeft += speedIncrement;
				wait1Msec(stoptime);
			}
		}
		else if(vexRT[Ch3] < -threshold){
			if(speedValueLeft >= -highSpeed){
				speedValueLeft -= speedIncrement;
				wait1Msec(stoptime);
			}
		}
		else{
			speedValueLeft = 0;
		}
		motor[leftDrive] = speedValueLeft;

		//right side
		if(vexRT[Ch2] > threshold){
			if(speedValueRight <=highSpeed){
				speedValueRight += speedIncrement;
				wait1Msec(stoptime);
			}
		}
		else if(vexRT[Ch2] < -threshold){
			if(speedValueRight >= -highSpeed){
				speedValueRight -= speedIncrement;
				wait1Msec(stoptime);
			}
		}
		else{
			speedValueRight = 0;
		}
		motor[rightDrive] = speedValueRight;
	}
}
