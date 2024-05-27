using UnityEngine;
using System.Collections;
    
	
    public class menu2 : MonoBehaviour {
    //private string  text = "choisissez un niveaux d'entrainement";
	public Texture image ;	
	private int hauteur_bouton = 200 ;
	private int longeur_boutom=50 ;
		
	void OnGUI()
	{
GUI.DrawTexture(new Rect(10,10, Screen.width, Screen.height), image);
	//	GUI.Label(new Rect(100,100,250,200), text);
		
		if (GUI.Button(new Rect(120,150,  hauteur_bouton,longeur_boutom),"Level 1")
	                )
	{
		Application.LoadLevel(1);
	  
	}
	
	if (GUI.Button(new Rect(150,200 ,  hauteur_bouton,longeur_boutom),"Level 2")
	                )
	{
		Application.LoadLevel(5);
	  
	}
	
	if (GUI.Button(new Rect(180,250,  hauteur_bouton,longeur_boutom),"Level 3")
	                )
	{
		Application.LoadLevel(6);
	  
	}
	
	if (GUI.Button(new Rect(210, 300,  hauteur_bouton,longeur_boutom),"returne")
	                )
	{
		Application.LoadLevel(0);
	  
	}
	
}
}