using UnityEngine;
using System.Collections;

public class help : MonoBehaviour {
private string  text = "Pour chaque Game placez vous bien devant la camera \n\n une espace de 2m au moin est favorable \n \n enlevez le maximum d'obstacle entre vous et la kinect\n \n vous pouvez choisir de jouer contre aurdinateur ou contre vos amis \n \n \t\t ENJOYT IT ";
public Texture image;
	//afficher le text du help
	void OnGUI() {
		
	GUI.DrawTexture(new Rect(0,0, Screen.width, Screen.height), image);
		GUI.Label(new Rect(100,100,350,300), text);
		
	if (GUI.Button(new Rect(500,50,60,30),"Quitter"))
		//appel a la scene (0) (menu principale)
		{
			Application.LoadLevel(0);
			}
		}
		
	
}
