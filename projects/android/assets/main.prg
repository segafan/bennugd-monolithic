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
import "mod_sensor"
import "mod_mouse"
import "mod_joy"

GLOBAL
// Set to your liking
width  = 600;
height = 800;
quit   = 0;

Process Main()
Private
int song=0, num_fingers=0, num_joys=0, num_sensors=0, i=0;
int g_w=0, g_h=0;
int text1=0, text2=0, text3=0, text4=0;
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

    // Write some debug info to the screen
    num_joys = joy_number();
    num_sensors = sensor_number();
    write(0, 320, 0, 2, "Width: "+width+" Height:"+height);
    write(0, 320, 10, 2, "scale_resolution: 0"+scale_resolution);
    write(0, 160, 100, 4, "Detected sensors: "+num_sensors);
    for(i=0; i<num_sensors; i++)
        write(0, 160, 110+10*i, 4, "Sensor "+i+": "+sensor_name(i));
    end;
    write(0, 160, 120+10*num_sensors, 4, "Detected joysticks: "+num_joys);
    for(i=0; i<num_joys; i++)
        write(0, 160, 130+10*(num_sensors+i), 4, "Joy "+i+": "+joy_name(i)+" Axes: "+joy_numaxes(i));
    end;

    /* Some touchscreens cannot detect all 5 fingers at once */
    while(num_fingers < 4 && focus_status == 1)
        sensor_log();
        // Position the pointer
        x = mouse.x; y = mouse.y;

        // Write pointer position according to both mod_mouse and mod_multi
        text1 = write(0, 0, 0,  0, "Multi: "+multi_info(0, "X")+"x"+multi_info(0, "Y"));
        text2 = write(0, 0, 10, 0, "Mouse: "+mouse.x+"x"+mouse.y);

        if(mouse.right)
            point_set(0, graph, 0, 0, 0);
        end;

        text = "";
        if(joy_getaxis(0, 0) < -10000)
            text += " JOY.LEFT "+joy_getaxis(0, 0);
        end
        if(joy_getaxis(0, 0) > 10000)
            text += " JOY.RIGHT "+joy_getaxis(0, 0);
        end
        if(joy_getaxis(0, 1) < -10000)
            text += " JOY.UP "+joy_getaxis(0, 1);
        end
        if(joy_getaxis(0, 1) > 10000)
            text += " JOY.DOWN "+joy_getaxis(0, 1);
        end
        if(joy_getbutton(0, 13))
            text += " LT (13) ";
        end
        if(joy_getbutton(0,14))
            text += " RT (14) ";
        end
        if(joy_getbutton(0,0))
            text += " UP (0) ";
        end
        if(joy_getbutton(0,1))
            text += " DOWN (1) ";
        end
        if(joy_getbutton(0,3))
            text += " RIGHT (3) ";
        end
        if(joy_getbutton(0,2))
            text += " LEFT (2) ";
        end
        if(joy_getbutton(0,5))
            text += " O (5) ";
        end
        if(joy_getbutton(0,8))
            text += " U (8) ";
        end
        if(joy_getbutton(0,9))
            text += " Y (9) ";
        end
        if(joy_getbutton(0,6))
            text += " A (6) ";
        end
        if(joy_getbutton(0,12))
            text += " R1 (12) ";
        end
        if(joy_getbutton(0,11))
            text += " L1 (11) ";
        end
        if(joy_getbutton(0,15))
            text += " Joy press/L3 (15) ";
        end
        if(joy_getbutton(0,16))
            text += " Joy press/R3 (16) ";
        end
        if(joy_getbutton(0,19))
            text += " LT (19) ";
        end
        if(mouse.left)
            text += " M.LEFT ";
        end
        if(mouse.right)
            text += " M.RIGHT ";
        end
        if(mouse.middle)
            text += " M.MIDDLE ";
        end
        text3 = write(0, 160, 140+10*(num_sensors+num_joys), 4, text);
        text4 = write(0, 160, 150+10*(num_sensors+num_joys), 4, "Sensor 2 reading: "+sensor_getaxis(2,0));

        frame;
        delete_text(text1); delete_text(text2); delete_text(text3); delete_text(text4);
    End;

    unload_map(0, graph);

    quit = 1;
    say("Quitting");
End;
