import "mod_say";
import "mod_joy";

// Wiimote example code
// To get the Wiimote (also, nunchuck and gamecube controller) button codes,
// go to:
// http://wiibrew.org/wiki/SDL_Wii
Process main()
Private
	int n=0, i=0, die=0, joy=0;
Begin
	n = joy_number();	// Get the number of available joysticks
	if(n > 0)
    	say("There are "+n+" joysticks available");
	    say("Joystick names and available buttons:");// Display the names for all the joysticks
        say("=====================================");
        for(i=0; i<n; i++)
            say("Joy["+i+"]: "+joy_name(i)+" has "+joy_numbuttons(i)+" buttons");
        end;
        say("");    // Empty line
        say("Press (A) in your Wiimote to continue");
        while(die == 0)
            for(i=0; i<n; i++)
                if(joy_getbutton(i, 0))
                    joy = i;
                    say("You pressed (A) in Wiimote "+joy);
                    die = 1;
                end;
            end;
            FRAME;
        end;
        say("Great, now press the (HOME) button on that Wiimote to quit");
        die=0;
        while(die == 0)
            if(joy_getbutton(joy, 6))
                say("Great, bye!");
                die = 1;
            end;
            FRAME;
        end;
    else
        say("Please, plug in a joystick to be able to use this code");
    end;
End;
