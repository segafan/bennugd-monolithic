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
import "mod_sound"
import "mod_wm"
import "mod_map"
import "mod_say"

GLOBAL
// Set to your liking
width  = 320;
height = 480;
sound  = 1;
quit   = 0;

Process bouncer()
Private
    int vx=3, vy=3;
    int w=0, h=0;

Begin
    say("Hi!");
    graph = load_png("Icon.png");
    // Position the graphic onscreen
    w = graphic_info(0, graph, G_WIDTH);
    h = graphic_info(0, graph, G_HEIGHT);
    x = width/2;
    y = height/2;
    while(quit == 0)
        if(x + vx + w/2 >= width || x + vx - w/2 < 0)
            vx = -vx;
        end
        if(y + vy + h/2 >= height || y + vy - h/2 < 0)
            vy = -vy;
        end
        x += vx; y += vy;
        if(mouse.left)
            x = mouse.x; y = mouse.y;
        end;
        FRAME;
    End;
End;

Process Main()
Private
int vx=0, vy=0;
int w=0, h=0;
int song=0;

Begin
    //set_mode(width, height, 32, MODE_FULLSCREEN|MODE_FRAMELESS);
    // Get the real screen resolution we're running at
    width = graphic_info(0, -1, G_WIDTH);
    height = graphic_info(0, -1, G_HEIGHT);
    say_fast("Running at "+width+"x"+height);
    bouncer();
    if(sound == 1)
        song = load_song("1.ogg");
        play_song(song, 0);
    end;
    graph = write_in_map(0, "Tilt your device!", 4);
    x = width/2; y = height/2;
    write_var(0, 0, 460, 6, focus_status); 
    write_var(0, 0, 470, 6, mouse_status); 
    write_var(0, 0, 480, 6, window_status);
    LOOP
        // Accelerometers are emulated as joysticks in iOS
        // Max-min readings are somewhere around +-6000
        vx += joy_getaxis(0,0)/2000;
        vy -= joy_getaxis(0,1)/2000;
        if(x <= width-graphic_info(0, graph, G_WIDTH)/2 && vx > 0)
            x += vx;
        end;
        if(x >= graphic_info(0, graph, G_WIDTH)/2 && vx < 0)
            x += vx;
        end;

        if(y <= height-graphic_info(0, graph, G_HEIGHT)/2 && vy > 0)
            y += vy;
        end;
        if(y >= graphic_info(0, graph, G_HEIGHT)/2 && vy < 0)
            y += vy;
        end;

        // Reset the counters if we're at the border of the screen
        if(x <= 10 || x >= width-10)
            vx = 0;
        end;
        if(y <= 10 || y >= height-10)
            vy = 0;
        end;

        frame;
    End;

    unload_map(0, graph);
    if(sound == 1)
        unload_song(song);
    end

    quit = 1;
End;
