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

Game::Game( HWND hWnd,const KeyboardServer& kServer )
:	gfx ( hWnd ),
	kbd( kServer ),

	//remember to initialize the variables
	crosshairX(0),
	crosshairY(0),
	boxX(200),
	boxY(280),
	lineY(400)
{}

//Model
void Game::Go()
{
	UpdateCrosshair();
	UpdateBox(1);

	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

//Drawings
void Game::DrawCrosshair(int x, int y)
{

	//vertical top
	gfx.PutPixel(4 + x, 0 + y, 255,255,255);
	gfx.PutPixel(4 + x, 1 + y, 255,255,255);
	gfx.PutPixel(4 + x, 2 + y, 255,255,255);

	//vertical bottom
	gfx.PutPixel(4 + x, 4 + y, 255,255,255);
	gfx.PutPixel(4 + x, 5 + y, 255,255,255);
	gfx.PutPixel(4 + x, 6 + y, 255,255,255);

	//horizontal left
	gfx.PutPixel(2 + x, 3 + y, 255,255,255);
	gfx.PutPixel(1 + x, 3 + y, 255,255,255);
	gfx.PutPixel(0 + x, 3 + y, 255,255,255);

	//horizontal right
	gfx.PutPixel(6 + x, 3 + y, 255,255,255);
	gfx.PutPixel(7 + x, 3 + y, 255,255,255);
	gfx.PutPixel(8 + x, 3 + y, 255,255,255);
}
void Game::DrawBox(int x, int y)
{
	for(int index = 0; index < 20; index++)
	{
		gfx.PutPixel(x + index,0+y,255,255,0);
		gfx.PutPixel(x + index,1+y,255,255,0);
		gfx.PutPixel(x + index,2+y,255,255,0);
		gfx.PutPixel(x + index,3+y,255,255,0);
		gfx.PutPixel(x + index,4+y,255,255,0);
		gfx.PutPixel(x + index,5+y,255,255,0);
		gfx.PutPixel(x + index,6+y,255,255,0);
		gfx.PutPixel(x + index,7+y,255,255,0);
		gfx.PutPixel(x + index,8+y,255,255,0);
		gfx.PutPixel(x + index,9+y,255,255,0);
		gfx.PutPixel(x + index,10+y,255,255,0);
		gfx.PutPixel(x + index,11+y,255,255,0);
		gfx.PutPixel(x + index,12+y,255,255,0);
		gfx.PutPixel(x + index,13+y,255,255,0);
		gfx.PutPixel(x + index,14+y,255,255,0);
		gfx.PutPixel(x + index,15+y,255,255,0);
		gfx.PutPixel(x + index,16+y,255,255,0);
		gfx.PutPixel(x + index,17+y,255,255,0);
		gfx.PutPixel(x + index,18+y,255,255,0);
		gfx.PutPixel(x + index,19+y,255,255,0);
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
	int speed = 3;

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
void Game::UpdateBox(int speed)
{
	hit = false;

	//boxX = boxX + speed;

	if(kbd.EnterIsPressed())
	{
		int cX = crosshairX + 4;
		int cY = crosshairY + 4;


		//Calculation of hitbox is a little weird. All calculations are based on the top left pixel, so we need to calculate for distance to
		//center of crosshair, and take into consideration the width and height of the box.

		//X values...
		if(cX > boxX && cX < (boxX + 20))
		{
			//Y values...
			if(cY>boxY && cY<(boxY + 20))
			{
				//Now that a hit has been registered, detect from which side.

				int centerX = boxX + 10;
				int centerY = boxY + 10;
				int rightX = boxX + 20;
				int bottomY = boxY + 20;

				//crosshair distance INSIDE box:
				int insideX = cX - boxX;
				int insideY = cY - boxY;



				if(insideX <= 10 && insideY <= 10)
				{
					//Pos1 - OK!
					if(insideX > insideY)
					{
						boxY = boxY + 5;
					}
					else
					{					
						boxX = boxX + 5;
					}
				}
				else if(insideX >= 10 && insideY <= 10)
				{
					//Pos2 - ERROR!
					if(insideX > insideY)
					{
						boxY = boxY + 5;
					}
					else
					{
						boxX = boxX - 5;
					}
				}
				else if(insideX <= 10 && insideY >= 10)
				{
					//Pos3
					if(insideX > insideY)
					{
						boxX = boxX - 5;
					}
					else
					{
						boxY = boxY - 5;
					}
					
					
				}
				else if(insideX >= 10 && insideY >= 10)
				{
					insideY = insideY-10;

					//Pos4
					if(insideY > insideX)
					{
						boxY = boxY - 5;
					}
					else
					{
						boxX = boxX + 5;
					}

					
					
				}

				
			}
		}
	}
}



void Game::ComposeFrame()
{
	

	DrawBox(boxX,boxY);

	DrawHorizontalLine(lineY);

	DrawCrosshair(crosshairX, crosshairY);


	// TODO: insert frame drawing code here
}