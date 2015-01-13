package net.lnmcc.testobdbroadcast;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class OBDReceiver extends BroadcastReceiver {
    private static final String TAG = "OBDReceiver";

    @Override
    public void onReceive(Context context, Intent intent) {
        Log.d(TAG, "lnmcc: received OBD broadcast");
    }
}
