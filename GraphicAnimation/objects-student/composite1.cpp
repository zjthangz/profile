
//CLASS Elephant

// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "composite1.h"
#include "utility.h"
// -----------------------------------------------------------------------------------------
// globals
// -----------------------------------------------------------------------------------------
extern vector<object3d*> gShapeVector;

#define NORMAL	0 //black eyes
#define SHINE	1 //red face & star
#define EXCITED	2 //red face
// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------
composite1::composite1()
{
	// Initialise the object's state

	setName("composite1");

	body=new sweep("bodysweep.txt",40);
	body->setDeformation(0.4,0.6,0.5);
	body->setRotation('z',90);
	body->setParent(this);
	body->setColour(0.7,0.7,0.7);

	head=new sphere(20);
	head->setColour(0.7,0.7,0.7);
	head->attachToParentAt(body,1.2,-1.5,0);

	eye_l=new sphere(16);
	eye_l->setColour(1,1,1);
	eye_l->attachToParentAt(head,0.4,-0.5,-0.6);
	eye_l->setDeformation(0.2,0.3,0.3);
	eye_l->setRotation('y',45.0,'z',-45.0);

	eye_r=new sphere(16);
	eye_r->setColour(1,1,1);
	eye_r->attachToParentAt(head,0.4,-0.5,0.6);
	eye_r->setDeformation(0.2,0.3,0.3);
	eye_r->setRotation('y',-45.0,'z',-45.0);

	leg_fl=new sphere(16);
	leg_fl->setColour(0.7,0.7,0.7);
	leg_fl->attachToParentAt(body,-1,-1,-0.8);
	leg_fl->setDeformation(0.4,0.8,0.4);
	leg_fl->setRotation('z',90.0);

	leg_fr=new sphere(16);
	leg_fr->setColour(0.7,0.7,0.7);
	leg_fr->attachToParentAt(body,-1,-1,0.8);
	leg_fr->setDeformation(0.4,0.8,0.4);
	leg_fr->setRotation('z',90.0);

	leg_bl=new sphere(16);
	leg_bl->setColour(0.7,0.7,0.7);
	leg_bl->attachToParentAt(body,-1,1,-1);
	leg_bl->setDeformation(0.5,0.8,0.5);
	leg_bl->setRotation('z',90.0);

	leg_br=new sphere(16);
	leg_br->setColour(0.7,0.7,0.7);
	leg_br->attachToParentAt(body,-1,1,1);
	leg_br->setDeformation(0.5,0.8,0.5);
	leg_br->setRotation('z',90.0);


	tfoot=new texture("foot.jpg");

	foot_fl=new tsphere(20);
	foot_fl->setTexture(tfoot);
	foot_fl->attachToParentAt(leg_fl,0,0.8,0);
	foot_fl->setDeformation(0.35,0.2,0.3);
	
	foot_fr=new tsphere(20);
	foot_fr->setTexture(tfoot);
	foot_fr->attachToParentAt(leg_fr,0,0.8,0);
	foot_fr->setDeformation(0.35,0.2,0.3);
	
	foot_bl=new tsphere(10);
	foot_bl->setTexture(tfoot);
	foot_bl->attachToParentAt(leg_bl,0,0.8,0);
	foot_bl->setDeformation(0.4,0.2,0.35);
	
	foot_br=new tsphere(20);
	foot_br->setTexture(tfoot);
	foot_br->attachToParentAt(leg_br,0,0.8,0);
	foot_br->setDeformation(0.4,0.2,0.35);

	nose_1=new extrusion("circle.txt","nose1_path.txt");
	nose_1->attachToParentAt(head,0,-1.3,0);
	nose_1->setColour(0.7,0.7,0.7);
	nose_1->setRotation('x',-90);

	nose_2=new extrusion("circle.txt","nose2_path.txt");
	nose_2->attachToParentAt(nose_1,0,0,0.1);
	nose_2->setColour(0.7,0.7,0.7);
	nose_2->setRotation('y',180);

	nose_3=new torus(16,16,0.2,0.05);
	nose_3->setDeformation(1,1.2,1);
	nose_3->attachToParentAt(nose_2,1.2,0,1.2);
	nose_3->setColour(0.7,0.7,0.7);
	nose_3->setRotation('z',90);

	ivory_l=new sweep("ivory.txt",20);
	ivory_l->attachToParentAt(nose_1,-0.3,0.3,0.4);
	ivory_l->setColour(1,1,1);
	ivory_l->setRotation('x',-60,'y',15);

	ivory_r=new sweep("ivory.txt",20);
	ivory_r->attachToParentAt(nose_1,-0.3,-0.3,0.4);
	ivory_r->setColour(1,1,1);
	ivory_r->setRotation('x',-120,'y',15);

	ear_l=new extrusion("ear.txt","ear_path_l.txt");
	ear_l->setColour(0.7,0.7,0.7);
	ear_l->attachToParentAt(head,-0.2,0,-0.75);
	ear_l->setRotation('x',90,'y',90);
	ear_r=new extrusion("ear.txt","ear_path_r.txt");
	ear_r->setColour(0.7,0.7,0.7);
	ear_r->attachToParentAt(head,-0.2,0,0.75);
	ear_r->setRotation('x',-90,'y',-90);

	tail=new sphere(16);
	tail->setColour(0.6,0.6,0.6);
	tail->setDeformation(0.9,0.05,0.05);
	tail->attachToParentAt(body,-0.9,1.8,0);

	
	//face objects
	eyeball_l=new sphere(16);
	eyeball_l->setColour(0,0,0);
	eyeball_l->setScale(0.15);
	eyeball_l->attachToParentAt(eye_l,0.1,-0,0);
	eyeball_l->hide();

	eyeball_r=new sphere(16);
	eyeball_r->setColour(0,0,0);
	eyeball_r->setScale(0.15);
	eyeball_r->attachToParentAt(eye_r,0.1,0,0);
	eyeball_r->hide();

	star_l=new extrusion("star.txt","star_path.txt");
	star_l->setColour(1,1,0);
	star_l->attachToParentAt(eye_l,0.1,-0,0);
	star_l->setRotation('y',90);
	star_l->hide();

	star_r=new extrusion("star.txt","star_path.txt");
	star_r->setColour(1,1,0);
	star_r->attachToParentAt(eye_r,0.1,-0,0);
	star_r->setRotation('y',90);
	star_r->hide();

	flush_l=new sphere(16);
	flush_l->setColour(1,0.3,0.4);
	flush_l->setDeformation(0.1,0.05,0.3);
	flush_l->setRotation('x',-45);
	flush_l->attachToParentAt(head,0,-0.7,0.7);
	flush_l->hide();

	flush_r=new sphere(16);
	flush_r->setColour(1,0.3,0.4);
	flush_r->setDeformation(0.1,0.05,0.3);
	flush_r->setRotation('x',45);
	flush_r->attachToParentAt(head,0,-0.7,-0.7);
	flush_r->hide();
	face(NORMAL);
	// put the shape onto the shapeVector so it gets draw messages
	gShapeVector.push_back(this);
}

