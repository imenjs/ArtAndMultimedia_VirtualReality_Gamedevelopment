using UnityEngine;
using System.Collections;

public class help : MonoBehaviour {
private string  text = "right click on mouse : to generate asteroid and to move it. \n right and left keyboard arrow :  to move the earth in 2D world. \n safetyZone is 100Km if  the astroide exceeds the turret will shoot on him." ; 
				public Texture image;
	//afficher le text du help
	void OnGUI() {
		
	GUI.DrawTexture(new Rect(0,0, Screen.width, Screen.height), image);
		GUI.Label(new Rect(200,250,350,300), text);
		
	if (GUI.Button(new Rect(500,50,60,30),"Start"))
		//appel a la scene (0) (menu principale)
		{
			Application.LoadLevel(0);
			}
		}
		
	
}
