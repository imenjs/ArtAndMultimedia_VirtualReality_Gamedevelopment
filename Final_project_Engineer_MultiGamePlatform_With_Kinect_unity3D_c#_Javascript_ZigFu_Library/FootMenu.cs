using UnityEngine;
using System.Collections;

public class FootMenu: MonoBehaviour {

	
	public Texture image ;	
		
	void OnGUI()
	{
		 GUI.DrawTexture(new Rect(0,0, Screen.width, Screen.height), image);
		if (Input.anyKeyDown)
			
		Application.LoadLevel(4);
		
	}
}
