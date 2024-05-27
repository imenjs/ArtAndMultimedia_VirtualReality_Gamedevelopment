using UnityEngine;
using System.Collections;

public class Scores : MonoBehaviour {

	
	public float V_jeu ;

	
	public static int Score  = 0 ;
	public static  int Shoot  = 10;
	public static int Level   = 1 ;
	public static int Perdus= 0 ;
	public static int Marquer= 0 ;
	public static int Score2=0;
	
	
	
	void OnGUI() 
		
		{
			   //positionnement de la label score,lave,level, espece perdus
			GUI.Label(new Rect(10, 10,120,20), "Score : " + joueur.Score.ToString()) ;
			GUI.Label(new Rect(10, 40,120,20), "shoot : " + joueur.Lives.ToString()) ;
			GUI.Label(new Rect(10, 70,120,20), "Marquer : " + joueur.Level.ToString()) ;
		    GUI.Label(new Rect(10, 100,120,20), "Ballon perdu : " + joueur.Perdus.ToString()) ;
			
			if (GUI.Button(new Rect(500,50,60,30),"Quitter"))
		//appel a la scene (0) (menu principale)
		{
			Application.LoadLevel(3);
			}
		
			}
}
		
		
	