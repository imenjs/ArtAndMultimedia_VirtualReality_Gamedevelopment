using UnityEngine;
using System.Collections;

    public class parti_perdu : MonoBehaviour {
    public Texture image ;	
		//private string  text = "space impact 3D. \n realiser par Labidi Imen";
    private int hauteur_bouton = 200 ;
	private int longeur_boutom=50 ;
	
		void OnGUI()
	{
		  GUI.DrawTexture(new Rect(0,0, Screen.width, Screen.height), image);
		//GUI.Label(new Rect(10,10,250,200), text);
		if (GUI.Button(new Rect(Screen.width/2 -hauteur_bouton/2, 
		               Screen.height/2 -longeur_boutom/2,  hauteur_bouton,longeur_boutom),"Game over \n go to the menu")
	                )
	{
		//reisialisation de score de nombre de vie de level et de missed ball
		
		joueur.Score=0;
		joueur.Lives=3;
		joueur.Level=1;
		joueur.Perdus=0;
		//jump pour la level 1 (game)defini dans build setting
		Application.LoadLevel(0);
	  }		
	}
}
