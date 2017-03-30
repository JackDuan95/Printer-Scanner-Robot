//MTE final project code
//Jack Duan, Matthew Salek, Roberto Wong, Aravinth Vijayakumar.

void soundcreation(int choice)
{
	if (choice == 1)
	{

		PlayTone(440,75);
		wait10Msec(75);
		PlayTone(293,75);
		wait10Msec(75);
		PlayTone(348,75);
		wait10Msec(75);
		wait10Msec(10);
		PlayTone(440,75);
		wait10Msec(75);
		PlayTone(293,75);
		wait10Msec(75);
		PlayTone(348,75);
		wait10Msec(75);
		wait10Msec(10);
		PlayTone(440,25);
		wait10Msec(25);
		PlayTone(524,25);
		wait10Msec(25);
		PlayTone(496,25);
		wait10Msec(25);
		wait10Msec(20);
		PlayTone(392,50);
		wait10Msec(50);
		wait10Msec(10);
		PlayTone(348,25);
		wait10Msec(25);
		PlayTone(392,25);
		wait10Msec(25);
		PlayTone(440,25);
		wait10Msec(25);
		wait10Msec(20);
		PlayTone(293,25);
		wait10Msec(25);
		wait10Msec(20);
		PlayTone(261,25);
		wait10Msec(25);
		PlayTone(329,25);
		wait10Msec(25);
		PlayTone(293,75);
		wait10Msec(75);
  }
  else
  {
	PlaySoundFile("mario_02.rso");
  }
}

void displaypercentage(int choice)
{
   eraseDisplay();
   nxtDisplayString(3, "Percent: %d", choice*4);
}

void displayscreen(int choice)
{
 if (choice == 1)
 {
   	eraseDisplay();
 		nxtDisplayString(1, "Scanning");
 }
 else if (choice==2)
 {
   eraseDisplay();
   nxtDisplayString(1,"Printing");
 }
 else
 {
   eraseDisplay();
   nxtDisplayString(1, "Completed");
 }
}

void verti_move()
{
	nMotorEncoder[motorA] = 0;
	motor[motorA] = 50;
	while (nMotorEncoder[motorA]<5);
	motor[motorA] = 0;
}

void horiz_move(int choice)
{
	if (choice==1)
	{
		SensorType[S1] = sensorTouch;
		motor[motorB]=-40;
	}
	else if (choice==0)
	{
		SensorType[S2] = sensorTouch;
		motor[motorB]=40;
	}
}

void pen(int choice)
{
	if (choice==1)//pen down
	{
	nMotorEncoder[motorC] = 0;
	motor[motorC] = -20;
	while (nMotorEncoder[motorC] > -30);
	motor[motorC] = 0;
	}
	else if(choice==0)//pen up
	{
	nMotorEncoder[motorC] = 0;
	motor[motorC] = 20;
	while (nMotorEncoder[motorC] < 30);
	motor[motorC] = 0;
	}
}

task main()
{
	soundcreation(1);
	displayscreen(1);
	int colour[25][20];
	bool penstatus=0;
	SensorType[S1] = sensorTouch;
	SensorType[S2] = sensorTouch;

	//SCANNING
	SensorType[S3]=sensorCOLORFULL;
	motor[motorB] = 40;//Brings to starting position
	while (SensorValue[S1] != 1);
	motor[motorB] = 0;

	for (int j = 0; j < 25; j++)
	{

			horiz_move(1);

			displaypercentage(j);

		for (int i=	0 ; i<20 ; i++)
		{
				colour[j][i]= SensorValue[S3];
				wait10Msec(20);

		}

		while (SensorValue[S2] == 0);
		motor[motorB] = 0;
		horiz_move(0);
		while (SensorValue[S1] == 0);
		motor[motorB] = 0;
		verti_move();
	}
	displaypercentage(25);
	while (nNxtButtonPressed==-1);//wait for button press

	//PRINTING
	displayscreen(2);
	motor[motorB] = 50;//Brings to starting postition
	while (SensorValue[S1] != 1);
	motor[motorB] = 0;

	for (int j = 0; j < 25; j++)
	{
			horiz_move(1);
			displaypercentage(j);

		for (int i=0 ; i<20 ; i++)
		{
				if (colour[j][i]<6 && penstatus==0)
				{
					motor[motorB]=0;
					pen(1);
					penstatus=1;
					horiz_move(1);
				}

				else if (colour[j][i]==6 && penstatus==1)
				{
					motor[motorB]=0;
					pen(0);
					penstatus=0;
					horiz_move(1);
				}

				else if (colour[j][i]<6 && penstatus==1);

				else if (colour[j][i]==6 && penstatus==0);

				wait10Msec(20);
		}

		while (SensorValue[S2] == 0);
		motor[motorB] = 0;

		if (penstatus==1)//moves pen up if last scan is not white
		{
			pen(0);
			penstatus=0;
		}

		horiz_move(0);
		while (SensorValue[S1] == 0);
		motor[motorB] = 0;
		verti_move();
	}
	soundcreation(0);
	displayscreen(0);
	while(nNxtButtonPressed==-1);
}
	/*int C_3 = 261;
int Csh_3 = 275;
int D_3 = 293;
int Dsh_3 = 310;
int E_3 = 329;
int F_3 = 348;
int Fsh_3 = 370;
int G_3 = 392;
int Gsh_3 = 412;
int A_3 = 440;
int Ash_3 = 466;
int B_3 = 496;
int C_4 = 524;
*/
