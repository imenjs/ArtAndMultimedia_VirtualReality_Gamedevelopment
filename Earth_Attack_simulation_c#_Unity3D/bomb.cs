using UnityEngine ;
using System.Collections;

public class bomb : MonoBehaviour {
	
	public float V_bombe ;
	public GameObject prefabrication_explosion ;
	
	//public AudioClip exploseSound ; 
	
	void Update () 
	{
		float movement = V_bombe * Time.deltaTime ; 
		
		
		transform.Translate(Vector3.up * movement) ;
		
		
	if ( gameObject.transform.position.y  > 200f)
			   Destroy(gameObject);
			
	}
			
		void OnTriggerEnter (Collider otherObject)
		{
			if (otherObject.tag == "astroid")
			{
			
				astroid astroid = (astroid) otherObject.gameObject.GetComponent ("astroid");
			    Instantiate(prefabrication_explosion, astroid.transform.position, astroid.transform.rotation);
				astroid.SetPositionVitesse() ;
				
			//audio.PlayOneShot(exploseSound);
			
				Destroy(gameObject);
		
				}
			
			}
		
}
