
//CLASS Hen

// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "composite2.h"
#include "utility.h"
// -----------------------------------------------------------------------------------------
// globals
// -----------------------------------------------------------------------------------------
extern vector<object3d*> gShapeVector;

#define NORMAL	0 //black eyes
#define STARE	1 //angry eyes
#define LOVE	2//heart eyes
// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------
composite2::composite2()
{
	// Initialise the object's state

	setName("composite2");
	body=new sphere(30);
	body->setParent(this);
	body->setColour(1,1,0.7);
	body->setPosition(2,0,0);
	body->setDeformation(0.6,0.6,0.5);

	comb[0]=new sphere(16);
	comb[0]->setDeformation(0.1,0.1,0.05);
	comb[0]->setColour(1,0,0);
	comb[0]->attachToParentAt(body,0.2,0.6,0);
	comb[1]=new sphere(16);
	comb[1]->setDeformation(0.1,0.1,0.05);
	comb[1]->attachToParentAt(body,0.3,0.6,0);
	comb[1]->setColour(1,0,0);
	comb[2]=new sphere(16);
	comb[2]->setDeformation(0.1,0.1,0.05);
	comb[2]->attachToParentAt(body,0.4,0.5,0);
	comb[2]->setColour(1,0,0);

	eye_l=new sphere(16);
	eye_l->setColour(1,1,1);
	eye_l->attachToParentAt(body,0.5,0.2,-0.1);
	eye_l->setScale(0.1);
	eye_r=new sphere(16);
	eye_r->setColour(1,1,1);
	eye_r->attachToParentAt(body,0.5,0.2,0.1);
	eye_r->setScale(0.1);

	twing=new texture("wing.jpg");
	wing_l=new tsphere(16);
	wing_l->setTexture(twing);
	wing_l->setDeformation(0.3,0.2,0.1);
	wing_l->attachToParentAt(body,0,0,-0.5);
	wing_r=new tsphere(16);
	wing_r->setTexture(twing);
	wing_r->setDeformation(0.3,0.2,0.1);
	wing_r->attachToParentAt(body,0,0,0.5);

	leg_r=new cylinder(16);
	leg_r->setDeformation(0.05,0.15,0.05);
	leg_r->attachToParentAt(body,0,-0.6,0.2);
	leg_r->setColour(1,0.8,0);

	leg_l=new cylinder(16);
	leg_l->setDeformation(0.05,0.15,0.05);
	leg_l->attachToParentAt(body,0,-0.6,-0.2);
	leg_l->setColour(1,0.8,0);

	foot_r=new extrusion("chickentoe.txt","chickentoe_path.txt");
	foot_r->attachToParentAt(leg_r,0,-0.2,0);
	foot_r->setColour(1,0.8,0);
	foot_r->setRotation('x',-90,'y',-90);
	foot_r->setScale(0.7);

	foot_l=new extrusion("chickentoe.txt","chickentoe_path.txt");
	foot_l->attachToParentAt(leg_l,0,-0.2,0);
	foot_l->setColour(1,0.8,0);
	foot_l->setRotation('x',-90,'y',-90);
	foot_l->setScale(0.7);

	tail=new extrusion("tail.txt","tail_path.txt");
	tail->setColour(1,1,0.7);
	tail->attachToParentAt(body,-0.55,0,0);
	tail->setRotation('x',60,'y',-90);
	tail->setScale(1.5);

	beak_t=new extrusion("beak.txt","beak_path.txt");
	beak_t->setDeformation(0.1,0.12,0.15);
	beak_t->attachToParentAt(body,0.6,0,0);
	beak_t->setRotation('y',90);
	beak_t->setColour(1,1,0);

	beak_b=new extrusion("beak.txt","beak_path.txt");
	beak_b->setDeformation(0.08,0.08,0.12);
	beak_b->attachToParentAt(body,0.58,0,0);
	beak_b->setRotation('y',-90,'z',180);
	beak_b->setColour(1,1,0);

	chin=new sweep("chin.txt",16);
	chin->attachToParentAt(beak_b,0,0.2,0);
	chin->setColour(1,0,0);
	chin->setRotation('x',180);
	chin->setScale(0.8);

	//face objects
	eyeball_l=new sphere(16);
	eyeball_l->setColour(0,0,0);
	eyeball_l->setScale(0.5);
	eyeball_l->attachToParentAt(eye_l,0.7,0.3,-0.2);
	eyeball_l->hide();

	eyeball_r=new sphere(16);
	eyeball_r->setColour(0,0,0);
	eyeball_r->setScale(0.5);
	eyeball_r->attachToParentAt(eye_r,0.7,0.3,0.2);
	eyeball_r->hide();

	stare_l=new extrusion("stare.txt","stare_path.txt");
	stare_l->setColour(1,0,0);
	stare_l->setScale(0.6);
	stare_l->attachToParentAt(eye_l,0.9,-0.2,-0.2);
	stare_l->setRotation('y',90);
	stare_l->hide();
	stare_r=new extrusion("stare.txt","stare_path.txt");
	stare_r->setColour(1,0,0);
	stare_r->setScale(0.6);
	stare_r->attachToParentAt(eye_r,1,-0.2,0.2);
	stare_r->setRotation('y',-90);
	stare_r->hide();

	heart_l=new extrusion("heart.txt","stare_path.txt");
	heart_l->setColour(1,0.08,0.57);
	heart_l->setScale(0.8);
	heart_l->attachToParentAt(eye_l,0.85,0.5,-0.2);
	heart_l->setRotation('y',90);
	heart_l->hide();

	heart_r=new extrusion("heart.txt","stare_path.txt");
	heart_r->setColour(1,0.08,0.57);
	heart_r->setScale(0.8);
	heart_r->attachToParentAt(eye_r,1,0.5,0.2);
	heart_r->setRotation('y',-90);
	heart_r->hide();
	face(NORMAL);
}

