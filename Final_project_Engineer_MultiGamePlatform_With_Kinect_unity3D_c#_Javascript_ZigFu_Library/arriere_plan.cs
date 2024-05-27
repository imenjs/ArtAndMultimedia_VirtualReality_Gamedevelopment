using UnityEngine;
using System.Collections;

public class arriere_plan : MonoBehaviour {

	public float Vitesse ;
	
	void Update() 
	{
		float C_vitesse = Vitesse* Time.deltaTime ;
		transform.Translate(Vector3.down * C_vitesse,Space.World);
			if (transform.position.y< -20)
				transform.position = new Vector3(transform.position.x, 20f , transform.position.z);
				
	}
}
