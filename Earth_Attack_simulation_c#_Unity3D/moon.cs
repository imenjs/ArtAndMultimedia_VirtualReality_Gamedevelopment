using UnityEngine;
using System.Collections;

public class moon : MonoBehaviour {

	public float speed;
	
	void Update () {
		
		 transform.Rotate(Vector3.down *  Time.deltaTime * speed);
	
	}
}
