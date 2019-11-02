task left_3stars(){
		closeClaw(2800);

		rotateRight(350);

		moveForward(600);

		closeClaw(3400);
		motor[claw] = 50;

		wait1Msec(500);

		upLift(400);

		moveBackward(700);

		wait1Msec(250);

		rotateRight(350);

		wait1Msec(250);

		specialMove(1000);

		downLiftMax();
}
