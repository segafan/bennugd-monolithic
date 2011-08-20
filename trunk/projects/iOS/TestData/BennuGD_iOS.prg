/**
 * iOS accelerometer test
 * in iOS, accelerometers are emulated as joysticks
 * Joseba García Etxebarria - (C) 2011
 * Use as you wish
 */

import "mod_video"
import "mod_joy"
import "mod_text"
import "mod_mouse"
import "mod_wm"
import "mod_map"
import "mod_say"

Process Main()
Private
int vx=0, vy=0;
int w=0, h=0;

Begin
    set_mode(320, 480, 32);
    graph = write_in_map(0, "Tilt your device!", 4);
    x = 160; y = 240;
    write_var(0, 0, 460, 6, focus_status); 
    write_var(0, 0, 470, 6, mouse_status); 
    write_var(0, 0, 480, 6, window_status);
    Repeat
        // Accelerometers are emulated as joysticks in iOS
        // Max-min readings are somewhere around +-6000
        vx += joy_getaxis(0,0)/2000;
        vy -= joy_getaxis(0,1)/2000;
        if(x <= 320-graphic_info(0, graph, G_WIDTH)/2 && vx > 0)
            x += vx;
        end;
        if(x >= graphic_info(0, graph, G_WIDTH)/2 && vx < 0)
            x += vx;
        end;

        if(y <= 480-graphic_info(0, graph, G_HEIGHT)/2 && vy > 0)
            y += vy;
        end;
        if(y >= graphic_info(0, graph, G_HEIGHT)/2 && vy < 0)
            y += vy;
        end;

        // Reset the counters if we're at the border of the screen
        if(x <= 10 || x >= 310)
            vx = 0;
        end;
        if(y <= 10 || y >= 470)
            vy = 0;
        end;

        frame;
    Until(mouse.left)

End;
