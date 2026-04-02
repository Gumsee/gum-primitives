#pragma once
#include <map>
#include <string>
#include <Maths/quat.h>
#include "Bone.h"

class SkeletalAnimation
{
public:
    struct PositionKeyframe
    {
        vec3 pos;
        float time;

        PositionKeyframe(vec3 pos, float time)
            : pos(pos), time(time) {}
    };

    struct RotationKeyframe
    {
        fquat rot;
        float time;

        RotationKeyframe(fquat rot, float time)
            : rot(rot), time(time) {}
    };

private:
    std::string sName;
    float fSpeed;
    float fStartTime;
    float fEndTime;
    float fCurrentTime;
    int iPriority;
    bool bIsActive;

    std::map<Bone*, crate<PositionKeyframe> > mPosKeyframes;
    std::map<Bone*, crate<RotationKeyframe> > mRotKeyframes;

    unsigned int getPositionKeyframeByTime(Bone* bone);
    unsigned int getRotationKeyframeByTime(Bone* bone);
    fquat getInterpolatedRotation(Bone* bone);
    vec3 getInterpolatedPosition(Bone* bone);

public:
    SkeletalAnimation();
    SkeletalAnimation(std::string name, ivec2 frames, float speed, int priority = 0);


    void applyToBones();

    void addPosKeyframe(Bone* bone, PositionKeyframe keyframe);
    void addRotKeyframe(Bone* bone, RotationKeyframe keyframe);

    void activate(bool active);
    void removeUnusedKeyframes();
    
    //Bone::PositionKeyframe Bone::getPosKeyframe(const unsigned int& index) { return this->vPosKeyframes[index]; }
    //Bone::RotationKeyframe Bone::getRotKeyframe(const unsigned int& index) { return this->vRotKeyframes[index]; }

    std::string getName();
    int getPriority();

    void setSpeed(float speed);
};