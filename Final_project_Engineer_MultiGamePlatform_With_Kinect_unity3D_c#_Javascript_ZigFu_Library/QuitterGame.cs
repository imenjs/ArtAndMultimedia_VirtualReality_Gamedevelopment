using UnityEngine;
using System.Collections;

public class QuitterGame : MonoBehaviour {

	void OnGUI() {
		
	
		
	if (GUI.Button(new Rect(1100,10,60,30),"Quitter"))
		//appel a la scene (0) (menu principale)
		{
			Application.LoadLevel(0);
			}
		}
		
	
}
