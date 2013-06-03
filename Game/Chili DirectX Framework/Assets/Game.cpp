/****************************************************************************************** 
 *	Chili DirectX Framework Version 11.12.17											  *	
 *	Game.cpp																			  *
 *	Copyright 2011 PlanetChili.net														  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "Game.h"
#include <cstdlib>
#include <ctime>


Game::Game( HWND hWnd,const KeyboardServer& kServer )
:	gfx ( hWnd ),
	kbd( kServer ),

	//remember to initialize the variables
	crosshairX(0),
	crosshairY(0),
	boxX(50),
	boxY(50),
	lineY(400),
	speed(3),
	boxSize(50)
{
	srand((unsigned)time(0));

}

//Model
void Game::Go()
{
	//Update the values in the model
	UpdateCrosshair();
	UpdateBox();
	UpdateHorizontalLine();

	//Then write them to the view
	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

//Drawings
void Game::DrawCrosshair(int x, int y)
{
	//vertical top
	gfx.PutPixel(0 + x, -3 + y, 255,255,255);
	gfx.PutPixel(0 + x, -2 + y, 255,255,255);
	gfx.PutPixel(0 + x, -1 + y, 255,255,255);

	//vertical bottom
	gfx.PutPixel(0 + x, 1 + y, 255,255,255);
	gfx.PutPixel(0 + x, 2 + y, 255,255,255);
	gfx.PutPixel(0 + x, 3 + y, 255,255,255);

	//horizontal left
	gfx.PutPixel(-3 + x, 0 + y, 255,255,255);
	gfx.PutPixel(-2 + x, 0 + y, 255,255,255);
	gfx.PutPixel(-1 + x, 0 + y, 255,255,255);

	//horizontal right
	gfx.PutPixel(1 + x, 0 + y, 255,255,255);
	gfx.PutPixel(2 + x, 0 + y, 255,255,255);
	gfx.PutPixel(3 + x, 0 + y, 255,255,255);
}
void Game::DrawBox(int posX, int posY, int size)
{
	for(int x = 0; x < size; x++)
	{
		for(int y = 0; y < size; y++)
		{
			gfx.PutPixel(x + posX, y + posY, 255,255,0);
		}
	}
}
void Game::DrawHorizontalLine(int y)
{
	int hRes = 800;

	for(int index = 0; index < hRes; index++)
	{
		gfx.PutPixel(index, y, 100,100,100);
	}
}


//Animations
void Game::UpdateCrosshair()
{
	if(kbd.LeftIsPressed())
	{
		crosshairX = crosshairX - speed;
	}

	if(kbd.RightIsPressed())
	{
		crosshairX = crosshairX + speed;
	}

	if(kbd.UpIsPressed())
	{
		crosshairY = crosshairY - speed;
	}

	if(kbd.DownIsPressed())
	{
		crosshairY = crosshairY + speed;
	}

}
void Game::UpdateBox()
{
	int boxCenterX = boxX + (boxSize/2);
	int boxCenterY = boxY + (boxSize/2);

	int xToCenter = boxCenterX - crosshairX;
	int yToCenter = boxCenterY - crosshairY;

	//Calculation of hitbox is a little weird. All calculations are based on the top left pixel, so we need to calculate for distance to
	//center of crosshair, and take into consideration the width and height of the box.

	//X values...
	if(crosshairX > boxX && crosshairX < (boxX + boxSize) && crosshairY>boxY && crosshairY<(boxY + boxSize))
	{

		//Top Left section
		if(xToCenter >= 0 && yToCenter >= 0)
		{
			if(xToCenter > yToCenter)
			{
				//push right
				if(boxX + boxSize < 799)
				{
					boxX = boxX + speed;
				}
			}

			if(xToCenter < yToCenter)
			{
				//push down
				if(boxY + boxSize < 599)
				{
					boxY = boxY + speed;
				}
			}
		}

		//Top Right section
		if(xToCenter < 0 && yToCenter > 0)
		{
			if(abs(xToCenter) > yToCenter )
			{
				//push left
				if(boxX > 0)
				{
					boxX = boxX - speed;
				}
			}

			if(abs(xToCenter) < yToCenter)
			{
				//push down
				if(boxY + boxSize < 599)
				{
					boxY = boxY + speed;
				}
			}
		}

		//Bottom Right section
		if(xToCenter <= 0 && yToCenter <= 0)
		{
			if(abs(xToCenter) < abs(yToCenter))
			{
				//Push up
				if(boxY > 0)
				{
					boxY = boxY - speed;
				}
			}

			if(abs(xToCenter) > abs(yToCenter))
			{
				//Push left
				if(boxX > 0)
				{
					boxX = boxX - speed;
				}
			}
		}

		if(xToCenter > 0 && yToCenter < 0)
		{
			if(xToCenter < abs(yToCenter))
			{
				//push up
				if(boxY > 0)
				{
					boxY = boxY - speed;
				}
			}

			if(xToCenter > abs(yToCenter))
			{
				//push right
				if(boxX + boxSize < 799)
				{
					boxX = boxX + speed;
				}
			}
		}
	}
}
void Game::UpdateHorizontalLine()
{
	//Move the line to a new location, if the box crosses it
	if(boxY < lineY && boxY + boxSize > lineY)
	{
		int random_integer = (rand() % 600);
		lineY = random_integer;
	}
}

//View
void Game::ComposeFrame()
{
	DrawBox(boxX, boxY, boxSize);
	DrawHorizontalLine(lineY);
	DrawCrosshair(crosshairX, crosshairY);
}