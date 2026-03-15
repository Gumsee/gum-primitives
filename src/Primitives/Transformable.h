#pragma once
#include <gum-maths.h>

#define TRANSFORMABLE_VECTOR_TRANSLATION VectorType(*vPosition.x, *vPosition.y, *vPosition.z)
#define TRANSFORMABLE_ROTATION_TRANSLATION RotationType(*qRotation.w, *qRotation.x, *qRotation.y, *qRotation.z)

template<typename T, unsigned int N>
class Transformable
{
template<bool cond>
using resolvedType = std::enable_if_t<cond, void>;
typedef std::remove_pointer_t<T>                             PureType;
typedef tvec<T, N>                                           VectorTypeInternal;
typedef tvec<PureType, N>                                    VectorType;
typedef std::conditional_t<N == 3, quat<T>, T>               RotationTypeInternal;
typedef std::conditional_t<N == 3, quat<PureType>, PureType> RotationType;
typedef std::conditional_t<N == 3, mat<PureType,4,4>, mat<PureType,3,3>>   MatrixType;

protected:
    VectorTypeInternal vPosition;
    VectorType vRotationAroundPoint, vScale;
    RotationTypeInternal qRotation;
    MatrixType mTransformation;

public:
    Transformable()
      : vScale(VectorType(1.0f)) {}
    
    virtual void onTransformUpdate() {};
    virtual void updateMatrix()
    {
        if constexpr (!std::is_pointer<T>::value)
            mTransformation = Gum::Maths::createTransformationMatrix(vPosition, qRotation, vScale);
        else
            mTransformation = Gum::Maths::createTransformationMatrix(TRANSFORMABLE_VECTOR_TRANSLATION, TRANSFORMABLE_ROTATION_TRANSLATION, vScale);
        onTransformUpdate();
    }
    

    void setMatrix(const MatrixType& m)
    { 
        this->mTransformation = m;

        vPosition = VectorType(mTransformation[3][0], mTransformation[3][1], mTransformation[3][2]);
        vScale = VectorType(
            VectorType(mTransformation[0][0], mTransformation[0][1], mTransformation[0][2]).length(),
            VectorType(mTransformation[1][0], mTransformation[1][1], mTransformation[1][2]).length(),
            VectorType(mTransformation[2][0], mTransformation[2][1], mTransformation[2][2]).length()
        );

        mat<PureType, 3, 3> rot {
            mTransformation[0][0] / vScale.x, mTransformation[1][0] / vScale.y, mTransformation[2][0] / vScale.z,
            mTransformation[0][1] / vScale.x, mTransformation[1][1] / vScale.y, mTransformation[2][1] / vScale.z,
            mTransformation[0][2] / vScale.x, mTransformation[1][2] / vScale.y, mTransformation[2][2] / vScale.z
        };
        qRotation = RotationType(rot);

        onTransformUpdate(); 
    }
    void setPosition(VectorType pos)                         { this->vPosition = pos; updateMatrix(); }
    void setRotation(RotationType rot)                       { this->qRotation = rot; updateMatrix(); }
    template<unsigned int S = N>
    resolvedType<S == 3> setRotation(VectorType rot)         { this->qRotation = RotationType::toQuaternion(rot); updateMatrix(); }
    void setScale(VectorType scale)                          { this->vScale = scale; updateMatrix(); }
    void setScale(PureType scale)                            { this->vScale = scale; updateMatrix(); }
    void increasePosition(VectorType pos)                    { this->vPosition += pos; updateMatrix(); }
    void increaseRotation(RotationType rot)                  { this->setRotation(qRotation * rot); }
    void increaseScale(VectorType scale)                     { this->setScale(vScale + scale); }
    template<unsigned int S = N>
    resolvedType<S == 3> increaseRotation(VectorType rot)    { this->increaseRotation(RotationType::toQuaternion(rot)); }
    
	virtual VectorType& getPosition()                   { if constexpr (!std::is_pointer<T>::value) return this->vPosition; else return TRANSFORMABLE_VECTOR_TRANSLATION; }
	virtual RotationType& getRotation()                 { if constexpr (!std::is_pointer<T>::value) return this->qRotation; else return TRANSFORMABLE_ROTATION_TRANSLATION; }
	virtual VectorTypeInternal getInternalPosition() const   { return this->vPosition; }
	virtual RotationTypeInternal getInternalRotation() const { return this->qRotation; }
	virtual VectorType& getScale()                      { return this->vScale; }
	virtual MatrixType& getMatrix()                     { return this->mTransformation; }
};

typedef Transformable<float, 2> Transformable2D;
typedef Transformable<float, 3> Transformable3D;
typedef Transformable<double, 2> Transformable2Dd;
typedef Transformable<double, 3> Transformable3Dd;