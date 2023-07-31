#pragma once
#include <Maths/vec.h>

class UniqueID
{
private:
    inline static unsigned int LAST_RENDERABLE_ID = 0;
    static unsigned int newID();
    static vec4 generateIndividualColor(const unsigned int& id);

protected:
    unsigned int iID;
    vec4 v4IndividualColor;

public:
    UniqueID();
    ~UniqueID();

    unsigned int getID() const;
    vec4 getIndividualColor() const;
    static unsigned int getLastID();
};