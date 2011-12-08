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
    string output;

Begin
    set_mode(width, height, 16);
    
    bouncer();
    
    // Start libcurl, set options, perform transfer
    curl = curl_init();
    if(curl == -1)
        say("Curl initialisation failed, quitting");
        quit = 1;
        return;
    end;
    
    curl_setopt(curl, CURLOPT_NOPROGRESS,    1);
    // Use this to write to a file
    //curl_setopt(curl, CURLOPT_WRITEDATA, "BennuGD forums.html");
    // Use this to download to a string
    curl_setopt(curl, CURLOPT_WRITEDATA, 0);
    curl_setopt(curl, CURLOPT_URL, "http://forum.bennugd.org");
    
    curl_perform(curl, &status);
    
    // Wait for the transfer to finish
    while(status != 0)
        FRAME;
    end;
    
    output = curl_fetch(curl);
    
    write(0, 0, 0, 0, output);
    
    curl_cleanup(curl);
    
    say("Download done!");

    while(! mouse.right)
        FRAME;
    end;
    quit=1;
End;