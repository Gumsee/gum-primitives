#pragma once
#include <Maths/vec.h>
#include <Essentials/Crate.h>
#include "UniqueID.h"

class Curve : private crate<vec3>, public UniqueID
{
public:
    enum CurveType
    {
        BEZIER_BERNSTEIN,
        BEZIER_CASTELJAU,
        STRAIGHT
    };

private:
    CurveType iType;
    crate<vec3> vData;
    unsigned int iResolution;
    unsigned int iIterations;

    void bezierCurveByBernstein();
    void bezierCurveByCasteljau();
    vec3 bezierCurveByCasteljauRec(crate<vec3> points, float i);

public:
    Curve(const CurveType& type);
    Curve(const crate<vec3>& points, const CurveType& type);
    ~Curve();

    void movePoint(const unsigned int& index, const vec3& point);
    void addPoint(const vec3& point, bool update = true);
    void removePoint(const int& index);

    void updateData();

    using crate<vec3>::operator[];

    //Setter
    void setType(const CurveType& type);

    //Getter
    CurveType getType() const;
    crate<vec3> getData() const;
    crate<vec3> getControlpoints() const;
    unsigned int numPoints() const;
};