using UnityEngine;
using System.Collections;

public class astroid: MonoBehaviour {
	public float V_min ;
	public float V_max ;
	
	private float Min_v_rotation=60f;
	private float Max_v_rotation=120f;
	
	private float Min_scale= .1f;
	private float Max_scale= 2f;
	
	public float V_rotation = 10 ;
	private float R_x, R_y, R_z ;
	private	float vitesse ; 
	private float x, y,z ;
	
	
	
	void  Start () 
	{
	
	SetPositionVitesse();
		}
	
	void Update () 
	{
		
		if (Input.GetKey(KeyCode.Mouse0)){
		float Rotation_vitesse = V_rotation * Time.deltaTime;
		
					transform.Rotate(Vector3.forward * Time.deltaTime * Rotation_vitesse);
		
		float mouvement = vitesse * Time.deltaTime ;
		transform.Translate(Vector3.down * mouvement, Space.World);
		
		// regeneration de l'enemy dés qu'il quitte la scene du jeux 
		if (transform.position.y<= -60)
		{
			SetPositionVitesse();
			
				;
			}
				
		}}
		
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
	x= Random.RandomRange(-100f, 100f);
	y= 100;
   	z= 0;	
		//application de mouvement de l'enemy vers le bas
		transform.position = new Vector3(x,y,z); 
		// Application des nouveaux dimmention de l'enemy (change scale astroid)
	transform.localScale = new Vector3 (R_x, R_y, R_z);
		
		}		
}
