
task Right_OneSide()
{
int masterDegree = 100;

	moveBackward(150);

	rotateLeft(100);

	closeClaw(3000);

	moveForward(50);

	motor[claw] = 80;

	moveBackward(50);

	upLift(250);

	rotateRight(100);

	specialMove(600);

	downLiftMax();


}
