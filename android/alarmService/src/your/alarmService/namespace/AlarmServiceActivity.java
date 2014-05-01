package your.alarmService.namespace;

import android.app.Activity;
import android.os.Bundle;
import android.app.PendingIntent;
import android.content.Intent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class AlarmServiceActivity extends Activity implements OnClickListener {
    /** Called when the activity is first created. */
	private static alarmService appRef = null;
	private Button b_call_Service, b_exit_Service;
	boolean k = false;
	
    @Override
    public void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        appRef = this;
        setContentView(R.layout.main);
        b_all_Service = (Button)findViewById(R.id.call_alarm_Service);
    }
    
    
}