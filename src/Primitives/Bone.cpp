#include "Bone.h"
#include <gum-maths.h>
#include <Essentials/Tools.h>


Bone::Bone(int id, std::string name, mat4 offsetmatrix)
    : iID(id), 
      sName(name), 
      m4OffsetMatrix(offsetmatrix), 
      mTranformationMatrix(offsetmatrix), 
      pParentBone(nullptr)
{
}

void Bone::updateTransform(mat4 transform)
{
    this->mTranformationMatrix = transform;
}

void Bone::addChild(Bone* bone) 
{ 
    if(bone == nullptr)
        return;
    
    this->vChildren.push_back(bone);
    bone->pParentBone = this;
}

std::string Bone::hierarchyString(const unsigned int& level)
{
    std::string retStr = Tools::repeatString("  ", level) + sName + "\n";

    for(Bone* child : vChildren)
        retStr += child->hierarchyString(level + 1);

    return retStr;
}


//
// Getter
//


Bone* Bone::getParent()                                                { return this->pParentBone; }
mat4 Bone::getOffsetMatrix()                                           { return this->m4OffsetMatrix; }
mat4 Bone::getTransform()                                              { return this->mTranformationMatrix; }
int Bone::getID()                                                      { return this->iID; }
Bone* Bone::getChild(const unsigned int& index)                        { return this->vChildren[index]; }
std::string Bone::getName()                                            { return this->sName; }
unsigned int Bone::numChildren()                                       { return this->vChildren.size(); }