void composite2::hide()
{
	body->		hide();
	comb[0]->	hide();
	comb[1]->	hide();
	comb[2]->	hide();
	eye_l->		hide();
	eye_r->		hide();
	wing_l->	hide();
	wing_r->	hide();
	foot_l->	hide();
	foot_r->	hide();
	tail->		hide();
	beak_t->	hide();
	beak_b->	hide();
	leg_l->		hide();
	leg_r->		hide();	
	eyeball_l->	hide();
	eyeball_r->	hide();
	stare_l->	hide();
	stare_r->	hide();
	heart_l->	hide();
	heart_r->	hide();
	chin->		hide();
}
void composite2::show()
{
	body->		show();
	comb[0]->	show();
	comb[1]->	show();
	comb[2]->	show();
	eye_l->		show();
	eye_r->		show();
	wing_l->	show();
	wing_r->	show();
	foot_l->	show();
	foot_r->	show();
	tail->		show();
	beak_t->	show();
	beak_b->	show();
	leg_l->		show();
	leg_r->		show();	
	eyeball_l->	show();
	eyeball_r->	show();
	chin->		show();
}
void composite2::walk(float time)//cycle=1s
{
	float theAngle= sin_d(time * 360.0) * 20;
	leg_r->setRotation('z', theAngle);
	leg_r->setPosition(0.3*sin_d(theAngle),-0.6,0.2);
	leg_l->setRotation('z',-theAngle);
	leg_l->setPosition(-0.3*sin_d(theAngle),-0.6,-0.2);
}

void composite2::sitstand(float time,float x,float y,float z) //cycle=1s
{
	//for sit   : time0=n*2
	//for stand : time0=n*2+1 only used after sit
	float thePosition = cos_d(time * 180) * 0.15;
	this->setPosition(x,thePosition-0.15+y,z);
	leg_l->setPosition(0,-thePosition-0.45,0.2);
	leg_r->setPosition(0,-thePosition-0.45,-0.2);
}

void composite2::face(int numf)
{
	if(numf==NORMAL){
		stare_l->hide();
		stare_r->hide();
		heart_l->	hide();
		heart_r->	hide();
		eyeball_l->show();
		eyeball_r->show();
	}
	if(numf==STARE){
		eyeball_l->hide();
		eyeball_r->hide();
		heart_l->	hide();
		heart_r->	hide();
		stare_l->show();
		stare_r->show();
	}
	if(numf==LOVE){
		eyeball_l->hide();
		eyeball_r->hide();
		stare_l->hide();
		stare_r->hide();
		heart_l->	show();
		heart_r->	show();
	}
}