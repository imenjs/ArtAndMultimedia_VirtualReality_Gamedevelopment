using UnityEngine;
using System.Collections;

public class help : MonoBehaviour {
private string  text = "faite deplacer le joueur on utilisant les flèche :gauche et droite du clavier\n tirrer sur les enemys on appuyant sur espace. \n le score s'incrimente par 10 lorsque tu tue l'enemy et par 50 en mangeant les gems.\n a chaque fois que vous arrivez a un score de 500 vous passer a la Level suivant.\n \t\t merci d'utiliser cet Application ";
public Texture image;
	//afficher le text du help
	void OnGUI() {
		
	GUI.DrawTexture(new Rect(0,0, Screen.width, Screen.height), image);
		GUI.Label(new Rect(100,150,350,300), text);
		
	if (GUI.Button(new Rect(500,50,60,30),"Quitter"))
		//appel a la scene (0) (menu principale)
		{
			Application.LoadLevel(0);
			}
		}
		
	
}
