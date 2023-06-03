#pragma once
#include <Maths/vec.h>
#include <vector>

class Curve : private std::vector<vec3>
{
public:
    enum CurveType
    {
        BEZIER_BERNSTEIN,
        BEZIER_CASTELJAU,
    };

private:
    CurveType iType;
    std::vector<vec3> vData;
    unsigned int iResolution;
    unsigned int iIterations;

    void bezierCurveByBernstein();
    void bezierCurveByCasteljau();
    vec3 bezierCurveByCasteljauRec(std::vector<vec3> points, float i);

public:
    Curve(const CurveType& type);
    Curve(const std::vector<vec3>& points, const CurveType& type);
    ~Curve();

    void addPoint(const vec3& point);
    void removePoint(const int& index);

    using std::vector<vec3>::operator[];

    //Setter
    void setType(const CurveType& type);

    //Getter
    CurveType getType() const;
    std::vector<vec3> getData() const;
    unsigned int numPoints() const;
};