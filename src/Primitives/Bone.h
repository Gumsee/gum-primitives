#pragma once
#include "Mesh.h"

#include <string>
#include <sstream>
#include <vector>

class Bone
{
private: 
      mat4 TranformationMatrix;
      std::string sName;
      Mesh* mesh;
      Bone* pParentBone; 
      mat4 m4OffsetMatrix;

      std::vector<vec3> PosKeys;
      std::vector<quat> RotKeys;
      std::vector<float> Times;
      std::vector<Bone*> vChildren;

      unsigned int iID;

      void setParent(Bone* bone);

public:
      Bone(Mesh* in_mesh, unsigned int in_id, std::string in_name, mat4 in_o_mat, mat4 transform);

      void UpdateKeyframeTransform(float time);

      unsigned int FindPosition(float time);
      unsigned int FindRotation(float time);

      quat CalcInterpolatedRotation(float time);
      vec3 CalcInterpolatedPosition(float time);

      void addChild(Bone* bone);

      void setTransform(mat4 trans);

      Bone* getParent();
      Bone* getChild(int index);
      unsigned int numChildren();
      mat4 getOffsetMatrix();
      mat4 getTransform();
      std::string getName();
      unsigned int getID();
      std::string hierarchyString(unsigned int level);
};