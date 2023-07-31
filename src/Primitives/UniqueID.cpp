#include "UniqueID.h"

UniqueID::UniqueID()
{
    this->iID = newID();
    this->v4IndividualColor = generateIndividualColor(iID);
}

UniqueID::~UniqueID()
{
    
}

unsigned int UniqueID::getID() const      { return this->iID; }
vec4 UniqueID::getIndividualColor() const { return this->v4IndividualColor; }

unsigned int UniqueID::newID()            { return LAST_RENDERABLE_ID++; }
unsigned int UniqueID::getLastID()        { return LAST_RENDERABLE_ID; }

vec4 UniqueID::generateIndividualColor(const unsigned int& id)
{
    vec4 ret;
	ret.r = (id & 0x000000FF) >>  0;
	ret.g = (id & 0x0000FF00) >>  8;
	ret.b = (id & 0x00FF0000) >> 16;
	ret.a = (id & 0xFF000000) >> 24;
    ret = ret / 255.0f;
    return ret;
}