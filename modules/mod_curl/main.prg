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
    int i=0;
Begin
    set_mode(width, height, 16);
    
    bouncer();

    write(0, width/2, height/2, 4, "Click on the screen to start download");
    while(! mouse.left)
        FRAME;
    end;
    
    // Start transfer
    curl_get("http://forum.bennugd.org", "BennuGD forums.html");
    
    while(curl_info(0, 1) == 0)
        FRAME;
    end;
    
    say("Download done!");

    delete_text(ALL_TEXT);
    write(0, width/2, height/2, 4, "Rigth Click on the screen again to quit");
    while(! mouse.right)
        FRAME;
    end;
    quit=1;
End;