// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// Assignment 1 & 2
// 3D Engine Code
// *****************************************************************************************
//
// Author: Tony Gray
//
// scene.cpp



// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "constants.h"			// system-wide constants
#include "utility.h"			// general utility functions
#include "light.h"
#include "camera.h"
#include "texture.h"
#include "scene.h"
#include "snd.h"
#include "skybox.h"
#include "fog.h"
#include "viewfrustum.h"


// #includes for geometry
#include "sweep.h"
#include "extrusion.h"
#include "cube.h"
#include "sphere.h"
#include "torus.h"
#include "terrain.h"
#include "billboard.h"
#include "plane.h"
#include "triangle.h"
#include "tsphere.h"
#include "cylinder.h"
#include "disc.h"
#include "house.h"
#include "composite1.h"
#include "composite2.h"
#include "composite3.h"
#include "egg.h"
#include "sign.h"

#define NORMAL	0 //black eyes
#define SHINE	1 //red face & star
#define EXCITED	2 //red face
#define STARE	1 //angry eyes
#define LOVE	2 //heart eyes
#define QUESTION	0 
#define SWEAT		1 
#define ANGER		2 
#define DOTS		3 
// -----------------------------------------------------------------------------------------
// global variables
// -----------------------------------------------------------------------------------------
extern ProgramMode		gProgramMode;							// initially, we're not animating

extern cameraClass		gCamera;								// the camera
extern object3d			*gSky;									// the global skybox
extern fog				*gFog;									// the global fog
extern viewfrustum		*gViewFrustum;							// the global view frustum object
extern float			gCurrentFrameTime;						// the time that the current animation frame was started

extern vector<object3d*> gShapeVector;
typedef vector<object3d*>::iterator shapeVectorIterator;






// -----------------------------------------------------------------------------------------
// variables that represent 3D objects being used in the animation
// -----------------------------------------------------------------------------------------
// these are really global variables, but you shouldn't need to access them from anywere
// except in this file 
// -----------------------------------------------------------------------------------------

// shapes
house *cottage;
terrain *ground;
composite1 *littleelephant;
composite2 *motherhen;
composite3 *newbornchick;
egg *egg1,*egg2,*egg2crack;
sign *s;
disc *haystack1,*haystack2,*brokeegg;
texture *thaystack,*tbrokeegg,*tbackground,*ttree;
snd *sbg,*swalk,*scrack,*schick,*shen,*scheer;
plane *bgback;
billboard *tree[4];

// some lights
light *ambient, *light0, *light1, *light2;



// -----------------------------------------------------------------------------------------
// constructScene
// -----------------------------------------------------------------------------------------
// This function constructs the objects required for the animation.  It is only called once
// wcomposite2 the program is first run.
// Use this to create child objects and bind them to their parents.
// -----------------------------------------------------------------------------------------

