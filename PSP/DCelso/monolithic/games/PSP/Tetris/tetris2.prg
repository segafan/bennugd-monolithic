/*------------------------------------------------------------------------------
	Demo program: Tetris
	Author: Roelf Leenders
	Date: Somewhere around 2007
------------------------------------------------------------------------------*/

program tetris;

//If set to 1, it uses png files, on 0 it uses an FPG file
#define USE_PNG 0

//Not defined by default!
//#define OS_PSP 1001

//import "mod_cd"
//import "mod_dir"
//import "mod_debug"
import "mod_file"
//import "mod_flic"
//import "mod_grproc"
import "mod_joy"
import "mod_key"
//import "mod_m7"
import "mod_math"
//import "mod_mem"
//import "mod_mouse"
//import "mod_path"
import "mod_proc"
//import "mod_scroll"
import "mod_rand"
//import "mod_regex"
import "mod_say"
//import "mod_sort"
//import "mod_sound"
//import "mod_string"
//import "mod_sys"
import "mod_text"
//import "mod_time"
//
import "mod_timers"
import "mod_wm"

import "mod_screen"
import "mod_video"
import "mod_map"
import "mod_draw"
//import "mod_effects"
//import "mod_blendop"



//PSP Controls
#define PSP_TRIANGLE_BUTTON 0
#define PSP_CIRCLE_BUTTON 1
#define PSP_X_BUTTON 2
#define PSP_SQUARE_BUTTON 3

#define PSP_L_BUTTON 4
#define PSP_R_BUTTON 5

#define PSP_DOWN_BUTTON 6
#define PSP_LEFT_BUTTON 7
#define PSP_UP_BUTTON 8
#define PSP_RIGHT_BUTTON 9

#define PSP_SELECT_BUTTON 10
#define PSP_START_BUTTON 11
//Joystick?
#define PSP_LEFT_RIGHT_AXIS 0
#define PSP_UP_DOWN_AXIS 1


const
	//Dimensions of the tetris area
	HIGH = 20;
	WIDE = 10;
	
	//Screen dimensions
	SCRW = 480;
	SCRH = 271;

global
	//PSP Key layout
	int __A = PSP_X_BUTTON;
	int __B = PSP_SQUARE_BUTTON;
	int __SELECT = PSP_SELECT_BUTTON;
	int __R = PSP_R_BUTTON;
	int __L = PSP_L_BUTTON;
	int __START = PSP_START_BUTTON;
	int __UP = PSP_UP_BUTTON;
	int __DOWN = PSP_DOWN_BUTTON;
	int __LEFT = PSP_LEFT_BUTTON;
	int __RIGHT = PSP_RIGHT_BUTTON;

	//High scores for all 3 difficulties
	int highscore[2];

	//Current difficulty
	int difficulty;
	int graad[2];

	int BLOKSPEED = 15;

	int drawmode = 1;

	int blok[10][5][5];
	int blockMap[11];
	//Available

	//upcoming block type
	int nexto = 0;
	//Current block type
	int nu = 1;
	//position of the current block
	int nux = 6;
	int nuy = 7;
	//which way it is rotated
	int kant;

	//Scoring:
	int ScoreVolleRij = 100;
	int ScoreZomaar = 2;

	//declare the playfield
	int steen[HIGH][WIDE];

	//Statistics:
	int score;
	int level;

	//Loading stuff
	int fpg;
	int music;

	int n;


