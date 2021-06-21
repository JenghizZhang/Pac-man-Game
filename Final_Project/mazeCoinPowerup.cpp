/*
Description:
This program is the implementation file of the header file mazeCoinPowerup. It implements four public functions
1. draw the maze, coins, and power up 2. check the coin eaten by pacman 3. check the power up eaten by pacman 4.
check whether all coins and power ups are eaten by the pacman (win the game).
*/
#include <GL/glut.h>
#include "mazeCoinPowerup.h"

//draw the maze, coins, and power up. mazeNum is for changing the maze.Here it should be 1 beacuse I only specified one maze information. We can add a new maze then use mazeNum = 2 to change the maze.
void mazeCoinPowerup::draw(int mazeNum)
{
	switch (mazeNum) //mazeNum is for changing the maze. Here it should be 1 beacuse I only specified one maze information. We can add a new maze then use mazeNum = 2 to change the maze.
	{
	case 1:
		glColor3f(0.0, 0.0, 1.0); //set the color to blue
		for (int i = 0; i < 30; ++i) //draw the cylinder along z axis
		{
			glPushMatrix();
				glTranslatef((float)zCylinderNum1[i][0], 0.0f, (float)zCylinderNum1[i][1]);//translate to the correct position

				glPushMatrix();
					glTranslatef(0.0f, 0.0f, (float)zCylinderNum1[i][2]);//translate to the correct position
					glutSolidSphere(0.1, 20, 20); //draw the sphere for smooth connection
				glPopMatrix();

				glPushMatrix();
					glutSolidSphere(0.1, 20, 20); //draw the sphere for smooth connection
				glPopMatrix();

				gluCylinder(quardratic, 0.1, 0.1, zCylinderNum1[i][2], 40, 40);//draw the cylinder based on the data
			glPopMatrix();
		}
		for (int j = 0; j < 34; ++j)//draw the cylinder along x axis
		{
			glPushMatrix();
				glTranslatef((float)xCylinderNum1[j][0], 0, (float)xCylinderNum1[j][1]);//translate to the correct position
				glRotatef(90, 0, 1, 0);//rotate along the y axis

				glPushMatrix();
					glTranslatef(0.0f, 0.0f, (float)xCylinderNum1[j][2]);//translate to the correct position
					glutSolidSphere(0.1, 20, 20);//draw the sphere for smooth connection
				glPopMatrix();

				glPushMatrix();
					glutSolidSphere(0.1, 20, 20);//draw the sphere for smooth connection
				glPopMatrix();

				gluCylinder(quardratic, 0.1, 0.1, xCylinderNum1[j][2], 32, 32);//draw the cylinder based on the data
			glPopMatrix();
		}
		for (int m = 0; m < 2; ++m) //draw the door
		{
			glPushMatrix();
				glTranslatef(xDoor[m][0], 0, xDoor[m][1]);//translate to the correct position
				glRotatef(90, 0, 1, 0);//rotate along the y axis

				glPushMatrix();
					glTranslatef(0, 0, xDoor[m][2]);//translate to the correct position
					glutSolidSphere(0.1, 20, 20);//draw the sphere for smooth connection
				glPopMatrix();

				glPushMatrix();
					glutSolidSphere(0.1, 20, 20);//draw the sphere for smooth connection
				glPopMatrix();

			gluCylinder(quardratic, 0.1, 0.1, xDoor[m][2], 32, 32);//draw the cylinder based on the data
			glPopMatrix();
		}
		//draw the three dots at the door
		glPushMatrix();
			glTranslatef(-0.3f, 0.0f, -2.0f);//translate to the correct position
			glutSolidSphere(0.1, 20, 20);//draw the sphere based on the data
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.3f, 0.0f, -2.0f);//translate to the correct position
			glutSolidSphere(0.1, 20, 20);//draw the sphere based on the data
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0f, 0.0f, -2.0f);//translate to the correct position
			glutSolidSphere(0.1, 20, 20);//draw the sphere based on the data
		glPopMatrix();


		glColor3f(192.0f / 255.0f, 192.0f / 255.0f, 192.0f / 255.0f);//set the color to silver
		for (int k = 0; k < 152; ++k) //draw the coins
		{
			if (coinPosNum1[k][2] != 0) // if the coin has not been eaten
			{
				glPushMatrix();
					glTranslatef((float)coinPosNum1[k][0], 0.05f, (float)coinPosNum1[k][1]);//translate to the correct position
					glutSolidSphere(0.1, 20, 20);//draw the sphere based on the data
				glPopMatrix();
			}
		}
		
		glColor3f(160.0f / 255.0f, 160.0f / 255.0f, 30.0f / 255.0f);//set the color to gold
		for (int l = 0; l < 4; ++l) //draw the power up
		{
			if (powerPosNum1[l][2] != 0) // if the power up has not been eaten
			{
				glPushMatrix();
					glTranslatef((float)powerPosNum1[l][0], 0.05f, (float)powerPosNum1[l][1]);
					glRotatef(90, 1, 0, 0);//rotate it along x axis
					glScalef(1.0f, 1.0f, 0.1f);//scale the sphere
					glutSolidSphere(0.25, 30, 30);//instead of using 2-D disk, it is better to use 3-D sphere and scale it to get better performance
					//gluDisk(quardratic, 0, 2.5, 50, 50); 
				glPopMatrix();
			}
		}
		break;
	default:
		break;
	}
}
//check whether all coins and power up are eaten.If yes, return 1.
bool mazeCoinPowerup::checkWin()
{
	int sumNum = 0;
	for (int i = 0; i < 4; ++i) //check all the power up
	{
		sumNum += powerPosNum1[i][2]; //if it is eaten, the value should be 0
	}
	for (int j = 0; j < 152; ++j) //check all the coins
	{
		sumNum += coinPosNum1[j][2]; //if it is eaten, the value should be 0
	}
	if (sumNum == 0)
	{
		return 1; //all the coins and power up are eaten
	}
	else
	{
		return 0;
	}
}
//check the state (eaten or not) of all coins. If it is eaten, set its value to 0. Input x and z is the coordinate of the pacman
void mazeCoinPowerup::checkCoin(float xPos, float zPos)
{
	//set the coordinate of pacman as integer.
	int x = (int)xPos;
	int z = (int)zPos;
	//check the state of the coin. search the z axis and then searh the x axis to check each the coin state.
	switch (z) 
	{
	case -10:
		switch (x) 
		{
		case -8:
			this->coinPosNum1[0][2] = 0;
			break;
		case -7:
			this->coinPosNum1[1][2] = 0;
			break;
		case -6:
			this->coinPosNum1[2][2] = 0;
			break;
		case -5:
			this->coinPosNum1[3][2] = 0;
			break;
		case -4:
			this->coinPosNum1[4][2] = 0;
			break;
		case -3:
			this->coinPosNum1[5][2] = 0;
			break;
		case -2:
			this->coinPosNum1[6][2] = 0;
			break;
		case -1:
			this->coinPosNum1[7][2] = 0;
			break;
		case 1:
			this->coinPosNum1[8][2] = 0;
			break;
		case 2:
			this->coinPosNum1[9][2] = 0;
			break;
		case 3:
			this->coinPosNum1[10][2] = 0;
			break;
		case 4:
			this->coinPosNum1[11][2] = 0;
			break;
		case 5:
			this->coinPosNum1[12][2] = 0;
			break;
		case 6:
			this->coinPosNum1[13][2] = 0;
			break;
		case 7:
			this->coinPosNum1[14][2] = 0;
			break;
		case 8:
			this->coinPosNum1[15][2] = 0;
			break;
		}
		break;
	case -9:
		switch (x)
		{
		case -5:
			this->coinPosNum1[16][2] = 0;
			break;
		case -1:
			this->coinPosNum1[17][2] = 0;
			break;
		case 1:
			this->coinPosNum1[18][2] = 0;
			break;
		case 5:
			this->coinPosNum1[19][2] = 0;
			break;
		}
		break;
	case -8:
		switch (x) 
		{
		case -8:
			this->coinPosNum1[20][2] = 0;
			break;
		case -5:
			this->coinPosNum1[21][2] = 0;
			break;
		case -1:
			this->coinPosNum1[22][2] = 0;
			break;
		case 1:
			this->coinPosNum1[23][2] = 0;
			break;
		case 5:
			this->coinPosNum1[24][2] = 0;
			break;
		case 8:
			this->coinPosNum1[25][2] = 0;
			break;
		}
		break;
	case -7:
		switch (x) 
		{
		case -8:
			this->coinPosNum1[26][2] = 0;
			break;
		case -7:
			this->coinPosNum1[27][2] = 0;
			break;
		case -6:
			this->coinPosNum1[28][2] = 0;
			break;
		case -5:
			this->coinPosNum1[29][2] = 0;
			break;
		case -4:
			this->coinPosNum1[30][2] = 0;
			break;
		case -3:
			this->coinPosNum1[31][2] = 0;
			break;
		case -2:
			this->coinPosNum1[32][2] = 0;
			break;
		case -1:
			this->coinPosNum1[33][2] = 0;
			break;
		case 0:
			this->coinPosNum1[34][2] = 0;
		case 1:
			this->coinPosNum1[35][2] = 0;
			break;
		case 2:
			this->coinPosNum1[36][2] = 0;
			break;
		case 3:
			this->coinPosNum1[37][2] = 0;
			break;
		case 4:
			this->coinPosNum1[38][2] = 0;
			break;
		case 5:
			this->coinPosNum1[39][2] = 0;
			break;
		case 6:
			this->coinPosNum1[40][2] = 0;
			break;
		case 7:
			this->coinPosNum1[41][2] = 0;
			break;
		case 8:
			this->coinPosNum1[42][2] = 0;
			break;
		}
		break;
	case -6:
		switch (x) 
		{
		case -8:
			this->coinPosNum1[43][2] = 0;
			break;
		case -5:
			this->coinPosNum1[44][2] = 0;
			break;
		case -3:
			this->coinPosNum1[45][2] = 0;
			break;
		case 3:
			this->coinPosNum1[46][2] = 0;
			break;
		case 5:
			this->coinPosNum1[47][2] = 0;
			break;
		case 8:
			this->coinPosNum1[48][2] = 0;
			break;
		}
		break;
	case -5:
		switch (x)
		{
		case -8:
			this->coinPosNum1[49][2] = 0;
			break;
		case -7:
			this->coinPosNum1[50][2] = 0;
			break;
		case -6:
			this->coinPosNum1[51][2] = 0;
			break;
		case -5:
			this->coinPosNum1[52][2] = 0;
			break;
		case -3:
			this->coinPosNum1[53][2] = 0;
			break;
		case -2:
			this->coinPosNum1[54][2] = 0;
			break;
		case -1:
			this->coinPosNum1[55][2] = 0;
			break;
		case 1:
			this->coinPosNum1[56][2] = 0;
			break;
		case 2:
			this->coinPosNum1[57][2] = 0;
			break;
		case 3:
			this->coinPosNum1[58][2] = 0;
			break;
		case 5:
			this->coinPosNum1[59][2] = 0;
			break;
		case 6:
			this->coinPosNum1[60][2] = 0;
			break;
		case 7:
			this->coinPosNum1[61][2] = 0;
			break;
		case 8:
			this->coinPosNum1[62][2] = 0;
			break;
		}
		break;
	case -4:
		switch (x)
		{
		case -5:
			this->coinPosNum1[63][2] = 0;
			break;
		case 5:
			this->coinPosNum1[64][2] = 0;
			break;
		}
		break;
	case -3:
		switch (x)
		{
		case -5:
			this->coinPosNum1[65][2] = 0;
			break;
		case 5:
			this->coinPosNum1[66][2] = 0;
			break;
		}
		break;
	case -2:
		switch (x)
		{
		case -5:
			this->coinPosNum1[67][2] = 0;
			break;
		case 5:
			this->coinPosNum1[68][2] = 0;
			break;
		}
		break;
	case -1:
		switch (x)
		{
		case -5:
			this->coinPosNum1[69][2] = 0;
			break;
		case 5:
			this->coinPosNum1[70][2] = 0;
			break;
		}
		break;
	case 0:
		switch (x)
		{
		case -5:
			this->coinPosNum1[71][2] = 0;
			break;
		case 5:
			this->coinPosNum1[72][2] = 0;
			break;
		}
		break;
	case 1:
		switch (x)
		{
		case -5:
			this->coinPosNum1[73][2] = 0;
			break;
		case 5:
			this->coinPosNum1[74][2] = 0;
			break;
		}
		break;
	case 2:
		switch (x)
		{
		case -5:
			this->coinPosNum1[75][2] = 0;
			break;
		case 5:
			this->coinPosNum1[76][2] = 0;
			break;
		}
		break;
	case 3:
		switch (x)
		{
		case -8:
			this->coinPosNum1[77][2] = 0;
			break;
		case -7:
			this->coinPosNum1[78][2] = 0;
			break;
		case -6:
			this->coinPosNum1[79][2] = 0;
			break;
		case -5:
			this->coinPosNum1[80][2] = 0;
			break;
		case -4:
			this->coinPosNum1[81][2] = 0;
			break;
		case -3:
			this->coinPosNum1[82][2] = 0;
			break;
		case -2:
			this->coinPosNum1[83][2] = 0;
			break;
		case -1:
			this->coinPosNum1[84][2] = 0;
			break;
		case 1:
			this->coinPosNum1[85][2] = 0;
			break;
		case 2:
			this->coinPosNum1[86][2] = 0;
			break;
		case 3:
			this->coinPosNum1[87][2] = 0;
			break;
		case 4:
			this->coinPosNum1[88][2] = 0;
			break;
		case 5:
			this->coinPosNum1[89][2] = 0;
			break;
		case 6:
			this->coinPosNum1[90][2] = 0;
			break;
		case 7:
			this->coinPosNum1[91][2] = 0;
			break;
		case 8:
			this->coinPosNum1[92][2] = 0;
			break;
		}
		break;
	case 4:
		switch (x)
		{
		case -8:
			this->coinPosNum1[93][2] = 0;
			break;
		case -5:
			this->coinPosNum1[94][2] = 0;
			break;
		case -1:
			this->coinPosNum1[95][2] = 0;
			break;
		case 1:
			this->coinPosNum1[96][2] = 0;
			break;
		case 5:
			this->coinPosNum1[97][2] = 0;
			break;
		case 8:
			this->coinPosNum1[98][2] = 0;
			break;
		}
		break;
	case 5:
		switch (x)
		{
		case -7:
			this->coinPosNum1[99][2] = 0;
			break;
		case -5:
			this->coinPosNum1[100][2] = 0;
			break;
		case -4:
			this->coinPosNum1[101][2] = 0;
			break;
		case -3:
			this->coinPosNum1[102][2] = 0;
			break;
		case -2:
			this->coinPosNum1[103][2] = 0;
			break;
		case -1:
			this->coinPosNum1[104][2] = 0;
			break;
		case 1:
			this->coinPosNum1[105][2] = 0;
			break;
		case 2:
			this->coinPosNum1[106][2] = 0;
			break;
		case 3:
			this->coinPosNum1[107][2] = 0;
			break;
		case 4:
			this->coinPosNum1[108][2] = 0;
			break;
		case 5:
			this->coinPosNum1[109][2] = 0;
			break;
		case 7:
			this->coinPosNum1[110][2] = 0;
			break;
		}
		break;
	case 6:
		switch (x)
		{
		case -7:
			this->coinPosNum1[111][2] = 0;
			break;
		case -5:
			this->coinPosNum1[112][2] = 0;
			break;
		case -3:
			this->coinPosNum1[113][2] = 0;
			break;
		case 3:
			this->coinPosNum1[114][2] = 0;
			break;
		case 5:
			this->coinPosNum1[115][2] = 0;
			break;
		case 7:
			this->coinPosNum1[116][2] = 0;
			break;
		}
		break;
	case 7:
		switch (x)
		{
		case -8:
			this->coinPosNum1[117][2] = 0;
			break;
		case -7:
			this->coinPosNum1[118][2] = 0;
			break;
		case -6:
			this->coinPosNum1[119][2] = 0;
			break;
		case -5:
			this->coinPosNum1[120][2] = 0;
			break;
		case -3:
			this->coinPosNum1[121][2] = 0;
			break;
		case -2:
			this->coinPosNum1[122][2] = 0;
			break;
		case -1:
			this->coinPosNum1[123][2] = 0;
			break;
		case 1:
			this->coinPosNum1[124][2] = 0;
			break;
		case 2:
			this->coinPosNum1[125][2] = 0;
			break;
		case 3:
			this->coinPosNum1[126][2] = 0;
			break;
		case 5:
			this->coinPosNum1[127][2] = 0;
			break;
		case 6:
			this->coinPosNum1[128][2] = 0;
			break;
		case 7:
			this->coinPosNum1[129][2] = 0;
			break;
		case 8:
			this->coinPosNum1[130][2] = 0;
			break;
		}
		break;
	case 8:
		switch (x)
		{
		case -8:
			this->coinPosNum1[131][2] = 0;
			break;
		case -1:
			this->coinPosNum1[132][2] = 0;
			break;
		case 1:
			this->coinPosNum1[133][2] = 0;
			break;
		case 8:
			this->coinPosNum1[134][2] = 0;
			break;
		}
		break;
	case 9:
		switch (x)
		{
		case -8:
			this->coinPosNum1[135][2] = 0;
			break;
		case -7:
			this->coinPosNum1[136][2] = 0;
			break;
		case -6:
			this->coinPosNum1[137][2] = 0;
			break;
		case -5:
			this->coinPosNum1[138][2] = 0;
			break;
		case -4:
			this->coinPosNum1[139][2] = 0;
			break;
		case -3:
			this->coinPosNum1[140][2] = 0;
			break;
		case -2:
			this->coinPosNum1[141][2] = 0;
			break;
		case -1:
			this->coinPosNum1[142][2] = 0;
			break;
		case 0:
			this->coinPosNum1[143][2] = 0;
			break;
		case 1:
			this->coinPosNum1[144][2] = 0;
			break;
		case 2:
			this->coinPosNum1[145][2] = 0;
			break;
		case 3:
			this->coinPosNum1[146][2] = 0;
			break;
		case 4:
			this->coinPosNum1[147][2] = 0;
			break;
		case 5:
			this->coinPosNum1[148][2] = 0;
			break;
		case 6:
			this->coinPosNum1[149][2] = 0;
			break;
		case 7:
			this->coinPosNum1[150][2] = 0;
			break;
		case 8:
			this->coinPosNum1[151][2] = 0;
			break;
		}
		break;

	}
}
//check the state (eaten or not) of all power ups. If it is eaten, set its value to 0. Input x and z is the coordinate of the pacman. If pacman eats a power up, return 0.
bool mazeCoinPowerup::checkPower(float xPos, float zPos) 
{
	//set the coordinate of pacman as integer.
	int x = (int)xPos;
	int z = (int)zPos;
	if (x == -8 && z == -9 && powerPosNum1[0][2] == 1) //check the state of the power up at the specific position
	{
		powerPosNum1[0][2] = 0;
		return 0;
	}
	else if (x == 8 && z == -9 && powerPosNum1[1][2] == 1)//check the state of the power up at the specific position
	{
		powerPosNum1[1][2] = 0;
		return 0;
	}
	else if (x == -8 && z == 5 && powerPosNum1[2][2] == 1)//check the state of the power up at the specific position
	{
		powerPosNum1[2][2] = 0;
		return 0;
	}
	else if (x == 8 && z == 5 && powerPosNum1[3][2] == 1)//check the state of the power up at the specific position
	{
		powerPosNum1[3][2] = 0;
		return 0;
	}
	return 1;
}