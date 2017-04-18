
//CLASS Hen

#ifndef _composite2_H
#define _composite2_H



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

class composite2 : public object3d
{
private:	
	sphere		*body,
				*comb[3],
				*eye_l,*eye_r;
	tsphere		*wing_l,*wing_r;

	extrusion	*foot_l,*foot_r,
				*tail,
				*beak_t,*beak_b;
	texture		*twing;
	cylinder	*leg_l,*leg_r;

	sphere		*eyeball_l,*eyeball_r;
	extrusion	*stare_l,*stare_r,
				*heart_l,*heart_r;
	sweep		*chin;
	public:
						composite2();
						void hide();
						void show();
						void walk(float time);
						void sitstand(float time,float x,float y,float z);
						void face(int f);
};


#endif // _composite2_H

