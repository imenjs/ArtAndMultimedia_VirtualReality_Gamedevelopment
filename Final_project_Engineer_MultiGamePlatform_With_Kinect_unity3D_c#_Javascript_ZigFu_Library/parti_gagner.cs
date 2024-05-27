using UnityEngine;
using System.Collections;

public class parti_gagner1 : MonoBehaviour {
public Texture image ;	
	
	private int hauteur_bouton = 200 ;
	private int longeur_boutom=50 ;
	
		void OnGUI()
	{
		  GUI.DrawTexture(new Rect(0,0, Screen.width, Screen.height), image);
		//GUI.Label(new Rect(10,10,250,200), text);
		if (GUI.Button(new Rect(130, 150,  hauteur_bouton,longeur_boutom),"continuer")
	                )
	{
		//reisialisation de score de nombre de vie de level et de missed ball
		joueur.Score2=0;
		//joueur.Score=0;
		//joueur.Lives=3;
		//joueur.Level=1;
		//joueur.Perdus=0;
		//jump pour la level 2 defini dans build setting
		Application.LoadLevel(5);
	  }	
else if (GUI.Button(new Rect(160, 250, hauteur_bouton, longeur_boutom),"rejouer"))
	{
		//reisialisation de score de nombre de vie de level et de missed ball
		joueur.Score2=0;
		joueur.Score=0;
		joueur.Lives=3;
		joueur.Level=1;
		joueur.Perdus=0;
//		jump pour la level 2 defini dans build setting
		Application.LoadLevel(1);
	  }		
	  else if (GUI.Button(new Rect(190, 350,hauteur_bouton,longeur_boutom),"menu"))
	  {
		  Application.LoadLevel(0);
		  }
	  
	  }
}