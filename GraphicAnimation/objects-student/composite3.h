
//CLASS Chick

#ifndef _composite3_H
#define _composite3_H



// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "face.h"
#include "object3d.h"
#include "sphere.h"
#include "extrusion.h"
#include "cylinder.h"
#include "sweep.h"
// -----------------------------------------------------------------------------------------
// class declaration
// -----------------------------------------------------------------------------------------

class composite3 : public object3d
{
private:	
	sphere		*head,
				*eye_l,
				*eye_r;

	extrusion	*foot_l,
				*foot_r,
				*beak_t,
				*beak_b;
	cylinder	*leg_l,
				*leg_r;
	sweep		*body;

	public:
						composite3();
						void hide();
						void show();
						void walk(float time);
						void crow(float time);
};


#endif // _composite3_H

