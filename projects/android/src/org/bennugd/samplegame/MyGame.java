package org.bennugd.samplegame;

import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;

import org.libsdl.app.SDLActivity;
import android.os.Bundle;
import android.widget.LinearLayout;


/*
 * A sample wrapper class that just calls SDLActivity
 */

public class MyGame extends SDLActivity {
    private AdView adView;
    
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.main);

        // Create the adView, please replace MY_AD_UNIT_ID
        // with your real AdMob publisher ID
        adView = new AdView(this, AdSize.BANNER, MY_AD_UNIT_ID);

        // Add the ad to super's Layout
        super.mLayout.addView(adView);

        // Create an ad request. Check logcat output for the hashed device ID to
        // get test ads on a physical device.
        AdRequest adRequest = new AdRequest();
        adRequest.addTestDevice(AdRequest.TEST_EMULATOR);

        // Initiate a generic request to load it with an ad
        adView.loadAd(new AdRequest());
    }
    
    protected void onDestroy() {
        if (adView != null) {
            adView.destroy();
        }
        super.onDestroy();
    }
}
