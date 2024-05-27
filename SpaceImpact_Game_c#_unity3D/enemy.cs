using UnityEngine;
using System.Collections;

public class enemy : MonoBehaviour {
	public float V_min ;
	public float V_max ;
	
	private float Min_v_rotation=60f;
	private float Max_v_rotation=120f;
	
	private float Min_scale= .8f;
	private float Max_scale= 2f;
	
	private float V_rotation ;
	private float R_x, R_y, R_z ;
	private	float vitesse ; 
	private float x, y,z ;
	
	void  Start () 
	{
	
	SetPositionVitesse();
		}
	
	void Update () 
	{
		
		float Rotation_vitesse = V_rotation * Time.deltaTime;
		
		transform.Rotate(new Vector3(-1, 0, 0) * Rotation_vitesse);
		
		
		float mouvement = vitesse * Time.deltaTime ;
		transform.Translate(Vector3.down * mouvement, Space.World);
		
		// regeneration de l'enemy dés qu'il quitte la scene du jeux 
		if (transform.position.y<= -8)
		{
			SetPositionVitesse();
			joueur.Perdus++ ;
			}
				
		}
		
	public void SetPositionVitesse()
	{
	// rotation de l'enemy avec une vitesse aleatoir à chaque fois
	V_rotation=Random.Range (Min_v_rotation, Max_v_rotation);
		// changement de taille de l'enemy ç chaque fois aleatoirement 
		R_x=Random.Range(Min_scale, Max_scale);
		R_y=Random.Range(Min_scale, Max_scale);
		R_z=Random.Range(Min_scale, Max_scale);
		
		//changement de vitesse de mouvement de l'enemy  vers le bas à  chaque fois aleatoirement
	vitesse = Random.RandomRange(V_max, V_min) ;		
	x= Random.RandomRange(-9f, 9f) ;
	y= 9.0f;
   	z= 0.0f;	
		//application de mouvement de l'enemy vers le bas
		transform.position = new Vector3(x,y,z); 
		// Application des bouveaux dimmention de l'enemy
transform.localScale = new Vector3 (R_x, R_y, R_z);
		
		}		
}
