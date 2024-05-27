package com.gamil;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;

public class platp extends Activity {
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
	super.onCreate(savedInstanceState);
	setContentView(R.layout.platp);
	
	
	ImageButton menu = (ImageButton) findViewById(R.id.spaguetti);
	menu.setOnClickListener(new View.OnClickListener() {
		public void onClick(View arg0) {
		//Starting a new Intent=activity
		Intent nextScreen1 = new Intent(getApplicationContext(), spaguetti.class);
		
		//lancement de l'activity 2
		startActivity(nextScreen1);
		}
		});

}
}