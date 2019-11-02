task left_center(){

	int masterDegree = 500;


	moveForward(300);
	//set the claw
	closeClaw(3000);
	motor[claw]  = 80;

	upLift(400);

	moveForward(100);

	rotateRight(masterDegree);

	resetGyro();

	specialMove(500);

	wait1Msec(250);

	downLiftMax();

	wait1Msec(250);

	correct();

	openClaw(2000);

	moveForward(300);
	//set the claw
	closeClaw(3200);
	motor[claw]  = 75;

	moveBackward(100);

	upLift(300);

	specialMove(650);

	downLiftMax();
}