begin
	//When running in Windows/Linux, we should be able to test it
	if(OS_ID == OS_WIN32 || OS_ID == OS_LINUX)
		//Adapt controls to a keyboard
		__A = _control;
		__B = _alt;
		__SELECT = _esc;
		__R = _r;
		__L = _l;
		__START = _enter;
		__UP = _up;
		__DOWN = _down;
		__LEFT = _left;
		__RIGHT = _right;
		
		//Size it up
		full_screen = false;
		scale_mode = SCALE_NORMAL2X;
		set_title("Tetris - By Roelf Leenders");
	end

	if(OS_ID == OS_PSP)
		joy_select(0);
	end
	
	set_mode(SCRW,SCRH,16);

	//Set the text color
	set_text_color(rgb(255,255,255)); //16 bit mode
	//set_text_color(15); //8 bit mode
	
	fill_map();

	//Load graphics
	if(USE_PNG)
		//Use PNG files to see if colours are working correctly
		fpg = 0;
		blockMap[1] = load_png("GFX/001.png");
		blockMap[2] = load_png("GFX/002.png");
		blockMap[3] = load_png("GFX/003.png");
		blockMap[4] = load_png("GFX/004.png");
		blockMap[5] = load_png("GFX/005.png");
		blockMap[6] = load_png("GFX/006.png");
		blockMap[7] = load_png("GFX/007.png");
		blockMap[8] = blockMap[2];
		blockMap[9] = blockMap[3];
		blockMap[10] = load_png("GFX/010.png");
	else
		//Other method, use the FPG file
		fpg = load_fpg("tetris.fpg");
		for(n=0;n<11;n++)
			blockMap[n] = n;
		end
	end

	//Scorelist
	//Load highscores from file: if there is no such file create one:
	if(!file_exists("scores.dat"));
	   save("scores.dat",highscore);
	end
	   
	load("scores.dat",highscore);


	//Create the blocks:
	n = 0;

	//   OO
	//   OO

	//      H  V
	blok[n][0][0] = 0;
	blok[n][0][1] = 0;
	blok[n][0][2] = 0;
	blok[n][0][3] = 0;
	blok[n][0][4] = 0;

	blok[n][1][0] = 0;
	blok[n][1][1] = 0;
	blok[n][1][2] = 1;
	blok[n][1][3] = 1;
	blok[n][1][4] = 0;

	blok[n][2][0] = 0;
	blok[n][2][1] = 0;
	blok[n][2][2] = 1;
	blok[n][2][3] = 1;
	blok[n][2][4] = 0;

	blok[n][3][0] = 0;
	blok[n][3][1] = 0;
	blok[n][3][2] = 0;
	blok[n][3][3] = 0;
	blok[n][3][4] = 0;

	blok[n][4][0] = 0;
	blok[n][4][1] = 0;
	blok[n][4][2] = 0;
	blok[n][4][3] = 0;
	blok[n][4][4] = 0;

	n++;

	//  O
	//  O
	//  OO

	//      H  V
	blok[n][0][0] = 0;
	blok[n][0][1] = 0;
	blok[n][0][2] = 0;
	blok[n][0][3] = 0;
	blok[n][0][4] = 0;

	blok[n][1][0] = 0;
	blok[n][1][1] = 0;
	blok[n][1][2] = 0;
	blok[n][1][3] = 0;
	blok[n][1][4] = 0;

	blok[n][2][0] = 0;
	blok[n][2][1] = 1;
	blok[n][2][2] = 1;
	blok[n][2][3] = 1;
	blok[n][2][4] = 0;

	blok[n][3][0] = 0;
	blok[n][3][1] = 0;
	blok[n][3][2] = 0;
	blok[n][3][3] = 1;
	blok[n][3][4] = 0;

	blok[n][4][0] = 0;
	blok[n][4][1] = 0;
	blok[n][4][2] = 0;
	blok[n][4][3] = 0;
	blok[n][4][4] = 0;

	//    O
	//   OOO
	n++;
	//      H  V
	blok[n][0][0] = 0;
	blok[n][0][1] = 0;
	blok[n][0][2] = 0;
	blok[n][0][3] = 0;
	blok[n][0][4] = 0;

	blok[n][1][0] = 0;
	blok[n][1][1] = 0;
	blok[n][1][2] = 1;
	blok[n][1][3] = 0;
	blok[n][1][4] = 0;

	blok[n][2][0] = 0;
	blok[n][2][1] = 1;
	blok[n][2][2] = 1;
	blok[n][2][3] = 1;
	blok[n][2][4] = 0;

	blok[n][3][0] = 0;
	blok[n][3][1] = 0;
	blok[n][3][2] = 0;
	blok[n][3][3] = 0;
	blok[n][3][4] = 0;

	blok[n][4][0] = 0;
	blok[n][4][1] = 0;
	blok[n][4][2] = 0;
	blok[n][4][3] = 0;
	blok[n][4][4] = 0;

	n++;
	// OOOO

	//      H  V
	blok[n][0][0] = 0;
	blok[n][0][1] = 0;
	blok[n][0][2] = 1;
	blok[n][0][3] = 0;
	blok[n][0][4] = 0;

	blok[n][1][0] = 0;
	blok[n][1][1] = 0;
	blok[n][1][2] = 1;
	blok[n][1][3] = 0;
	blok[n][1][4] = 0;

	blok[n][2][0] = 0;
	blok[n][2][1] = 0;
	blok[n][2][2] = 1;
	blok[n][2][3] = 0;
	blok[n][2][4] = 0;

	blok[n][3][0] = 0;
	blok[n][3][1] = 0;
	blok[n][3][2] = 1;
	blok[n][3][3] = 0;
	blok[n][3][4] = 0;

	blok[n][4][0] = 0;
	blok[n][4][1] = 0;
	blok[n][4][2] = 0;
	blok[n][4][3] = 0;
	blok[n][4][4] = 0;



	n++;
	//   OO
	//  OO

	//      H  V
	blok[n][0][0] = 0;
	blok[n][0][1] = 0;
	blok[n][0][2] = 0;
	blok[n][0][3] = 0;
	blok[n][0][4] = 0;

	blok[n][1][0] = 0;
	blok[n][1][1] = 0;
	blok[n][1][2] = 1;
	blok[n][1][3] = 0;
	blok[n][1][4] = 0;

	blok[n][2][0] = 0;
	blok[n][2][1] = 1;
	blok[n][2][2] = 1;
	blok[n][2][3] = 0;
	blok[n][2][4] = 0;

	blok[n][3][0] = 0;
	blok[n][3][1] = 1;
	blok[n][3][2] = 0;
	blok[n][3][3] = 0;
	blok[n][3][4] = 0;

	blok[n][4][0] = 0;
	blok[n][4][1] = 0;
	blok[n][4][2] = 0;
	blok[n][4][3] = 0;
	blok[n][4][4] = 0;

	//End easy difficulty, coming blocks are for medium
	graad[0] = n+1;

	n++;



	//  O O
	//  OOO

	//      H  V
	blok[n][0][0] = 0;
	blok[n][0][1] = 0;
	blok[n][0][2] = 0;
	blok[n][0][3] = 0;
	blok[n][0][4] = 0;

	blok[n][1][0] = 0;
	blok[n][1][1] = 1;
	blok[n][1][2] = 0;
	blok[n][1][3] = 1;
	blok[n][1][4] = 0;

	blok[n][2][0] = 0;
	blok[n][2][1] = 1;
	blok[n][2][2] = 1;
	blok[n][2][3] = 1;
	blok[n][2][4] = 0;

	blok[n][3][0] = 0;
	blok[n][3][1] = 0;
	blok[n][3][2] = 0;
	blok[n][3][3] = 0;
	blok[n][3][4] = 0;

	blok[n][4][0] = 0;
	blok[n][4][1] = 0;
	blok[n][4][2] = 0;
	blok[n][4][3] = 0;
	blok[n][4][4] = 0;

	n++;

	//     O
	//    OOO
	//     O

	//      H  V
	blok[n][0][0] = 0;
	blok[n][0][1] = 0;
	blok[n][0][2] = 0;
	blok[n][0][3] = 0;
	blok[n][0][4] = 0;

	blok[n][1][0] = 0;
	blok[n][1][1] = 0;
	blok[n][1][2] = 1;
	blok[n][1][3] = 0;
	blok[n][1][4] = 0;

	blok[n][2][0] = 0;
	blok[n][2][1] = 1;
	blok[n][2][2] = 1;
	blok[n][2][3] = 1;
	blok[n][2][4] = 0;

	blok[n][3][0] = 0;
	blok[n][3][1] = 0;
	blok[n][3][2] = 1;
	blok[n][3][3] = 0;
	blok[n][3][4] = 0;

	blok[n][4][0] = 0;
	blok[n][4][1] = 0;
	blok[n][4][2] = 0;
	blok[n][4][3] = 0;
	blok[n][4][4] = 0;

	//End of medium, upcoming are for hard
	graad[1] = n+1;

	n++;

	//    O
	//   O
	//  O

	//      H  V
	blok[n][0][0] = 0;
	blok[n][0][1] = 0;
	blok[n][0][2] = 0;
	blok[n][0][3] = 0;
	blok[n][0][4] = 0;

	blok[n][1][0] = 0;
	blok[n][1][1] = 1;
	blok[n][1][2] = 0;
	blok[n][1][3] = 0;
	blok[n][1][4] = 0;

	blok[n][2][0] = 0;
	blok[n][2][1] = 0;
	blok[n][2][2] = 1;
	blok[n][2][3] = 0;
	blok[n][2][4] = 0;

	blok[n][3][0] = 0;
	blok[n][3][1] = 0;
	blok[n][3][2] = 0;
	blok[n][3][3] = 1;
	blok[n][3][4] = 0;

	blok[n][4][0] = 0;
	blok[n][4][1] = 0;
	blok[n][4][2] = 0;
	blok[n][4][3] = 0;
	blok[n][4][4] = 0;

	//End of hard difficulty
	graad[2] = n+1;
	say("Graad 2:" + graad[2]);
	//initialize
	score = 0;
	level = 0;
	
	//Fire up the menu
	menu();

