#include "UniqueID.h"

UniqueID::UniqueID()
{
    this->iID = newID();
    this->v4IndividualColor = generateIndividualColor(iID);
}

UniqueID::~UniqueID()
{
    
}

unsigned int UniqueID::getID() const       { return this->iID; }
color UniqueID::getIndividualColor() const { return this->v4IndividualColor; }

unsigned int UniqueID::newID()             { return LAST_RENDERABLE_ID++; }
unsigned int UniqueID::getLastID()         { return LAST_RENDERABLE_ID; }

color UniqueID::generateIndividualColor(const unsigned int& id)
{
    color ret;
	ret.r = (id & 0x000000FF) >>  0;
	ret.g = (id & 0x0000FF00) >>  8;
	ret.b = (id & 0x00FF0000) >> 16;
	ret.a = (id & 0xFF000000) >> 24;
    return ret;
}

unsigned int UniqueID::colorToID(color col)
{
    unsigned int id = 0;
    id += (int)col.r >>  0;
    id += (int)col.g >>  8;
    id += (int)col.b >> 16;
    id += (int)col.a >> 24;

    return id;
}