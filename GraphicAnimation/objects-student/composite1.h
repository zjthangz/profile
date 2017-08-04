
//CLASS Elephant

#ifndef _composite1_H
#define _composite1_H

// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "face.h"
#include "object3d.h"
#include "tcube.h"
#include "texture.h"
#include "torus.h"
#include "cylinder.h"
#include "sphere.h"
#include "tsphere.h"
#include "extrusion.h"
#include "sweep.h"

// -----------------------------------------------------------------------------------------
// class declaration
// -----------------------------------------------------------------------------------------

class composite1 : public object3d
{
private:	
	sphere		*head,
				*eye_l,*eye_r,
				*leg_fl,*leg_fr,*leg_bl,*leg_br,
				*tail;
	tsphere		*foot_fl,*foot_fr,*foot_bl,*foot_br;
	extrusion	*nose_1,*nose_2,
				*ear_l,*ear_r;
	torus		*nose_3;
	sweep		*ivory_l,*ivory_r,
				*body;
	texture		*tfoot;

	sphere		*eyeball_l,*eyeball_r;
	extrusion	*star_l,*star_r;
	sphere		*flush_l,*flush_r;

	public:
						composite1();
						void hide();
						void show();
						void face(int f);
						void walk(float time);
						void sit(float time,float x,float y,float z);
						void standup(float time,float x,float y,float z);
						void turnhead(float time);

};


#endif // _composite1_H