end


/**
	Basic menu, option to select difficulty and view the corresponding highscore

*/
process menu()

private
	int i;
	string graden[2] = "Easy","Medium","Hard";
	string str_text;
	string str_tex2;
	int text,tex2;

begin

	//Empty playfield
	for(x=0;x<HIGH;x++)
		for(y=0;y<WIDE;y++)
			steen[x][y] = 0;
		end
	end	

	//fill the background map with a gradient
	fill_map();

	//set difficulty to easy as default
	difficulty = 1;

	//create a graphic with TETRIS written in it
	graph = write_in_map(0,"TETRIS",4);

	//Write the rest of the text and variables
	write(0,SCRW/2,160,4,"Press [Start] To Start");
	write(0,SCRW/2,170,4,"[Select] to Quit");
		

	str_text = graden[difficulty-1];
	str_tex2 = highscore[difficulty-1];
	
	write(0,SCRW/2-50,190,3,"Difficulty:");
	text = write_var(0,SCRW/2+100,190,5,str_text);

	write(0,SCRW/2-50,210,3,"HighScore:");
	
	str_tex2 = highscore[difficulty-1];
	tex2 = write_var(0,SCRW/2+100,210,5,str_tex2);
	
	write(0,SCRW,SCRH,8,"By Moogster (Roelf Leenders)");

	//since TETRIS is the graphic of this process, put it as title above the options:
	x = SCRW/2;
	y = SCRH/3;

	loop
		//Exit if pressed escape

		i+=4500;

		//Effect to make it look like the title is rotating:
		size_x = 300;
		size_y = abs(get_distx(i,300));
		//make it mirror vertically to make the rotating believable
		if(get_distx(i,300)<0)
			flags = 2;
		else
			flags = 0;
		end
		
		//Switch difficulty and fix variables according to that
		if(checkButton(__LEFT) and difficulty>1)
			difficulty--;
			str_text = graden[difficulty-1];
			str_tex2 = highscore[difficulty-1];
			while(checkButton(__LEFT))frame;end
		end

		//Switch difficulty and fix variables according to that
		if(checkButton(__RIGHT) and difficulty<3)
			difficulty++;
			str_text = graden[difficulty-1];
			str_tex2 = highscore[difficulty-1];
			while(checkButton(__RIGHT))frame;end
		end

		//break out of the loop if the game is started
		if(checkButton(__START))
			break;
		end

		//and exit if select is pressed
		if(checkButton(__SELECT))
			exit("",0);
		end
		
		frame;
	end

	//START GAME
	//============

	//Limit the frames per second related to the difficulty, to make the game faster
	//for higher and slower for lower difficulty
	set_fps(20+difficulty*7,0);

	//delete all menu text
	delete_text(all_text);

	//process to render playfield to the screen
	render();

	//write game texts
	write_int(0,SCRW*2/3,SCRH/3-10,4,&score);
	write(0,SCRW*2/3,SCRH/3-20,4,"Score:");
	write(0,SCRW*2/3,SCRH/3+10,4,"Level:");
	write_int(0,SCRW*2/3,SCRH/3+20,4,&level);
	
	//and fire up the game logic
	game();