void constructScene()
{
	// create the lights first
	ambient = new light(GL_LIGHT_MODEL_AMBIENT);
	light0 = new light(GL_LIGHT0);
	light1 = new light(GL_LIGHT1);
    
	tbackground =new texture("background.png");
	bgback=new plane();
	bgback->setTexture(tbackground);
	bgback->setPosition(-100,10,-150);
	bgback->setDeformation(614,20,1);

	ttree=new texture("tree.png");
	tree[0]=new billboard(ttree,beginCylindricalBillboard);
	tree[0]->setPosition(-30,2,-40);
	tree[0]->setDeformation(3,5,1);
	tree[1]=new billboard(ttree,beginCylindricalBillboard);
	tree[1]->setPosition(-5,2,-10);
	tree[1]->setDeformation(3,5,1);
	tree[2]=new billboard(ttree,beginCylindricalBillboard);
	tree[2]->setPosition(15,2,-30);
	tree[2]->setDeformation(3,5,1);
	tree[3]=new billboard(ttree,beginCylindricalBillboard);
	tree[3]->setPosition(50,2,0);
	tree[3]->setDeformation(3,5,1);

	s=new sign();
	cottage=new house();
	cottage->setPosition(0,0,-20);

	littleelephant=new composite1();
	littleelephant->setPosition(-40,-0.5,0);

	motherhen=new composite2();
	motherhen->setPosition(17,-1.7,11);
	motherhen->setRotation('y',-180);

	newbornchick=new composite3();
	newbornchick->setPosition(5,-2.15,10);
	newbornchick->setRotation('y',-90);
	newbornchick->hide();

	egg1=new egg();
	egg1->setPosition(0,-2.2,10);
	egg2=new egg();
	egg2->setPosition(5,-2.2,10);
	egg2crack=new egg();
	egg2crack->setPosition(5,-2.2,10);
	egg2crack->hide();

	ground = new terrain("ground.bmp");
	ground->setPosition(0, -4, 0);
	ground->setDeformation(12.0, 1.5, 4.0);
	ground->setColour(0.4, 0.8, 0.2);
	ground->setShininess(1);

	gSky = new skybox("sky14-");
	vectr fogColour;
	fogColour.set(0.05, 0.45, 0.1);
	gFog = new fog(80.0,95.0, fogColour);

	thaystack=new texture("haystack.jpg");
	haystack1=new disc(16,1);
	haystack1->setPosition(0,-2.5,10);
	haystack1->setTexture(thaystack);

	haystack2=new disc(16,1);
	haystack2->setPosition(5,-2.5,10);
	haystack2->setTexture(thaystack);

	tbrokeegg=new texture("brokeegg.png");
	brokeegg=new disc(16,1);
	brokeegg->setTexture(tbrokeegg);
	brokeegg->setPosition(0,-2.4,10);
	brokeegg->setScale(0.5);
	brokeegg->hide();

	sbg=new snd("bg.ogg");
	swalk=new snd("walk.wav");
	scrack=new snd("crack.wav");
	schick=new snd("chick.wav");
	shen=new snd("hen.ogg");
	scheer=new snd("cheer.ogg");
}




// -----------------------------------------------------------------------------------------
// resetScene
// -----------------------------------------------------------------------------------------
// This function is called wcomposite2ever the animation is restarted.  Use it to reset objects
// to their starting position or size, or to reset any aspects of the objects that
// might have been altered during an animation sequence.
// -----------------------------------------------------------------------------------------

void resetScene()
{
	// initialise the camera
	gCamera.setPosition(-30, 2, 10);
	gCamera.setTarget(littleelephant);

    
	ambient->setColour(0.5, 0.5, 0.5, 1.0);
    
	light0->turnOn();
	light0->setPosition(-10, 10, 5);
	light0->setColour(0.7, 0.7, 0.7, 1.0);
	light0->setSpecularColour(0.7, 0.7, 0.7, 1.0);
	light0->makePositional();
	light0->setLinearAttenuation(0.1);
	
	light1->turnOn();
	light1->setPosition(10, 10, -5);
	light1->setColour(0.7, 0.7, 0.7, 1.0);
	light1->setSpecularColour(0.7, 0.7, 0.7, 1.0);
	light1->makePositional();
	light1->setLinearAttenuation(0.1);
    
	// reset all objects to their starting position
	
	littleelephant->setPosition(-40,-0.5,0);
	littleelephant->face(NORMAL);
	littleelephant->turnhead(0);

	motherhen->setPosition(17,-1.7,11);
	motherhen->setRotation('y',-180);
	motherhen->show();
	motherhen->face(NORMAL);
	
	newbornchick->setPosition(5,-2.15,10);
	newbornchick->setRotation('y',-90);
	newbornchick->hide();

	egg1->show();
	egg2->show();
	brokeegg->hide();
	
	s->hide();
}




// -----------------------------------------------------------------------------------------
// animateForNextFrame
// -----------------------------------------------------------------------------------------
// This function is called to animate objects ready for the next frame
// -----------------------------------------------------------------------------------------

