package com.gamil;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;

public class menuprincipale extends Activity {
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
	super.onCreate(savedInstanceState);
	setContentView(R.layout.menuprincipale);
	
	// Receiving the Data
	
	
	ImageButton menuP = (ImageButton) findViewById(R.id.plat);
	//Listening to button event 
	//action sur un bouton
	
	menuP.setOnClickListener(new View.OnClickListener() {
	public void onClick(View arg0) {
	//Starting a new Intent=activity
	Intent nextScreen = new Intent(getApplicationContext(), platp.class);
	
	//lancement de l'activity 2
	startActivity(nextScreen);
	}
	});
	
	ImageButton menu = (ImageButton) findViewById(R.id.dessert);
	menu.setOnClickListener(new View.OnClickListener() {
		public void onClick(View arg0) {
		//Starting a new Intent=activity
		Intent nextScreen1 = new Intent(getApplicationContext(), dessert.class);
		
		//lancement de l'activity 2
		startActivity(nextScreen1);
		}
		});
	
	}
	}