end



/*
	Renders the level/next-block-preview/current block to the screen
	every frame.
*/
process render();

private
	int i,j,k,l,block;

begin

	//If a render process is already active, don't start this one
	if(get_id(type render) != id)
		return;
	end

	loop
		//select key to exit to the main menu, exit everything and start the menu.
		if(checkButton(__SELECT))
			while(checkButton(__SELECT))frame;end
			clear_screen();
			delete_text(all_text);
			score = 0;
			difficulty = 0;
			let_me_alone();
			menu();
			return;
		end

		//Rendering level with squares filled
		for(i = 0;i < HIGH+2;i++)
			for(j = 0;j < WIDE+2;j++)
				block = 0;

				if(i == 0 or i == HIGH+1 or j == 0 or j == WIDE+1)
					block = 1;
				else
					block = steen[i-1][j-1];
				end

				if(block == 0)
					block = 10;	
				end

				put(fpg,blockMap[block],80+((j-WIDE/2)*8),SCRH/2+((i-HIGH/2)*8)-8);
			end
		end


		if(drawmode)
			//Preview window
			for(i = 0;i < 5+2;i++)
				for(j = 0;j < 5+2;j++)
					block = 0;

					if(i == 0 or i == 5+1 or j == 0 or j == 5+1)
						block = 1;
					else
						if(blok[nexto][i-1][j-1])
							block = nexto+1;
						end
					end

					if(block == 0)
						block=10;
					end

					put(fpg,blockMap[block],100+(WIDE*8)+((j-5/2)*8),SCRH/2+((i-HIGH/2)*8)-8);

				end
			end
			
			//Current moving block
			for(i = 0;i < 5;i++)
				for(j = 0;j < 5;j++)

					switch(kant)
						case 0:
							k = i;
							l = j;
						end
						case 1:
							k = 4-j;
							l = i;
						end
						case 2:
							k = 4-i;
							l = 4-j;
						end
						case 3:
							k = j;
							l = 4-i;
						end
					end
					
					block = blok[nu][i][j];
					
					if(block != 0)
						put(fpg,blockMap[nu+1],80+(((nux+k-1)-WIDE/2)*8),SCRH/2+(((nuy+l-1)-HIGH/2)*8)-8);
					end
				end
			end
			
		end//drawmode
		
		frame;
	end

