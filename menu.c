//main menu of the game
//Version 0.1
//4/25/2020  -   Initial Version by jinren zhou
//#include <windows.h>
#include <stdio.h>
#include "SDL/SDL.h"
//#include "SDL_thread.h"


////////////////
//#include "PVP.h"

//#include<SDL_main.h>

int menu(void)
//int main()
{
	
         SDL_Surface* screen;	//This pointer will reference the backbuffer
	//SDL_Surface* screen1;
        SDL_Surface* menu;	//This pointer will reference our bitmap sprite
	//SDL_Surface* menu1=NULL;
	//SDL_Surface* button0;
	SDL_Surface* temp;	//This pointer will temporarily reference our bitmap sprite
	//SDL_Surface* board=NULL;

	SDL_Rect src, dest;
	




	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	//When this program exits, SDL_Quit must be called
	//atexit(SDL_Quit);

	//Set the video mode to fullscreen 640x480 with 16bit colour and double-buffering
	screen = SDL_SetVideoMode(741, 495, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	//screen1 = SDL_SetVideoMode(741, 495, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);



	SDL_WM_SetCaption("Team5--CHESS", 0);
	if (screen == NULL) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}

	//Load the bitmap into a temporary surface, and check for success
	temp = SDL_LoadBMP("chess0.bmp");
	

	if (temp == NULL) {
		printf("Unable to load bitmap: %s\n", SDL_GetError());
		return 1;
	}

	//Convert the surface to the appropriate display format
	menu = SDL_DisplayFormat(temp);

	//Release the temporary surface
	SDL_FreeSurface(temp);

	//Construct the source rectangle for our blit
	src.x = 0;
	src.y = 0;
	src.w = menu->w;	//Use image->w to display the entire width of the image
	src.h = menu->h;	//Use image->h to display the entire height of the image

	//Construct the destination rectangle for our blit
	dest.x = 0;		//Display the image at the (X,Y) coordinates (100,100)
	dest.y = 0;
	dest.w = menu->w;	//Ensure the destination is large enough for the image's entire width/height
	dest.h = menu->h;

	//Blit the image to the backbuffer
	SDL_BlitSurface(menu, &src, screen, &dest);

	//Flip the backbuffer to the primary
	SDL_Flip(screen);
	////////////////////////////////////////////////
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;

	SDL_Event event;
	int quit = 0;
	while (quit == 0)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_MOUSEMOTION)
			{
				rect.x = event.motion.x;
				rect.y = event.motion.y;
				//printf("x0=  %d, y0=  %d\n", rect.x, rect.y);

				if (rect.x >= 292 && rect.x <= 445 && rect.y >= 225 && rect.y <= 277)  
				{
					temp = SDL_LoadBMP("chess0_b_1.bmp");
					menu = SDL_DisplayFormat(temp);
					SDL_FreeSurface(temp);
					SDL_BlitSurface(menu, &src, screen, &dest);
					SDL_Flip(screen);

				}
				else if (rect.x >= 292 && rect.x <= 445 && rect.y >= 327 && rect.y <= 370) 
				{
					temp = SDL_LoadBMP("chess0_b_2.bmp");
					menu = SDL_DisplayFormat(temp);
					SDL_FreeSurface(temp);
					SDL_BlitSurface(menu, &src, screen, &dest);
					SDL_Flip(screen);

				}
				else if (rect.x >= 292 && rect.x <= 445 && rect.y >= 407 && rect.y <= 456) 
				{
					temp = SDL_LoadBMP("chess0_b_3.bmp");
					menu = SDL_DisplayFormat(temp);
					SDL_FreeSurface(temp);
					SDL_BlitSurface(menu, &src, screen, &dest);
					SDL_Flip(screen);

				}
				else if (rect.x >= 655 && rect.x <= 696 && rect.y >= 437 && rect.y <= 463) 
				{
					temp = SDL_LoadBMP("chess0_b_4.bmp");
					menu = SDL_DisplayFormat(temp);
					SDL_FreeSurface(temp);
					SDL_BlitSurface(menu, &src, screen, &dest);
					SDL_Flip(screen);

				}
				else if (((rect.x < 292) | (rect.x > 445) | (rect.y < 225) | (rect.y > 456)) | ((rect.y > 227 && rect.y < 327) | (rect.y > 370 && rect.y < 407)) | (((rect.x < 655) | (rect.x > 696)) && (rect.y < 437 
&& rect.y>463)))
				{
					//printf("x1=  %d, y1=  %d\n", rect.x, rect.y);
					temp = SDL_LoadBMP("chess0.bmp");
					menu = SDL_DisplayFormat(temp);
					SDL_FreeSurface(temp);
					SDL_BlitSurface(menu, &src, screen, &dest);
					SDL_Flip(screen);
				}

			}	////////////////////////////////////////////////////
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if (rect.x >= 292 && rect.x <= 445 && rect.y >= 225 && rect.y <= 277)
					{
						
						/*temp = SDL_LoadBMP("board.bmp");
						board=SDL_DisplayFormat(temp);
						SDL_FreeSurface(temp);
						SDL_BlitSurface(board, &src, screen1, &dest);
						SDL_Flip(screen1);
						PVP(screen1);
						temp = SDL_LoadBMP("chess0.bmp");
						menu = SDL_DisplayFormat(temp);
						SDL_FreeSurface(temp);
						SDL_BlitSurface(menu, &src, screen, &dest);
						SDL_Flip(screen);*/



						printf("PVp---button1");
					}

					if (rect.x >= 292 && rect.x <= 445 && rect.y >= 327 && rect.y <= 370)
					{
						printf("PVE---button1");
					}
					if (rect.x >= 292 && rect.x <= 445 && rect.y >= 407 && rect.y <= 456)
					{
						printf("GAME RULES---button3");
					}

				}
			}
			if (event.type == SDL_QUIT)
				{
					quit = 1;
				}

				
				if ((event.type == SDL_MOUSEBUTTONDOWN) && (rect.x >= 655 && rect.x <= 696 && rect.y >= 437 && rect.y <= 463))
				{
					quit = 1;//event.button.button=e
				}
			
		}
	}
		//Wait for 2500ms (2.5 seconds) so we can see the image


		//Release the surface
		SDL_FreeSurface(menu);

		//Return success!





		//printf("dsafdsa");

		SDL_Quit();
		return 0;
	
}