void composite1::hide()
{
	head->		hide();
	eye_l->		hide();
	eye_r->		hide();
	leg_fl->	hide();
	leg_fr->	hide();
	leg_bl->	hide();
	leg_br->	hide();
	tail->		hide();
	foot_fl->	hide();
	foot_fr->	hide();
	foot_bl->	hide();
	foot_br->	hide();
	nose_1->	hide();
	nose_2->	hide();
	ear_l->		hide();
	ear_r->		hide();
	nose_3->	hide();
	ivory_l->	hide();
	ivory_r->	hide();
	body->		hide();
	flush_l->	hide();
	flush_r->	hide();
	star_l->	hide();
	star_r->	hide();
	eyeball_l->	hide();
	eyeball_r->	hide();

}
void composite1::show()
{
	head->		show();
	eye_l->		show();
	eye_r->		show();
	leg_fl->	show();
	leg_fr->	show();
	leg_bl->	show();
	leg_br->	show();
	tail->		show();
	foot_fl->	show();
	foot_fr->	show();
	foot_bl->	show();
	foot_br->	show();
	nose_1->	show();
	nose_2->	show();
	ear_l->		show();
	ear_r->		show();
	nose_3->	show();
	ivory_l->	show();
	ivory_r->	show();
	body->		show();
	eyeball_l->	show();
	eyeball_r->	show();
}