void animateForNextFrame(float time, long frame)
{
	if(!sbg->isPlaying()) {
		sbg->startSound();
		sbg->setVolume(0.2);
	}
	if(time<=8){
		littleelephant->walk(time);
		motherhen->walk(time);
		static float x1=0;
		x1 = smoothAcceleration(0, 1.5, 5, +17, +7);
		motherhen->setPosition(x1,-1.7,11);
	}
	if (time>=8) motherhen->setRotation('y',-90); 

	if(time<=6){
		float p1 = -40;
		float p2 = -10;
		float duration = 6.0;
		float position = (((p2 - p1) / duration) * time) + p1;
		littleelephant->setPosition(position, -0.5, 0);
	}
		if(time>=6&&time<=8){
		float p1 = -10;
		float p2 = -5;
		float position = sin_d((time-6) *45.0) * (p2 - p1);
		littleelephant->setPosition(-10+position,-0.5, 0);
	}

	if(!swalk->isPlaying()&&time<=8) swalk->startSound();
	if(time>=8) swalk->stopSound();
	if(time<=3){
		float p1 = -30;
		float p2 = -5;
		float duration = 3.0;
		float position = (((p2 - p1) / duration) * time) + p1;
		float p3 = 10;
		float p4 = 25;
		float durationz = 3.0;
		float positionz = (((p4 - p3) / duration) * time) + p3;
		gCamera.setPosition(position, 2, positionz);
		gCamera.setTarget(littleelephant);
	}
	if(time>=3&&time<=6){			
		float p1 = -25;
		float p2 = 0;//target
		float p3 = -5;
		float p4 = 5;//position
		float duration = 3.0;
		float positiont = (((p2 - p1) / duration) * (time-3)) + p1;
		float position = (((p4 - p3) / duration) * (time-3)) + p3;
		gCamera.setPosition(position, 2, 25);
		gCamera.setTarget(positiont,0,0);
	}

		if(time>=6&&time<=7) littleelephant->turnhead(time);
		if(time>=8&&time<=9) motherhen->sitstand(time,5,-1.7,9);
		if(time>=9.5) s->showsign(DOTS,5,-0.6,11);
		if(time>=11.5) s->hidesign(DOTS);
		if(time>=13&&time<=14) motherhen->sitstand(time,5,-1.7,9);
		if(time>=14) motherhen->setRotation('y',0);


		if(time>=14&&time<=17){
			static float x2=0,z1=0;
			x2 = smoothAcceleration(14, 1, 1, +3, +1);
			z1 = smoothAcceleration(14, 1, 1, +11, +10);
			motherhen->setPosition(x2,-1.7,z1);
			motherhen->walk(time);
			float p1 = 0;
			float p2 = -5;//target
			float p3=5;
			float p4=10;
			float duration = 3.0;
			float positiont = (((p2 - p1) / duration) * (time-14)) + p1;
			gCamera.setTarget(positiont ,0,0);
			float position = (((p4 - p3) / duration) * (time-14)) + p3;
			gCamera.setPosition(position, 2, 25);
		}


		if(time>=17&&time<=18) egg2->shake(time);
		if(time>=18) egg2->hide();
		if(time>=18) {
			egg2crack->show();
			egg2crack->crack();
		}
		if(time>=18&&time<=19) egg2crack->shake(time);


		if(!scrack->isPlaying()&&time>=18&&time<=20) scrack->startSound();
		if(time>=20) scrack->stopSound();

		if(time>=18) littleelephant->face(EXCITED);
		if(time>=20) newbornchick->show();
		if(time>=21&&time<=23) newbornchick->crow(time-1);
		if(time>=24&&time<=26) newbornchick->crow(time);
		if(time>=26&&time<=28) newbornchick->crow(time-2);
		if(time>=21)	egg2crack->hide();
		if(!scheer->isPlaying()&&time>=20&&time<=22){
			scheer->startSound();
			scheer->setVolume(0.5);
		}
		if(time>=22) scheer->stopSound();
		if(!schick->isPlaying()&&time>=21&&time<=23) schick->startSound();
		if(time>=23) schick->stopSound();
		if(!schick->isPlaying()&&time>=24&&time<=28) schick->startSound();
		if(time>=28) schick->stopSound();

		if(time>=21&&time<=26)	littleelephant->face(SHINE);
		if(time>=21&&time<=23) motherhen->face(LOVE);
		if(time>=23&&time<=25){
			motherhen->face(NORMAL);
			float p1 = 1;
			float p2 = 3;
			float p3 = 10;
			float p4 = 8;
			float position_x= (1-cos_d((time-23) *45.0)) * (p2 - p1);
			float position_z= (1-cos_d((time-23) *45.0)) * (p4 - p3);
			motherhen->setPosition(p1+position_x, -1.7, p3+position_z);
			motherhen->walk(time);
		}
		if(time>=25&&time<=30){
			float v=2;
			float position_h = (v * (time-25) + 3);
			motherhen->setPosition(position_h, -1.7, 8);
			motherhen->walk(time);
		}
		if(time>=25&&time<=27){
			newbornchick->setRotation('y',0);
			float p1 = 5;
			float p2 = 7;
			float p3 = 10;
			float p4 = 8;
			float position_x= (1-cos_d((time-25) *45.0)) * (p2 - p1);
			float position_z= (1-cos_d((time-25) *45.0)) * (p4 - p3);
			newbornchick->setPosition(p1+position_x, -2.15, p3+position_z);
			newbornchick->walk(time);
		}
		if(time>=27&&time<=30){
			float v=2;
			float position_c = (v * (time-27) + 7);
			newbornchick->setPosition(position_c, -2.15, 8);
			newbornchick->walk(time);
		}
		if(time>=27) littleelephant->face(EXCITED);
		if(time>=30) {
			newbornchick->hide();
			motherhen->hide();
		}


		if(time>=30&&time<=33){
			float p1 = -5;
			float p2 = 0;//target
			float p3=10;
			float p4=0;//position
			float duration = 3.0;
			float positiont = (((p2 - p1) / duration) * (time-30)) + p1;
			gCamera.setTarget(positiont ,0,0);
			float position = (((p4 - p3) / duration) * (time-30)) + p3;
			gCamera.setPosition(position, 2, 25);
		}

		if(!swalk->isPlaying()&&time>=31&&time<=34) swalk->startSound();
		if(time>=34) swalk->stopSound();

		if(time>=31&&time<=34){
			static float x3=0, z2=0;
			x3 = smoothAcceleration(31, 1, 1,-5,0);
			z2 = smoothAcceleration(31, 1, 1,0,10);		
			littleelephant->setPosition(x3, -0.5, z2);
			littleelephant->walk(time-1);
		}
		if(time>=34&&time<=36){
			littleelephant->sit(time-1,0,-0.5,10);
		}

		if(!scrack->isPlaying()&&time>=35.5&&time<=36.5) scrack->startSound();
		if(time>=36.5) scrack->stopSound();

		if(time>=33&&time<=34){
			littleelephant->turnhead(time-2);
		}
		if(time>=36) egg1->hide();
		if(time>=37) littleelephant->face(NORMAL);
		if(time>=37.5&&time<=38) s->showsign(QUESTION, 1.5,1.5,10);
		if(time>=38.5) {
			s->hidesign(QUESTION);
			brokeegg->show();
		}

		if(time>=39&&time<=40) littleelephant->standup(time+1,0,-0.5,10);
		
		if(time>=40&&time<=42){
			static float x4=0;
			x4 = smoothAcceleration(40, 0.5, 1,0,-3);		
			littleelephant->setPosition(x4, -0.5, 10);
			littleelephant->walk(time);
		}

		if(!swalk->isPlaying()&&time>=40&&time<=42) swalk->startSound();
		if(time>=42) swalk->stopSound();

		if(time>=43&&time<=45){
			s->fallsweat(time-43,2,-1.2,1,0.5,11.5);
		}
		if(time>=45){
			motherhen->show();
			motherhen->setPosition(16,-1.7,5);
			motherhen->setRotation('y',-135);
			motherhen->face(STARE);
			s->showsign(ANGER,14.5,-1.5,7.5);
		}
		if(time>=45&&time<=47){
			float p1 = 0;
			float p2 = 5;
			float duration = 2.0;
			float position = (((p2 - p1) / duration) * (time-45)) + p1;
			gCamera.setPosition(position, 2, 25);
			gCamera.setTarget(position,0,0);
		}
		if(!shen->isPlaying()&&time>=46&&time<=47) shen->startSound();
		if(time>=47) shen->stopSound();
		
	if (time >= 48)
		gProgramMode = kpmFinished;


}