end



/*
	Detects horizontal lines and handles accordingly
	
*/
process detect();

private
int i,j,k;
int rij[HIGH];

begin

	loop
		//add up how many positions are taken for every horizontal rule
		for(i = HIGH-1;i >= 0;i--)
			rij[i] = 0;
			for(j = 0;j < WIDE;j++)
				if(steen[i][j] > 0)
					rij[i]++;
				end
			end

			//if the amount of blocks on a line the same is as the amount of positions
			if(rij[i] == WIDE)
				//line detected!
				
				//Add the points for a line to the total score
				score+=ScoreVolleRij;
				
				//move the rest of the lines one position down
				for(k = i;k>0;k--)
					for(j = 0;j < WIDE;j++)
						steen[k][j] = steen[k-1][j];
					end
				end
				i++;
			end

		end

		frame;
	end

end



/*
	Returns whether or not block type(blocknumber given in 'blokje' with rotation 'gekant')
	can fit on block position x,y in the playing field. Returns true or false
*/
process kanNaar(blokje,gekant,x,y)

private
int i,j,k,l;

begin

	for(i=0;i<5;i++)
		for(j=0;j<5;j++)

			switch(gekant)
				case 0:
					k = i;
					l = j;
				end
				case 1:
					k = 4-j;
					l = i;
				end
				case 2:
					k = 4-i;
					l = 4-j;
				end
				case 3:
					k = j;
					l = 4-i;
				end
			end

			if(blok[blokje][i][j])
				k = x+k-2;
				l = y+l-2;

				if(k < 0 or k>WIDE-1 or l<0 or l>HIGH-1)
					return false;
				else
					if(steen[l][k]>0)
						return false;
					end
				end
			end
			
		end
	end

	return true;

