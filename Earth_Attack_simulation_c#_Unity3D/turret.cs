using UnityEngine;
using System.Collections;

public class turret : MonoBehaviour {

	
	public float V_jeu ;
	public GameObject prefabrication_bombe;
	public GameObject prefabrication_explosion ;
	
	public Transform LookAtTarget;
	public AudioClip sound;
	
	
	
	void Update () 
	{
	    // initialisation de mouvement
		
		transform.LookAt(LookAtTarget);
		
		float mouvement =Input.GetAxisRaw("Horizontal") *V_jeu  * Time.deltaTime  ;
        
		
		
		
		if ( Erth.distance < 100)
		{		
		
			//creat Bomb (Instanciate prefab)
			
			
			Vector3 position= new Vector3 (transform.position.x,  transform.position.y + (collider.bounds.size.y/2));
	    	 Instantiate (prefabrication_bombe, position , Quaternion.identity) ;
			//il nous faux l'ajout de bouton initiale 
			}		
		}
		
	//on collision do
		
		void OnTriggerEnter (Collider otherObject)
		
		{
			
			//StartCoroutine(DestroyShip ()) ;
			//StartCoroutine(DestroyShip ()) ;
			
			
			if (otherObject.tag == "astroid")
			{
			
			
			
				astroid astroid = (astroid) otherObject.gameObject.GetComponent ("astroid");
			   
				astroid.SetPositionVitesse() ;
				
				StartCoroutine(DestroyShip ()) ;
				
						}
			
			}
			
			IEnumerator DestroyShip ()
			{
			
				Instantiate(prefabrication_explosion, transform.position, Quaternion.identity);
				gameObject.renderer.enabled =false ;
				transform.position = new Vector3(0f, transform.position.y, transform.position.z);
				yield  return new WaitForSeconds (1.5f) ;
				
				
			}	
		
}