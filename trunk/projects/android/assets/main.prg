/**
 * Android test
 * Joseba García Etxebarria - (C) 2012
 * Use as you wish
 */

import "mod_video"
import "mod_map"
import "mod_sys"
import "mod_text"
import "mod_multi"
import "mod_wm"

Process Main()
Private
    int width, height, num_fingers;

Begin
    width = graphic_info(0, 0, G_WIDTH);
    height = graphic_info(0, 0, G_HEIGHT);
    write(0, width/2, height/2, 4, "Touch the screen to open the browser");
    
    /* Some touchscreens cannot detect all 5 fingers at once */
    while(num_fingers < 1 && focus_status == 1)
        num_fingers = multi_numpointers();
        
        FRAME;
    end
    
    // Quit our app so that we don't stay idle on the background
    exec(_P_NOWAIT, "http://forum.bennugd.org", 0, 0);
End

