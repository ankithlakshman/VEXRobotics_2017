
task Pskills()
{
//START PROGRAMMING
	moveBackward(300);
	closeClaw(3000);
	motor[claw] = 80;
	upLift(400);
	specialMove(600);
	downLiftMax();
	wait1Msec(300);

	moveForward(800);
	closeClaw(3000);
	motor[claw] = 80;
	upLift(400);
	specialMove(800);
	downLiftMax();
	wait1Msec(300);

	moveForward(800);
	closeClaw(3000);
	motor[claw] = 80;
	upLift(400);
	specialMove(800);
	downLiftMax();

	wait1Msec(500);

	closeClaw(3000);
	moveForward(100);
	rotateRight(370);
	moveForward(2000);
	closeClaw(3100);
	motor[claw] = 50;
	wait1Msec(250);
	upLift(400);
	moveBackward(150);
	rotateLeft(370);
	specialMove(50);

	downLiftMax();
	moveForward(100);
	motor[rightDrive] = -100;
	motor[leftDrive] = -100;
	wait1Msec(250);
	motor[rightDrive] = 0;
	motor[leftDrive] = 0;
	wait1Msec(1000);

	moveForward(800);
	closeClaw(3000);
	motor[claw] = 80;
	upLift(400);
	specialMove(800);
	downLiftMax();

	moveForward(650);
	rotateLeft(370);
	moveForward(500);
	closeClaw(3000);
	motor[claw]  = 80;
	upLift(400);
	moveForward(300);
	rotateRight(370);
	specialMove(500);
	wait1Msec(250);
	downLiftMax();
	openClaw(2000);
	moveForward(900);
	closeClaw(3000);
	motor[claw]  = 75;
	moveBackward(100);
	upLift(300);
	specialMove(750);
	downLiftMax();
}
