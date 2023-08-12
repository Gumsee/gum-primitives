#pragma once
#include <gum-maths.h>

template<unsigned int N>
class Transformable
{
template<bool cond>
using resolvedType = typename std::enable_if<cond, void>::type; 
using RotationType = typename std::conditional<N == 3, quat, float>::type;
using MatrixType = typename std::conditional<N == 3, mat4, mat3>::type;

protected:
    tvec<float, N> vPosition, vRotationAroundPoint, vScale;
    RotationType qRotation;
    MatrixType mTransformation;

public:
    Transformable()
    {
        vPosition = tvec<float, N>(0.0f);
        qRotation = RotationType();
        vRotationAroundPoint = tvec<float, N>(0.0f);
        vScale = tvec<float, N>(1.0f);
    }

    ~Transformable()
    {

    }
    
    virtual void onTransformUpdate() {};
    virtual void updateMatrix()
    {
        mTransformation = Gum::Maths::createTransformationMatrix(vPosition, qRotation, vScale);
        onTransformUpdate();
    }
    


    void setPosition(tvec<float, N> pos)       { this->vPosition = pos; updateMatrix(); }
    void setRotation(RotationType rot)         { this->qRotation = rot; updateMatrix(); }
    template<unsigned int S = N>
    resolvedType<S == 3> setRotation(tvec<float, S> rot)       { this->qRotation = quat::toQuaternion(rot); updateMatrix(); }
    void setScale(tvec<float, N> scale)        { this->vScale = scale; updateMatrix(); }
    void setScale(float scale)                 { this->vScale = scale; updateMatrix(); }
    void increasePosition(tvec<float, N> pos)  { this->setPosition(vPosition + pos); }
    void increaseRotation(RotationType rot)    { this->setRotation(qRotation * rot); }
    void increaseScale(tvec<float, N> scale)   { this->setScale(vScale + scale); }
    template<unsigned int S = N>
    resolvedType<S == 3> increaseRotation(tvec<float, S> rot)  { this->setRotation(quat::toEuler(getRotation()) + rot); }
    
	virtual tvec<float, N> getPosition() const { return this->vPosition; }
	virtual RotationType getRotation() const   { return this->qRotation; }
	virtual tvec<float, N> getScale() const    { return this->vScale; }
	virtual MatrixType getMatrix() const       { return this->mTransformation; }
};

typedef Transformable<2> Transformable2D;
typedef Transformable<3> Transformable3D;