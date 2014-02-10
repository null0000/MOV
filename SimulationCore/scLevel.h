#ifndef SCLEVEL_H
#define SCLEVEL_H

#include <vector>
#include "scGame.h"

class scGame;
class gcRenderable;
class scSimulatable;


class scLevel
{
public:
    scLevel(scGame &Owner); /*Temporary constructor for the main level*/

private:
    scGame owner;
};

#endif // SCLEVEL_H
