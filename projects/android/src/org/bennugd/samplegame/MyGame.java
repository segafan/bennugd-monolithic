package org.bennugd.samplegame;

import org.libsdl.app.SDLActivity;
import android.os.Bundle;


/*
 * A sample wrapper class that just calls SDLActivity
 */

public class MyGame extends SDLActivity {
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    protected void onDestroy() {
        super.onDestroy();
    }
}
