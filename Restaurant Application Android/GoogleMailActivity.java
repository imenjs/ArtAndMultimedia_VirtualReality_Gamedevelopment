package com.gamil;

import android.app.Activity;
//import java.io.InputStream;
//import java.net.URL;

//import android.app.Activity;
import android.content.Intent;
//import android.graphics.drawable.Drawable;
import android.os.Bundle;
//import android.view.Menu;
//import android.view.MenuItem;
import android.view.View;
//import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;

//import android.os.Bundle;
//import android.view.Menu;
//import android.view.MenuItem;

public class GoogleMailActivity extends Activity {
	ImageView view;
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
    	 view = new ImageView(this);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
    
    
 
    ImageButton menuP = (ImageButton) findViewById(R.id.application);
	//Listening to button event 
	//action sur un bouton
	
	menuP.setOnClickListener(new View.OnClickListener() {
	public void onClick(View arg0) {
	//Starting a new Intent=activity
	Intent nextScreen = new Intent(getApplicationContext(), Application.class);
	
	//lancement de l'activity 2
	startActivity(nextScreen);
	}
	});
	
	ImageButton menu = (ImageButton) findViewById(R.id.qrcode);
	menu.setOnClickListener(new View.OnClickListener() {
		public void onClick(View arg0) {
		//Starting a new Intent=activity
		Intent nextScreen1 = new Intent(getApplicationContext(), QrCode.class);
		
		//lancement de l'activity 2
		startActivity(nextScreen1);
		}
		});
	
	ImageButton menu3 = (ImageButton) findViewById(R.id.geolocalisation);
	menu3.setOnClickListener(new View.OnClickListener() {
		public void onClick(View arg0) {
		//Starting a new Intent=activity
		Intent nextScreen3 = new Intent(getApplicationContext(), Gmap.class);
		
		//lancement de l'activity 2
		startActivity(nextScreen3);
		}
		});

    
}}


    /*
    private void setImageView(String url){
    	try{
    		view.setImageDrawable(Drawable.createFromStream((InputStream) new URL(url).getContent(), "src"));
    	}catch(Exception e){
    		e.printStackTrace();
    	}
    }
}*/
/*
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
    	menu.add(0,100,0,"googleMap");
    	menu.add(0,101,0,"lireQrCode");
    	menu.add(0,102,0,"Application");
    	menu.add(0,103,0,"siteWeb");
    	
    	
        return true;
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
    	
    	switch(item.getItemId()){
    	case 100:
    		//setImageView("http://chart.apis.google.com/chart?cht=lxy&chs=200x125&chd=t:10,20,40,80,90,95,99|20,30,40,50,60,70,80|-1|5,25,45,65,85&chco=3072F3,ff0000,00aaaa&chls=2,4,1&chm=s,FF0000,0,-1,5|s,0000ff,1,-1,5|s,00aa00,2,-1,5");
    		// Line charts
    	Button	menu = (Button) findViewById(R.id.imageView1);
    
    		menu.setOnClickListener(new View.OnClickListener() {
    			public void onClick(View arg0) {
    			//Starting a new Intent=activity
    			Intent nextScreen1 = new Intent(getApplicationContext(), QrCode.class);
    			
    			//lancement de l'activity 2
    			startActivity(nextScreen1);
    			}
    			});
    		
    		    		break;
    		
    	case 101:    		
        	// Bar charts
        	setImageView("http://chart.apis.google.com/chart?cht=bvg&chs=200x125&chd=s:hello,world&chco=4d89f9,c6d9fd");
        	break;
    	
    	case 102:
    		// Pie charts
    		setImageView("http://chart.apis.google.com/chart?cht=p3&chd=s:Uf9a&chs=250x100&chl=January|February|March|April");;
    		break;
    		
    		
    	case 103:
    		// Pie charts
    		setImageView("http://imen-abidi.e-monsite.com/");;
    		break;
    		
    	    	}
    	return true;

    }
    
    
}*/