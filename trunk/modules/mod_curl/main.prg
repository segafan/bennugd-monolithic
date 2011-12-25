import "mod_video"
import "mod_curl"
import "mod_say"
import "mod_mouse"
import "mod_text"
import "mod_map"
import "mod_file"

Global
int width = 1024;
int height = 768;
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
    
    // Remove Google logo, if it exists already
    if(file_exists("classicplus.png"))
        fremove("classicplus.png");
        say("Removed existing logo");
    end;
    
    bouncer();
    
    say("Starting download");
    
    // Start libcurl, set options, perform transfer
    curl = curl_init();
    if(curl == -1)
        say("Curl initialisation failed, quitting");
        quit = 1;
        return;
    end;
    
    curl_setopt(curl, CURLOPT_NOPROGRESS,    1);
    // Use this to write to a file
    //curl_setopt(curl, CURLOPT_WRITEDATA, "classicplus.png");
    // Use this to download to a string
    curl_setopt(curl, CURLOPT_WRITEDATA, &output);
    curl_setopt(curl, CURLOPT_URL, "http://www.google.es/");
    
    curl_perform(curl, &status);
    
    // Wait for the transfer to finish
    while(status != 0)
        FRAME;
    end;
    
    //output = curl_fetch(curl);
    
    write(0, 0, 0, 0, output);
    
    curl_cleanup(curl);
    
    // Replace the bouncer image by the google logo we just downloaded
    //unload_map(0, son.graph);
    //son.graph = load_png("classicplus.png");
    
    say("Download done!");

    while(! mouse.right)
        FRAME;
    end;
    quit=1;
End;