end



/*
	Deprecated process to test out if stuff was working correctly, skip!
*//*
process Test();

private
int i,j,k,l;


begin
	write(0,0,0,0,"Coords:");
	write_int(0,20,10,0,&nux);
	write_int(0,40,10,0,&nuy);


	loop

		if(checkButton(__LEFT))
			if(!kanNaar(nu,kant,--nux,nuy))
				nux++;
			end
			while(checkButton(__LEFT))frame;end
		end

		if(checkButton(__RIGHT))
			if(!kanNaar(nu,kant,++nux,nuy))
				nux--;
			end
			while(checkButton(__RIGHT))frame;end
		end

		if(checkButton(__UP))
			if(!kanNaar(nu,kant,nux,--nuy))
				nuy++;
			end
			while(checkButton(__UP))frame;end
		end

		if(checkButton(__DOWN))
			if(!kanNaar(nu,kant,nux,++nuy))
				nuy--;
			end
			while(checkButton(__DOWN))frame;end
		end

		if(checkButton(__A))
			kant = (kant+1)%4;
			while(checkButton(_control))frame;end
		end


		if(checkButton(__START))
			while(checkButton(__START))frame;end
			for(i=0;i<5;i++)
				for(j=0;j<5;j++)

					switch(kant)
						case 0:
							k = i;
							l = j;
						end
						case 1:
							k = 4-j;
							l = i;
						end
						case 2:
							k = 4-i;
							l = 4-j;
						end
						case 3:
							k = j;
							l = 4-i;
						end
					end

					if(blok[nu][i][j] > 0)
						steen[l+nuy-2][k+nux-2] = 1;
					end
				end
			end

			//Next block
			nu = nexto;
			nexto = rand(0,graad[difficulty-1]-1);

			nux = WIDE/2;
			nuy = -1;
			kant = 0;

			while(!kanNaar(nu,kant,nux,nuy))
				nuy++;
			end

		end

		frame;
	end

end*/


/*
	Game logic! holds track of variables, game over, playing block descendance,
	block picking, etc.
*/
process game()

private
//if zero the playblock is ready to go down a line
neer=1;

//Helping variables
i,j,k,l;
li,r,d;

ct;

begin

//Launch the process that autodetects if lines are filled
detect();

//determines which blocks are being played with(nu = current, next = next block)
nu = rand(0,graad[difficulty-1]-1);
nexto = rand(0,graad[difficulty-1]-1);

//set the render process to render the preview field too
drawmode = 1;

//set current block position(x -> nux, y -> nuy)
nux = WIDE / 2;
nuy = -1;
//set current block rotation
kant = 0;

//reset score and level
score = 0;
level = 1;

//descent the current block untill it is fully in the playfield.
while(!kanNaar(nu,kant,nux,nuy))
	nuy++;
end

