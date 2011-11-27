import "mod_video"
import "mod_curl"
import "mod_say"
import "mod_mouse"
import "mod_text"
import "mod_map"

Global
int width = 640;
int height = 480;
int quit=0;
end;

Process bouncer()
Private
    int vx=3, vy=3;

Begin
    graph = load_png("Icon.png");
    // Position the graphic onscreen
    x = 10+graphic_info(0, GRAPH, G_WIDTH);
    y = 10+graphic_info(0, GRAPH, G_HEIGHT);
    while(quit == 0)
        if(x + vx >= width || x+vx < 0)
            vx = -vx;
        end
        if(y+vy >= height || y+vy < 0)
            vy = -vy;
        end
        x += vx; y += vy;
        FRAME;
    End;
End;

Process main()
Private
    int i=0, status=0, curl=0;

Begin
    curl_global_init();
    set_mode(width, height, 16);
    
    bouncer();

    write(0, width/2, height/2, 4, "Click on the screen to start download");
    while(! mouse.left)
        FRAME;
    end;
    
    // Start libcurl, set options, perform transfer
    curl = curl_init();
    if(curl == -1)
        say("Curl initialisation failed, quitting");
        quit = 1;
        return;
    end;
    
    curl_setopt(curl, 43,    1);
    say(1);
    curl_setopt(curl, 10001, "BennuGD forums.html");
    say(2);
    curl_setopt(curl, 10002, "http://forum.bennugd.org");
    say(3);
    
    curl_perform(curl, &status);
    
    // Wait for the transfer to finish
    while(status != 0)
        FRAME;
    end;
    
    curl_cleanup(curl);
    curl_global_cleanup();
    
    say("Download done!");

    delete_text(ALL_TEXT);
    write(0, width/2, height/2, 4, "Rigth Click on the screen again to quit");
    while(! mouse.right)
        FRAME;
    end;
    quit=1;
End;