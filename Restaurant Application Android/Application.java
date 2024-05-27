package com.gamil;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;

public class Application extends Activity {
	// Initializing variables
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
	super.onCreate(savedInstanceState);
	setContentView(R.layout.accueil);
	
	ImageButton menuP = (ImageButton) findViewById(R.id.menuP);
	//Listening to button event 
	//action sur un bouton
	
	menuP.setOnClickListener(new View.OnClickListener() {
	public void onClick(View arg0) {
	//Starting a new Intent=activity
	Intent nextScreen = new Intent(getApplicationContext(), menuprincipale.class);
	
	//lancement de l'activity 2
	startActivity(nextScreen);
	}
	});
	
	ImageButton menu = (ImageButton) findViewById(R.id.menu);
	menu.setOnClickListener(new View.OnClickListener() {
		public void onClick(View arg0) {
		//Starting a new Intent=activity
		Intent nextScreen1 = new Intent(getApplicationContext(), menudujour.class);
		
		//lancement de l'activity 2
		startActivity(nextScreen1);
		}
		});
	
	
	}
}