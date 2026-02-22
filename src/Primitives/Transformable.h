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
    

    void setMatrix(const mat4& mat)
    { 
        this->mTransformation = mat;

        vPosition = vec3(mTransformation[3][0], mTransformation[3][1], mTransformation[3][2]);

        float sx = vec3(mTransformation[0][0], mTransformation[0][1], mTransformation[0][2]).length();
        float sy = vec3(mTransformation[1][0], mTransformation[1][1], mTransformation[1][2]).length();
        float sz = vec3(mTransformation[2][0], mTransformation[2][1], mTransformation[2][2]).length();
        vScale = vec3(sx, sy, sz);

        mat3 rot {
            mTransformation[0][0] / sx, mTransformation[1][0] / sy, mTransformation[2][0] / sz,
            mTransformation[0][1] / sx, mTransformation[1][1] / sy, mTransformation[2][1] / sz,
            mTransformation[0][2] / sx, mTransformation[1][2] / sy, mTransformation[2][2] / sz
        };
        qRotation = quat(rot);

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
    resolvedType<S == 3> increaseRotation(tvec<float, S> rot)  { this->increaseRotation(quat::toQuaternion(rot)); }
    
	virtual tvec<float, N> getPosition() const { return this->vPosition; }
	virtual RotationType getRotation() const   { return this->qRotation; }
	virtual tvec<float, N> getScale() const    { return this->vScale; }
	virtual MatrixType getMatrix() const       { return this->mTransformation; }
};

typedef Transformable<2> Transformable2D;
typedef Transformable<3> Transformable3D;