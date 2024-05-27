using UnityEngine;
using System.Collections;

public class bombe : MonoBehaviour {
	public int stage =0;
	public float V_bombe ;
	public GameObject prefabrication_explosion ;
	
	void Update () 
	{
		float movement = V_bombe	* Time.deltaTime ; 
		
		transform.Translate(Vector3.up  * movement) ;
		
	if ( gameObject.transform.position.y  > 8.4f)
			   Destroy(gameObject);
			
	}
			
		void OnTriggerEnter (Collider otherObject)
		{
			if (otherObject.tag == "enemy")
			{
			
				enemy enemy = (enemy) otherObject.gameObject.GetComponent ("enemy");
			    Instantiate(prefabrication_explosion, enemy.transform.position, enemy.transform.rotation);
				enemy.SetPositionVitesse() ;
				
				Destroy(gameObject);
			// incrimentation du score
				joueur.Score += 10 ;
				joueur.Score2+=10;
				// passage de stage
				 if (joueur.Score2>=300) {
					 if (stage==0){
					Application.LoadLevel(3);
				    stage++;
					 }
					 else if (stage==1){
						 Application.LoadLevel(9);
					 }
				}
			
			}
		
}
}