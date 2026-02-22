#pragma once
#include <Maths/color.h>

class UniqueID
{
private:
    inline static unsigned int LAST_RENDERABLE_ID = 0;
    static unsigned int newID();
    static color generateIndividualColor(const unsigned int& id);

protected:
    unsigned int iID;
    color v4IndividualColor;

public:
    UniqueID();
    ~UniqueID();

    unsigned int getID() const;
    color getIndividualColor() const;
    static unsigned int getLastID();
    static unsigned int colorToID(color col);
};