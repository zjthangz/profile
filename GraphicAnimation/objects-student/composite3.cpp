
//CLASS Chick

// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "composite3.h"
#include "utility.h"
// -----------------------------------------------------------------------------------------
// globals
// -----------------------------------------------------------------------------------------
extern vector<object3d*> gShapeVector;
// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------
composite3::composite3()
{
	// Initialise the object's state

	setName("composite3");

	body=new sweep("chick_body.txt",40);
	body->setParent(this);
	body->setColour(0.9,0.9,0);
	body->setScale(0.15);
	body->setRotation('z',-30);


	head=new sphere(30);
	head->setDeformation(0.3,0.3,0.3);
	head->attachToParentAt(body,0,1.5,0);
	head->setColour(0.9,0.9,0);
	head->setScale(4);
	head->setRotation('z',30);

	eye_l=new sphere(10);
	eye_l->setColour(0,0,0);
	eye_l->attachToParentAt(head,0.2,0.1,-0.2);
	eye_l->setScale(0.05);

	eye_r=new sphere(10);
	eye_r->setColour(0,0,0);
	eye_r->attachToParentAt(head,0.2,0.1,0.2);
	eye_r->setScale(0.05);

	beak_t=new extrusion("beak.txt","beak_path.txt");
	beak_t->setDeformation(0.1,0.12,0.15);
	beak_t->attachToParentAt(head,0.28,0,0);
	beak_t->setRotation('y',90);
	beak_t->setColour(1,0.5,0);

	beak_b=new extrusion("beak.txt","beak_path.txt");
	beak_b->setDeformation(0.08,0.08,0.12);
	beak_b->attachToParentAt(head,0.28,0,0);
	beak_b->setRotation('y',-90,'z',180);
	beak_b->setColour(1,0.5,0);

	leg_r=new cylinder(16);
	leg_r->setDeformation(0.13,0.5,0.13);
	leg_r->attachToParentAt(body,0.8,-1.5,0.5);
	leg_r->setColour(1,0.8,0);
	leg_r->setRotation('z',30);

	leg_l=new cylinder(16);
	leg_l->setDeformation(0.13,0.5,0.13);
	leg_l->attachToParentAt(body,0.8,-1.5,-0.5);
	leg_l->setColour(1,0.8,0);
	leg_l->setRotation('z',30);

	foot_r=new extrusion("chickentoe.txt","chickentoe_path.txt");
	foot_r->attachToParentAt(leg_r,0,-0.5,0);
	foot_r->setColour(1,0.8,0);
	foot_r->setRotation('x',-90,'y',-90);
	foot_r->setScale(1.8);

	foot_l=new extrusion("chickentoe.txt","chickentoe_path.txt");
	foot_l->attachToParentAt(leg_l,-0,-0.5,0);
	foot_l->setColour(1,0.8,0);
	foot_l->setRotation('x',-90,'y',-90);
	foot_l->setScale(1.8);
}

void composite3::hide()
{
	head->		hide();
	body->		hide();
	eye_l->		hide();
	eye_r->		hide();
	leg_l->		hide();
	leg_r->		hide();
	foot_l->	hide();
	foot_r->	hide();
	beak_t->	hide();
	beak_b->	hide();
}
void composite3::show()
{
	head->		show();
	body->		show();
	eye_l->		show();
	eye_r->		show();
	leg_l->		show();
	leg_r->		show();
	foot_l->	show();
	foot_r->	show();
	beak_t->	show();
	beak_b->	show();
}
void composite3::walk(float time)//cycle=1s
{
	float theAngle= sin_d(time * 360.0) * 20;
	leg_r->setRotation('z', theAngle+30);
	leg_l->setRotation('z',-theAngle+30);
}

void composite3::crow(float time)//cycle=2s time0=n*4
{
	float theAngle= sin_d(time * 90.0) * 25;
	beak_t->setRotation('y',90,'z',theAngle);
	beak_b->setRotation('y',-90,'z',180-theAngle);
}