void composite1::face(int numf){
	if(numf==NORMAL){
		flush_l->hide();
		flush_r->hide();
		star_l->hide();
		star_r->hide();
		eyeball_l->show();
		eyeball_r->show();
	}
	if(numf==SHINE){
		eyeball_l->hide();
		eyeball_r->hide();
		flush_l->show();
		flush_r->show();
		star_l->show();
		star_r->show();
	}
	if(numf==EXCITED){
		star_l->hide();
		star_r->hide();
		flush_l->show();
		flush_r->show();
		eyeball_l->show();
		eyeball_r->show();
	}
}

void composite1::walk(float time)//cycle=2s
{
	float theAngle_f = sin_d(time * 180.0) * 15;
	float theAngle_b = sin_d(time * 180.0-90) * 15;
	leg_fr->setRotation('z', 90.0+theAngle_f);
	leg_fr->setPosition(-1,-1-0.8*sin_d(theAngle_f),0.8);
	leg_fl->setRotation('z',90.0-theAngle_f);
	leg_fl->setPosition(-1,-1+0.8*sin_d(theAngle_f),-0.8);
	leg_br->setRotation('z', 90.0+theAngle_b);
	leg_br->setPosition(-1,1-0.8*sin_d(theAngle_b),1);
	leg_bl->setRotation('z',90.0-theAngle_b);
	leg_bl->setPosition(-1,1+0.8*sin_d(theAngle_b),-1);


}

void composite1::sit(float time,float x,float y,float z) //use for 1 sec time0=n*4+1
{
	leg_fr->setRotation('z',180);
	leg_fr->setPosition(-1,-1.4,0.8);
	leg_fl->setRotation('z',180);
	leg_fl->setPosition(-1,-1.4,-0.8);
	leg_br->setRotation('z',0);
	leg_br->setPosition(-1,1.4,1);
	leg_bl->setRotation('z',0);
	leg_bl->setPosition(-1,1.4,-1);
	float thePosition = sin_d(time * 90) * 0.4;
	this->setPosition(x,thePosition-0.4+y,z);
}

void composite1::standup(float time,float x,float y,float z) //use for 1 sec time0=n*4
{
	float theAngle = sin_d(time * 90) * 90;
	leg_fr->setRotation('z', 180-theAngle);
	leg_fr->setPosition(-1,-1.4+0.4*sin_d(theAngle),0.8);
	leg_fl->setRotation('z', 180-theAngle);
	leg_fl->setPosition(-1,-1.4+0.4*sin_d(theAngle),-0.8);
	leg_br->setRotation('z', theAngle);
	leg_br->setPosition(-1,1.4-0.4*sin_d(theAngle),1);
	leg_bl->setRotation('z', theAngle);
	leg_bl->setPosition(-1,1.4-0.4*sin_d(theAngle),-1);
	float thePosition = sin_d(time * 90) * 0.4;
	this->setPosition(x,thePosition-0.4+y,z);
}

void composite1::turnhead(float time)//use for 1 sec time0=4n:turn; time0=4n+1:turnback
{
	float theAngle = sin_d(time * 90.0) * 30;
	head->setRotation('x',theAngle);
}

