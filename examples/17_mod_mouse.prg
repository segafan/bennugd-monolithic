import "mod_mouse"
import "mod_video"
import "mod_say"
import "mod_timers"
import "mod_map"
import "mod_sound"

Process main()
Private
    int song=0;

Begin
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(640, 480, 16, MODE_WINDOW))
        return -1;
    end;
    set_mode(640, 480, 16, MODE_WINDOW);
    // Load a few things and display them
    mouse.graph = png_load("mouse.png");
    song = load_song("game.s3m");
    play_song(song, 0);
    //map_save(0, mouse.graph, "mouse.map");
    while(! mouse.left)
        FRAME;
    end;
    //Unload stuff
    unload_map(0, mouse.graph);
    stop_song();
    unload_song(song);
End;
