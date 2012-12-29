/**
 * Android test
 * Joseba García Etxebarria - (C) 2012
 * Use as you wish
 */

import "mod_video"
import "mod_map"
import "mod_draw"
import "mod_say"
import "mod_file"
import "mod_text"
import "mod_wm"
import "mod_multi"
import "mod_mouse"
import "mod_joy"

GLOBAL
// Set to your liking
width  = 600;
height = 800;
quit   = 0;

Process Main()
Private
int song=0, num_fingers=0, num_joys=0, i=0;
int g_w=0, g_h=0;
int text1=0, text2=0, text3=0;
string text;

Begin
    // Get the real screen resolution we're running at
    width = graphic_info(0, 0, G_WIDTH);
    height = graphic_info(0, 0, G_HEIGHT);
    // Set scale_resolution to width/2xheight/2
    scale_resolution = width*10000+height;
    scale_resolution_aspectratio=SRA_PRESERVE;
    set_mode(320, 480, 32);

    // Paint the background red so that you know what it looks like
    drawing_color( rgb(255,0,0) );
    drawing_map( 0, 0 );
    draw_box(0, 0, width, height);

    // Load mouse pointer and get its props
    graph = load_png("mouse.png");
    g_w = graphic_info(0, graph, G_WIDTH);
    g_h = graphic_info(0, graph, G_HEIGHT);

	// Write some debug info to the screen
	num_joys = joy_number();
	write(0, 320, 0, 2, "Width: "+width+" Height:"+height);
	write(0, 320, 10, 2, "scale_resolution: 0"+scale_resolution);
	write(0, 160, 240, 4, "Detected joysticks: "+num_joys);
	for(i=0; i<num_joys; i++)
		write(0, 160, 250+10*i, 4, joy_name(i)+" Axes: "+joy_numaxes(i));
	end;
	
    /* Some touchscreens cannot detect all 5 fingers at once */
    while(num_fingers < 4 && focus_status == 1)
        // Position the pointer
        x = mouse.x+g_w/2; y = mouse.y+g_h/2;
		
		// Write pointer position according to both mod_mouse and mod_multi
		text1 = write(0, 0, 0,  0, "Multi: "+multi_info(0, "X")+"x"+multi_info(0, "Y"));
		text2 = write(0, 0, 10, 0, "Mouse: "+mouse.x+"x"+mouse.y);
		
		text = "";
		if(joy_getbutton(0, 0))
			text += " UP ";
		end
		if(joy_getbutton(0,1))
			text += " DOWN ";
		end
		if(joy_getbutton(0,2))
			text += " LEFT ";
		end
		if(joy_getbutton(0,3))
			text += " RIGHT ";
		end
		if(joy_getbutton(0,4))
			text += " CENTER ";
		end
		if(joy_getbutton(0,5))
			text += " A ";
		end
		if(joy_getbutton(0,6))
			text += " B ";
		end
		if(joy_getbutton(0,7))
			text += " C ";
		end
		if(joy_getbutton(0,8))
			text += " X ";
		end
		if(joy_getbutton(0,9))
			text += " Y ";
		end
		if(joy_getbutton(0,10))
			text += " Z ";
		end
		if(joy_getbutton(0,11))
			text += " L1 ";
		end
		if(joy_getbutton(0,12))
			text += " R1 ";
		end
		if(joy_getbutton(0,13))
			text += " L2 ";
		end
		if(joy_getbutton(0,14))
			text += " R2 ";
		end
		if(joy_getbutton(0,15))
			text += " THUMBL ";
		end
		if(joy_getbutton(0,16))
			text += " THUMBR ";
		end
		if(joy_getbutton(0,17))
			text += " START ";
		end
		if(joy_getbutton(0,18))
			text += " SELECT ";
		end
		if(joy_getbutton(0,19))
			text += " MODE ";
		end
		if(joy_getbutton(0,20))
			text += " 1 ";
		end
		if(joy_getbutton(0,21))
			text += " 2 ";
		end
		if(joy_getbutton(0,22))
			text += " 3 ";
		end
		if(joy_getbutton(0,23))
			text += " 4 ";
		end
		if(joy_getbutton(0,24))
			text += " 5 ";
		end
		if(joy_getbutton(0,25))
			text += " 6 ";
		end
		if(joy_getbutton(0,26))
			text += " 7 ";
		end
		if(joy_getbutton(0,27))
			text += " 8 ";
		end
		if(joy_getbutton(0,28))
			text += " 9 ";
		end
		if(joy_getbutton(0,29))
			text += " 10 ";
		end
		if(joy_getbutton(0,30))
			text += " 11 ";
		end
		if(joy_getbutton(0,31))
			text += " 12 ";
		end
		if(joy_getbutton(0,32))
			text += " 13 ";
		end
		if(joy_getbutton(0,33))
			text += " 14 ";
		end
		if(joy_getbutton(0,34))
			text += " 15 ";
		end
		if(joy_getbutton(0,35))
			text += " 16 ";
		end
		if(mouse.left)
			say("Left");
			text += " M.LEFT ";
		end
		if(mouse.right)
			say("Right");
			text += " M.RIGHT ";
		end
		if(mouse.middle)
			say("middle");
			text += " M.MIDDLE ";
		end
		text3 = write(0, 160, 260+10*i, 4, text);
		
        frame;
		delete_text(text1); delete_text(text2); delete_text(text3);
    End;

    unload_map(0, graph);

    quit = 1;
    say("Quitting");
End;
