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
import "mod_sys"

GLOBAL
// Set to your liking
width  = 600;
height = 800;
quit   = 0;

Process Main()
Private
int song=0, num_fingers=0, i=0;

Begin
    // Get the real screen resolution we're running at
    width = graphic_info(0, 0, G_WIDTH);
    height = graphic_info(0, 0, G_HEIGHT);
    // Set scale_resolution to width/2xheight/2
    //scale_resolution = width*10000+height;
    //set_mode(width, height, 32);
    
    write(0, 0,  0, 0, "Width: "+width+" Height:"+height);
    write(0, 0, 10, 0, "scale_resolution: 0"+scale_resolution);
    
    graph = map_new(width, height, 32);
    x = width/2; y = height/2;

    write_var(0, 0, height, 6, num_fingers);
    drawing_map(0, graph);
    drawing_color(rgb(0, 255, 255));

    /* Some touchscreens cannot detect all 5 fingers at once */
    while(num_fingers < 4 && focus_status == 1)
        // Store the total amount of fingers touching the screen
	if(mouse.left)
            exec(_P_WAIT, "https://twitter.com/intent/tweet?text=@panreyes, Something like this?&url=http://code.google.com/p/bennugd-monolithic/source/browse/trunk/projects/android/assets/main.prg", 0, 0);
            break;
        end
        frame;
    End;

    unload_map(0, graph);

    quit = 1;
    say("Quitting");
End;
