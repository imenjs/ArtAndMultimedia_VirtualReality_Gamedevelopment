using UnityEngine;
using System.Collections;

public class bonus : MonoBehaviour {
//public GameObject prefabrication_explosion ;
	public float V_bonus ;
	private float x, y,z ;
  public int TBonus=0;
	
	void Update () 
	{
	
		float movement = V_bonus	* Time.deltaTime ; 
		transform.Translate(Vector3.down  * movement) ;
		
	if (transform.position.y<= -8)
		{
	
				TBonus++;
			StartCoroutine(DestroyShip ()) ;
			
			}
				
	}
			IEnumerator DestroyShip ()
			{
			x= Random.RandomRange(-9f, 9f) ;
				y= 9.0f;
			z= 0.0f;	
			// Instantiate(prefabrication_explosion, transform.position, Quaternion.identity);
				gameObject.renderer.enabled =false ;
				transform.position = new Vector3(x,y,z); 
				//transform.position = new Vector3( transform.position.x,0f, transform.position.z);
				yield  return new WaitForSeconds (6f) ;
				gameObject.renderer.enabled =true ;
	}

public void SetPositionVitesse()
	{
	
	//vitesse = Random.RandomRange(V_max, V_min) ;		
	x= Random.RandomRange(-9f, 9f) ;
	y= 9.0f;
   	z= 0.0f;	
		transform.position = new Vector3(x,y,z); 	
		}		
}

