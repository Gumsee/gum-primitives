#pragma once
#include "Mesh.h"
#include <string>
#include <Essentials/Crate.h>

class Bone
{
private:
    int iID;
    std::string sName;
    mat4 m4OffsetMatrix;
    mat4 mTranformationMatrix;

    Bone* pParentBone;
    crate<Bone*> vChildren;

public:
    Bone(int id, std::string name, mat4 offsetmatrix);

    void updateTransform(mat4 transform);

    void addChild(Bone* bone);
    std::string hierarchyString(const unsigned int& level = 0);

    Bone* getParent();
    Bone* getChild(const unsigned int& index);
    mat4 getOffsetMatrix();
    mat4 getTransform();
    std::string getName();
    int getID();
    unsigned int numChildren();
};