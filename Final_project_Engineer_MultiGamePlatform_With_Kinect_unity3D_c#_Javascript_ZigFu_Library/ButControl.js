var But1: Texture2D;
var But2: Texture2D;
var But3: Texture2D;
var But4: Texture2D;
var But5: Texture2D;
var But6: Texture2D;
var But7: Texture2D;
var But8: Texture2D;
var But9: Texture2D;
var But10: Texture2D;

private var but=false;

var NbBut=10;
var NbButInCage=0;
var NbButOutCage =0;

function OnControllerColliderHit(hit:ControllerColliderHit)

{

	if (hit.gameObject.tag=="TestBut")
	
	{
	but=true;
	NbBut-=1;
	
	}

}

function OnGUI ()
{

	GUI.Label(new Rect(10, 10,200,200), "Score : " + NbBut.ToString()) ;

}

function Update () {
	
	

switch(NbBut)

	{
	case 10: 
	guiTexture.texture= But10;
	

	
	case 9: 
	guiTexture.texture= But9;
	

	case 8: 
	guiTexture.texture= But8;
	

	case 7: 
	guiTexture.texture= But7;
	
	
	case 6: 
	guiTexture.texture= But6;
	
	
	case 5: 
	guiTexture.texture= But5;
	
	
	case 4: 
	guiTexture.texture= But4;
	
	
	case 3: 
	guiTexture.texture= But3;
	
	
	case 2: 
	guiTexture.texture= But2;
	
	
	case 1: 
	guiTexture.texture= But1;
	
	
	case 0:
	if (NbBut<5)
	{
	 //affich happiness or sadness
	
	}	
	break;


} }
function LateUpdate()
{
	if(but)
		{
		
			transform.position=Vector3(0,4,0);
			gameObject.Find("Main camera").transform.position=Vector3(0,4,-10);
			but=false;
		
		}
}