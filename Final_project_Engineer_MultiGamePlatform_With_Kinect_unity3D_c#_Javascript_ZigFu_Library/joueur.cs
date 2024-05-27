using UnityEngine;
using System.Collections;

public class joueur : MonoBehaviour {

	
	public float V_jeu ;
	public GameObject prefabrication_bombe;
	public GameObject prefabrication_explosion ;
	
	public static int Score  = 0 ;
	public static  int Lives  = 5;
	public static int Level   = 1 ;
	public static int Perdus= 0 ;
	public static int Score2=0;
	
	void Update () 
	{
	    // initialisation de mouvement
		float mouvement =Input.GetAxisRaw("Horizontal") *V_jeu  * Time.deltaTime  ;
        
		// mouvement de joueur
		transform.Translate(Vector3.right * mouvement) ;		
		
		if (transform.position.x <= -10.5f)
			transform.position = new Vector3 (10.4f, transform.position.y, transform.position.z);
		
		    else if (transform.position.x >= 10.5f )
		     	transform.position = new Vector3 (-10.4f, transform.position.y, transform.position.z);
	   
		if (Input.GetKeyDown("space"))
		{		
		
			// loncer les bonbe
			// prefabrication_bombe : une bonbe est fabrique , puis elle sera definir come prefab alors enne sera repeter au tant qu'ont le veux
			Vector3 position= new Vector3 (transform.position.x,  transform.position.y + (collider.bounds.size.y/2));
	    	 Instantiate (prefabrication_bombe, position , Quaternion.identity) ;
			//il nous faux l'ajout de bouton initiale 
			}		
		}
		void OnGUI() 
		{
			   //positionnement de la label score,lave,level, espece perdus
			GUI.Label(new Rect(10, 10,120,20), "Score : " + joueur.Score.ToString()) ;
			GUI.Label(new Rect(10, 40,120,20), "Lives : " + joueur.Lives.ToString()) ;
			GUI.Label(new Rect(10, 70,120,20), "Level : " + joueur.Level.ToString()) ;
		    GUI.Label(new Rect(10, 100,120,20), "espece perdus : " + joueur.Perdus.ToString()) ;
			
			
		if (GUI.Button(new Rect(500,10,50,20),"*") )
		{
			Application.LoadLevel(0);
			
			joueur.Score2=0;
		joueur.Score=0;
		joueur.Lives=3;
		joueur.Level=1;
		joueur.Perdus=0;
		}
			}
		
		void OnTriggerEnter (Collider otherObject)
		
		{
			if (otherObject.tag == "bonus")
			{
			joueur.Score +=50 ;
				joueur.Score2+=50;
				bonus bonus= (bonus) otherObject.gameObject.GetComponent ("bonus");
			   
				bonus.SetPositionVitesse() ;
				
				if (joueur.Score2>=300)
					Application.LoadLevel(3);
				
				}
			//StartCoroutine(DestroyShip ()) ;
	//			StartCoroutine(DestroyShip ()) ;
			
			
			if (otherObject.tag == "enemy")
			{
			joueur.Lives-- ;
				enemy enemy = (enemy) otherObject.gameObject.GetComponent ("enemy");
			   
				enemy.SetPositionVitesse() ;
				
			StartCoroutine(DestroyShip ()) ;
				
						}
			
			}
			
			IEnumerator DestroyShip ()
			{
			
				Instantiate(prefabrication_explosion, transform.position, Quaternion.identity);
				gameObject.renderer.enabled =false ;
				transform.position = new Vector3(0f, transform.position.y, transform.position.z);
				yield  return new WaitForSeconds (1.5f) ;
				
				if (joueur.Lives >0)
					
				gameObject.renderer.enabled =true ;
				
				else 
					Application.LoadLevel(2);
			}	
		
}