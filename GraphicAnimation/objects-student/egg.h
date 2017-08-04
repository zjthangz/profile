
#ifndef _egg_H
#define _egg_H



// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "face.h"
#include "object3d.h"
#include "tsphere.h"
#include "texture.h"

// -----------------------------------------------------------------------------------------
// class declaration
// -----------------------------------------------------------------------------------------

class egg : public object3d
{
private:	
	tsphere		*e;
	texture		*tcrack;

	public:
						egg();
						void hide();
						void show();
						void crack();
						void shake(float time);
};


#endif // _egg_H

