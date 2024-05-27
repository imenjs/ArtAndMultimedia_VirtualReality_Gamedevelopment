using UnityEngine;
using System.Collections;

public class MenuDance2 : MonoBehaviour {

	public Texture image;
void OnGUI() {
		
	GUI.DrawTexture(new Rect(0,0, Screen.width, Screen.height), image);
		
	
	
		
	if (GUI.Button(new Rect(600,80,130,50),"Contre ordi"))
		//appel a la scene (0) (menu principale)
		{
			Application.LoadLevel(16);
			}
		
		if (GUI.Button(new Rect(600,180,130,50),"Deux joueurs"))
		//appel a la scene (0) (menu principale)
		{
			Application.LoadLevel(17);
		}
			
			if (GUI.Button(new Rect(600,260,130,50),"Retour"))
		//appel a la scene (0) (menu principale)
		{
			Application.LoadLevel(3);
			}
			
			}		}

