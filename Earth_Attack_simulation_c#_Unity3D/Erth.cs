using UnityEngine;
using System.Collections;

public class Erth : MonoBehaviour {

	public float moveSpeed = 8;
	
    public float turnSpeed = 10;
	private float lastdistance = 0;
	
	public GameObject object_astroid ;
	public GameObject distancegui ; 
	public GameObject velocitygui ;
	public static float distance ;
	
	
	void star ()
	
	{
		
		//object_astroid = GameObject.FindWithTag("asteroid");
		
	}
	
	
    void Update ()
    
	{
		
		// Calculate distance between earth and astroid
		
		 distance = Vector3.Distance(transform.position , object_astroid.transform.position);
		
		distancegui.guiText.text = "distance" + distance.ToString() ;
		
	// define danger
		
		if ((distance <100) )
		{
			velocitygui.guiText.text = "SafetyZone = Danger"  ;
				
		}
		else {
			
			velocitygui.guiText.text = "SafetyZone = Safe";
			
		}
		
     // mvt eart 2D (right, left)
        
        if(Input.GetKey(KeyCode.LeftArrow))
			
            transform.Translate(Vector3.left * moveSpeed * Time.deltaTime);
			//transform.Rotate(Vector3.up, -turnSpeed * Time.deltaTime);
        
        if(Input.GetKey(KeyCode.RightArrow))
			
			transform.Translate(Vector3.right * moveSpeed * Time.deltaTime);
            //transform.Rotate(Vector3.up, turnSpeed * Time.deltaTime); 
		
    }
	
	
	
}
