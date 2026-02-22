#include "SkeletalAnimation.h"
#include "Maths/Maths.h"
#include <Essentials/Time.h>


SkeletalAnimation::SkeletalAnimation() : SkeletalAnimation("", ivec2(0,0), 0, 0) {}
SkeletalAnimation::SkeletalAnimation(std::string name, ivec2 frames, float speed, int priority)
    : sName(name),
      fStartTime(frames.x),
      fEndTime(frames.y),
      fSpeed(speed),
      iPriority(priority),
      bIsActive(false)
{}


unsigned int SkeletalAnimation::getPositionKeyframeByTime(Bone* bone)
{
    for(unsigned int i = 0; i < mPosKeyframes[bone].size() - 1; i++)
        if(fCurrentTime < mPosKeyframes[bone][i + 1].time)
            return i;
    return 0;
}

unsigned int SkeletalAnimation::getRotationKeyframeByTime(Bone* bone)
{
    for(unsigned int i = 0 ; i < mRotKeyframes[bone].size() - 1; i++)
        if(fCurrentTime < mRotKeyframes[bone][i + 1].time)
            return i;
    return 0;
}

vec3 SkeletalAnimation::getInterpolatedPosition(Bone* bone)
{
    if(mPosKeyframes[bone].size() == 1)
        return mPosKeyframes[bone][0].pos;

    unsigned int PositionIndex = getPositionKeyframeByTime(bone);
    unsigned int NextPositionIndex = PositionIndex + 1;

    float DeltaTime = mPosKeyframes[bone][NextPositionIndex].time - mPosKeyframes[bone][PositionIndex].time;
    float factor = (fCurrentTime - mPosKeyframes[bone][PositionIndex].time) / DeltaTime;

    const vec3 start = mPosKeyframes[bone][PositionIndex].pos;
    const vec3 end = mPosKeyframes[bone][NextPositionIndex].pos;

    return vec3::mix(start, end, factor);
}


quat SkeletalAnimation::getInterpolatedRotation(Bone* bone)
{
    if(mRotKeyframes[bone].size() == 1)
        return mRotKeyframes[bone][0].rot;

    unsigned int RotationIndex = getRotationKeyframeByTime(bone);
    unsigned int NextRotationIndex = RotationIndex + 1;

    float DeltaTime = mRotKeyframes[bone][NextRotationIndex].time - mRotKeyframes[bone][RotationIndex].time;
    float factor = (fCurrentTime - mRotKeyframes[bone][RotationIndex].time) / DeltaTime;

    const quat start = mRotKeyframes[bone][RotationIndex].rot;
    const quat end = mRotKeyframes[bone][NextRotationIndex].rot;

    //std::cout << bone->getName() << " " << RotationIndex << std::endl;
    return quat::slerp(start, end, factor);
}

void SkeletalAnimation::applyToBones(bool replaceoldtrans)
{
    if(!bIsActive)
        return;

    fCurrentTime += fSpeed * Time::getFrametime();
    if(fCurrentTime < fStartTime 
    || fCurrentTime > fEndTime)
        fCurrentTime = fStartTime;

    for(auto mapdata : mPosKeyframes)
    {
        Bone* bone = mapdata.first;
        //std::cout << "Updating " << bone->getName() << " by " << getName() << " " << getInterpolatedPosition(bone).toString() << std::endl;
    
        bone->updateTransform(Gum::Maths::createTransformationMatrix(
            getInterpolatedPosition(bone), 
            getInterpolatedRotation(bone), 
            vec3(1.0f)
        ));
    }
}


void SkeletalAnimation::removeUnusedKeyframes()
{
    for(auto it = mPosKeyframes.cbegin(); it != mPosKeyframes.cend();)
    {
        Bone* bone = it->first;
        if(mPosKeyframes[bone].size() == 2 
        && mPosKeyframes[bone][0].pos == mPosKeyframes[bone][1].pos)
        {
            it = mPosKeyframes.erase(it);
            continue;
        }
        
        it++;
    }
    
    for(auto it = mRotKeyframes.cbegin(); it != mRotKeyframes.cend();)
    {
        Bone* bone = it->first;
        if(mRotKeyframes[bone].size() == 2 
        && mRotKeyframes[bone][0].rot == mRotKeyframes[bone][1].rot)
        {
            it = mRotKeyframes.erase(it);
            continue;
        }
        
        it++;
    }
}


void SkeletalAnimation::addPosKeyframe(Bone* bone, SkeletalAnimation::PositionKeyframe keyframe) { if(bone != nullptr) mPosKeyframes[bone].push_back(keyframe); }
void SkeletalAnimation::addRotKeyframe(Bone* bone, SkeletalAnimation::RotationKeyframe keyframe) { if(bone != nullptr) mRotKeyframes[bone].push_back(keyframe); }


void SkeletalAnimation::activate(bool active)
{
    this->bIsActive = active;
}

std::string SkeletalAnimation::getName() { return this->sName; }

void SkeletalAnimation::setSpeed(float speed) { this->fSpeed = speed; }