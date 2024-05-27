using UnityEngine;
using System.Collections;
    
	
    public class menu : MonoBehaviour {
    private string  text = "space impact 3D. \n realiser par Labidi Imen";
	public Texture image ;	
	private int hauteur_bouton = 170 ;
	private int longeur_boutom=50 ;
		
	void OnGUI()
	{
		 GUI.DrawTexture(new Rect(0,0, Screen.width, Screen.height), image);
		GUI.Label(new Rect(10,10,250,200), text);
		
		if (GUI.Button(new Rect(180,   Screen.height/2 -longeur_boutom/2,  hauteur_bouton,longeur_boutom),"Mode complet")
	                )
	{
		Application.LoadLevel(1);
	  
	}
	
	else if (GUI.Button(new Rect(210,270,hauteur_bouton,longeur_boutom),"Mode d'entrainement"))
	{
		Application.LoadLevel(7);
}

else if (GUI.Button(new Rect(240,340,hauteur_bouton,longeur_boutom),"Instructions"))
	{
		Application.LoadLevel(9);
}
}
}