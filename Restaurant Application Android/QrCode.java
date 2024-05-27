package com.gamil;

import java.io.InputStream;
import java.net.URL;

import android.app.Activity;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ImageView;

public class QrCode  extends Activity {
    /** Called when the activity is first created. */
	
	ImageView view;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        view = new ImageView(this);
        setContentView(view);
        setImageView("http://encode.i-nigma.com/QRCode/img.php?d=SMSTO%3A25217944%3Ademande%20table%201.%20merci%20de%20patient%C3%A9&c=demande%20reservation&s=4");
    }
    
    private void setImageView(String url){
    	try{
    		view.setImageDrawable(Drawable.createFromStream((InputStream) new URL(url).getContent(), "src"));
    	}catch(Exception e){
    		e.printStackTrace();
    	}
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
    	menu.add(0,100,0,"Line charts");
    	menu.add(0,101,0,"Bar charts");
    	menu.add(0,102,0,"Pie charts");
    	menu.add(0,103,0,"Venn diagrams");
    	menu.add(0,104,0,"Radar charts");
    	menu.add(0,105,0,"Scatter plots");
    	menu.add(0,106,0,"QRCode");
    	menu.add(0,107,0,"Maps");
    	menu.add(0,108,0,"Google-o-meters");
        return true;
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
    	switch(item.getItemId()){
    	case 100:
    		// Line charts
    		setImageView("http://chart.apis.google.com/chart?cht=lxy&chs=200x125&chd=t:10,20,40,80,90,95,99|20,30,40,50,60,70,80|-1|5,25,45,65,85&chco=3072F3,ff0000,00aaaa&chls=2,4,1&chm=s,FF0000,0,-1,5|s,0000ff,1,-1,5|s,00aa00,2,-1,5");
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
    		// Venn diagrams
    		setImageView("http://chart.apis.google.com/chart?cht=v&chs=200x100&chd=t:100,80,60,30,25,20,10");
    		break;
        
    	case 104:
    		// Radar charts
    		setImageView("http://chart.apis.google.com/chart?cht=rs&chs=200x200&chd=s:voJATd9v,MW9BA9&chco=FF0000,FF9900&chls=2.0,4.0,0.0|2.0,4.0,0.0&chxt=x&chxl=0:|0|45|90|135|180|225|270|315&chxr=0,0.0,360.0&chg=25.0,25.0,4.0,4.0&chm=B,FF000080,0,1.0,5.0|B,FF990080,1,1.0,5.0|h,0000FF,0,1.0,4.0|h,3366CC80,0,0.5,5.0|V,00FF0080,0,1.0,5.0|V,008000,0,5.5,5.0|v,00A000,0,6.5,4");
    		break;
        
    	case 105:
    		// Scatter plots
    		setImageView("http://chart.apis.google.com/chart?cht=s&chd=t:12,87,75,41,23,96,68,71,34,9|98,60,27,34,56,79,58,74,18,76|84,23,69,81,47,94,60,93,64,54&chxt=x,y&chxl=0:|0|20|30|40|50|60|70|80|90|10|1:|0|25|50|75|100&chs=200x125");
    		break;
        
    	case 106:
    		// QRCode
    		setImageView("http://chart.apis.google.com/chart?cht=qr&chs=135x135&chl=Hello%20World");
    		break;
       
    	case 107:
    		// Maps
    		setImageView("http://chart.apis.google.com/chart?cht=t&chs=440x220&chd=t:0,100,50,32,60,40,43,12,14,54,98,17,70,76,18,29&chco=FFFFFF,FF0000,FFFF00,00FF00&chld=DZEGMGAOBWNGCFKECGCVSNDJTZGHMZZM&chtm=africa&chf=bg,s,EAF7FE");
    		break;
        
    	case 108:
    		// Google-o-meters
    		setImageView("http://chart.apis.google.com/chart?cht=gom&chd=t:10&chl=Hello%20World&chs=400x200");
    		break;

    	}
    	return true;
    }}