//ready to go!
loop
	//which level is based on the score
	level = 1+(score / 5000);

	//can't go higher than level 10
	if(level > 10) level = 10;end
	
	//blocks descent faster for higher levels
	BLOKSPEED = 16 - level;

	//decrease time(in frames) before the current block can go down one line
	neer--;


	//if time to go down a line:
	if(neer == 0)
		if(!kannaar(nu,kant,nux,nuy+1))
			//if it can't descent a line, set y to true so the process knows it's time
			//for the next block
			y = 1;
		else
			//else go down and add the basic score addition to the total score
			nuy++;
			score += ScoreZomaar;
		end
		//time to the next descent of a block is BLOKSPEED
		neer = BLOKSPEED;
	else
		//not time to go down a line, so no new block.
		y = 0;
	end

	//signal that user wants to move the block to left/right/down direction
	if(checkButton(__LEFT))
		li++;
	else
		li = 0;
	end
	
	if(checkButton(__RIGHT))
		r++;
	else
		r = 0;
	end
	//fast down:
	if(checkButton(__DOWN) or checkButton(__B))
		d++;
	else
		d = 0;
	end

	//act on those signals by moving if possible:
	if(d == 1 or ((d%(BLOKSPEED/5)==BLOKSPEED/5-1) and d > 5))
		if(!kannaar(nu,kant,nux,++nuy))
			nuy--;
		end
	end

	if(li == 1 or ((li%(BLOKSPEED/5)==BLOKSPEED/5-1) and li > 5))
		if(!kannaar(nu,kant,--nux,nuy))
			nux++;
		end
	end

	if(r == 1 or ((r%(BLOKSPEED/5)==BLOKSPEED/5-1) and r > 5))
		if(!kannaar(nu,kant,++nux,nuy))
			nux--;
		end
	end

	//signal that the user wants to rotate the block
	if(checkButton(__A))
		ct++;
	else
		ct=0;
	end

	//act on that signal
	if(ct == 1 and kanNaar(nu,(kant+1)%4,nux,nuy))
		kant = (kant+1)%4;
	end



	//if y is true it's time for a new block
	if(y)

		for(i=0;i<5;i++)
			for(j=0;j<5;j++)

				switch(kant)
					case 0:
						k = i;
						l = j;
					end
					case 1:
						k = 4-j;
						l = i;
					end
					case 2:
						k = 4-i;
						l = 4-j;
					end
					case 3:
						k = j;
						l = 4-i;
					end
				end

				if(blok[nu][i][j] > 0)
					steen[l+nuy-2][k+nux-2] = nu+1;
				end

			end
		end

		//next block! current block 'nu' is assigned next block 'next'
		nu = nexto;
		//and choose a new block type for 'next'
		nexto = rand(0,graad[difficulty-1]-1);

		//reset variables to signal with
		li = -300;
		r = -300;
		d = -300;

		//reset position of the new block
		nux = WIDE/2;
		nuy = -1;
		kant = 0;

		//descent untill fully in the playground
		while(!kanNaar(nu,kant,nux,nuy))
			nuy++;
			//if descendance takes long, it means the new block can't be placed,
			//playfield is full and player is game over
			if(nuy >= 4)
				gameover();
				return;
			end
		end

	end

	frame;
end


end


/*
	Process to handle game over by player
*/
process gameover()

private
	int t;
begin

	//if the reached score is bigger than the highscore on the current difficulty
	//change the highscore and save it
	if(score > highscore[difficulty-1])
	  highscore[difficulty-1] = score;
	  t = write(0,SCRW*2/3,SCRH*2/3-20,4,"New Highscore!");
	  save("scores.dat",highscore);
	end

	//write game over text
	x = write(0,SCRW*2/3,SCRH*2/3,4,"Game Over");
	y = write(0,SCRW*2/3,SCRH*2/3+20,4,"<Press [Start] to start over>");

	//end all processes except for the current one
	let_me_alone();

	//and restart the render process
	render();

	//signal render() process not to draw the preview next block part
	drawmode = 0;

	loop
		//if key start, start over after fancy filling effect
		if(checkButton(__START))
			//delete game over text
			delete_text(x);
			delete_text(y);

			//if highscore, delete New Highscore text too
			if(t != 0)
				delete_text(t);
			end

			//working upwards, fill the playfield
			for(x=HIGH;x>=0;x--)
				for(y=0;y<WIDE;y++)
					steen[x][y] = 1;
				end
				frame;
			end
			
			//going back, empty it
			for(x=0;x<HIGH;x++)
				for(y=0;y<WIDE;y++)
					steen[x][y] = 0;
				end
				frame;
			end

			//and start the game over
			game();
			drawmode = 1;
			return;
		end

		frame;
	end

end


/**
	Fills the background with a gradient:
*/
process fill_map()
begin
	for(y=0;y<SCRH;y++)
	  //z = 16+(y*16/240);
	  for(x=0;x<SCRW;x++)
		if (OS_ID==OS_PSP)
		  put_pixel(x,y,rgb(70+y*150/SCRH,70+x*20/SCRW,70+x*20/SCRW));
                else
		  put_pixel(x,y,rgb(70+x*20/SCRW,70+x*20/SCRW,70+y*150/SCRH));
                end
	  end
	end

end

function checkButton(int buttonID)
begin
	if(OS_ID == OS_PSP)	
		return get_joy_button(buttonID);
	else
		return key(buttonID);
	end
end

