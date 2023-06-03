#include "Transformable.h"

Transformable::Transformable()
{
	v3Position = vec3(0,0,0);
	qRotation = quat();
	v3RotationAroundPoint = vec3(0,0,0);
	v3Scale = vec3(1,1,1);
}

Transformable::~Transformable()
{
    
}

void Transformable::updateMatrix()
{
    m4Transformation = Gum::Maths::createTransformationMatrix(v3Position, qRotation, v3Scale);
    onTransformUpdate();
}

void Transformable::setPosition(vec3 pos)	   { this->v3Position = pos; updateMatrix(); }
void Transformable::setRotation(quat rot)	   { this->qRotation = rot; updateMatrix(); }
void Transformable::setRotation(vec3 rot)	   { this->qRotation = quat::toQuaternion(rot); updateMatrix(); }
void Transformable::setScale(vec3 scale)	   { this->v3Scale = scale; updateMatrix(); }
void Transformable::setScale(float scale)	   { this->v3Scale = scale; updateMatrix(); }
void Transformable::increasePosition(vec3 pos) { this->setPosition(v3Position + pos); }
void Transformable::increaseRotation(quat rot) { this->setRotation(qRotation * rot); }
void Transformable::increaseRotation(vec3 rot) { this->setRotation(quat::toEuler(getRotation()) + rot); }
void Transformable::increaseScale(vec3 scale)  { this->setScale(v3Scale + scale); }

vec3 Transformable::getPosition() const        { return this->v3Position; }
quat Transformable::getRotation() const        { return this->qRotation; }
vec3 Transformable::getScale() const           { return this->v3Scale; }
mat4 Transformable::getMatrix() const          { return this->m4Transformation; }