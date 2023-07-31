#pragma once
#include <gum-maths.h>

class Transformable
{
protected:
    vec3 v3Position, v3RotationAroundPoint, v3Scale;
    quat qRotation;
    mat4 m4Transformation;

public:
    Transformable();
    ~Transformable();
    
    virtual void updateMatrix();
    virtual void onTransformUpdate() {};


    void setPosition(vec3 pos);
    void setRotation(quat rot);
    void setRotation(vec3 rot);
    void setScale(vec3 scale);
    void setScale(float scale);
    void increasePosition(vec3 pos);
    void increaseRotation(quat rot);
    void increaseRotation(vec3 rot);
    void increaseScale(vec3 scale);
    
	virtual vec3 getPosition() const;
	virtual quat getRotation() const;
	virtual vec3 getScale() const;
	virtual mat4 getMatrix() const;
};