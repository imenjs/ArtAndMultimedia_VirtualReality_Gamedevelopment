package com.gamil;

import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.graphics.drawable.Drawable;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.widget.Toast;

import com.google.android.maps.GeoPoint;
import com.google.android.maps.ItemizedOverlay;
import com.google.android.maps.MapActivity;
import com.google.android.maps.MapController;
import com.google.android.maps.MapView;
import com.google.android.maps.OverlayItem;

public class Gmap extends MapActivity implements LocationListener {
	
	
	MapView maMap;
	MapController monControleur;
	double latitude    = 36.549362;
	double longitude   = 8.7711111;
	
	double latitude1    = 36.985003;
	double longitude1   = 9.420776;
	
	
	@Override
		
	   public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.gmap);
        maMap = (MapView)findViewById(R.id.myGmap);
        maMap.setBuiltInZoomControls(true);
        
        GeoPoint point = new GeoPoint(microdegrees(latitude),microdegrees( longitude));
        
        MonOverLay object = new MonOverLay(getResources().getDrawable(R.drawable.iconemap));
        object.addPoint(point);
        
        
        //GeoPoint point2 = new GeoPoint(microdegrees(latitude1),microdegrees( longitude1));
        
        //MonOverLay object1 = new MonOverLay(getResources().getDrawable(R.drawable.iconeposition));
        //object1.addPoint(point2);
        
        
        
        maMap.getOverlays().add(object);
       // maMap.getOverlays().add(object1);
        
        maMap.setSatellite(true);
        
        
        monControleur = maMap.getController() ; 
        monControleur.setZoom(12);
        monControleur.setCenter(point);
        
        LocationManager Im =(LocationManager)getSystemService(Context.LOCATION_SERVICE);
        Im.requestLocationUpdates(LocationManager.GPS_PROVIDER, 1000L, 500.0f, this);
	}

	private int microdegrees(double value){
		return (int)(value*1000000);
	}
	
	@Override
	protected boolean isRouteDisplayed() {
		return false;
}
	
public class MonOverLay extends ItemizedOverlay<OverlayItem>{

		List<GeoPoint> points = new ArrayList<GeoPoint>();
	
	public MonOverLay(Drawable defaultMarker) {
		super(boundCenterBottom(defaultMarker));
		// TODO Auto-generated constructor stub
	}

	@Override
	protected OverlayItem createItem(int i) {
		
		GeoPoint point = points.get(i);
		
		return new OverlayItem(point,"Titre","Description");
	}

	@Override
	public int size() {
		
		return  points.size();
	}
	
	public void addPoint(GeoPoint point){
		this.points.add(point);
		populate();
		
		
	}
	
}

public void onLocationChanged(Location location) {
	if(location !=null){
		
		Toast.makeText(this, "NouvellePosition: "+location.getLatitude()+location.getLongitude(), Toast.LENGTH_LONG);
		monControleur.animateTo(new GeoPoint(microdegrees(location.getLatitude()),microdegrees(location.getLongitude() )));
	
	} 
	
}

public void onProviderDisabled(String provider) {
	// TODO Auto-generated method stub
	
}

public void onProviderEnabled(String provider) {
	// TODO Auto-generated method stub
	
}

public void onStatusChanged(String arg0, int arg1, Bundle arg2) {
	// TODO Auto-generated method stub
	
}
}