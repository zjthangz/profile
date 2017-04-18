// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "egg.h"
#include "utility.h"
// -----------------------------------------------------------------------------------------
// globals
// -----------------------------------------------------------------------------------------
extern vector<object3d*> gShapeVector;
// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------
egg::egg()
{
	// Initialise the object's state

	setName("egg");

	tcrack=new texture("crack.jpg");

	e=new tsphere(16);
	e->setDeformation(0.28,0.4,0.28);
	e->setColour(1,0.98,0.8);
	e->setParent(this);
	e->setRotation('z',90);

}

void egg::hide()
{
	e->		hide();

}
void egg::show()
{
	e->		show();

}
void egg::crack()
{
	e->setTexture(tcrack);
}

void egg::shake(float time) //cycle=0.5s
{
	float theAngle= sin_d(time *720.0) * 15;
	e->setRotation('z',90+theAngle);
}