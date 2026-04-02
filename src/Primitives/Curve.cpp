#include "Curve.h"
#include <Maths/Maths.h>

//static float F1(float u) { return 2.0f*powf(u, 3.0f) - 3.0f*powf(u, 2.0f) + 1; }
//static float F2(float u) { return -2.0f*powf(u, 3.0f) + 3.0f*powf(u, 2.0f); }
//static float F3(float u) { return powf(u, 3.0f) - 2.0f*powf(u, 2.0f) + u; }
//static float F4(float u) { return powf(u, 3.0f) - powf(u, 2.0f); }

static float polynomBernstein(int m, int i, float u)
{ 
    return (float)Gum::Maths::binomialCoeff(m, i) * powf(u, (float)i) * powf(1.0f - u, (float)m - (float)i); 
}
	

Curve::Curve(const CurveType& type)
{
    this->iType = type;
    this->iResolution = 50;
    this->iIterations = iResolution;
}

Curve::Curve(const crate<vec3>& points, const CurveType& type)
    : Curve(type)
{
    insert(end(), points.begin(), points.end());
    updateData();
}

Curve::~Curve()
{

}

void Curve::updateData()
{
    if(size() > 2)
    {
        switch(iType)
        {
            case BEZIER_BERNSTEIN: bezierCurveByBernstein(); break;
            case BEZIER_CASTELJAU: bezierCurveByCasteljau(); break;
            case STRAIGHT:         vData.clear(); vData.insert(vData.begin(), begin(), end()); break;
        };
    }
    else
    {
        vData.clear();
        vData.insert(vData.begin(), begin(), end());
    }
}

// create Bezier curve using Bernstein coeff
void Curve::bezierCurveByBernstein()
{
    vData.clear();
    float etape = (float)iIterations;
    float nbU = (float)iResolution;
    int n = (int)size() - 1;

    if(etape > nbU * (float)size()) 
        etape = nbU;

    
    for(float i = 0.0; i <= etape / nbU; i += 1.0f / nbU)
    {
        vec3 p;
        for(int j = 0; j <= n; ++j)
            p += at(j, vec3()) * polynomBernstein(n, j, i);
        vData.push_back(p);
    }

    if(etape / nbU == 1) 
        vData.push_back(at(n, vec3()));
}

// create recursively Bezier curve using Casteljau method
void Curve::bezierCurveByCasteljau()
{
    vData.clear();

    float etape = (float)iIterations;
    float nbU = (float)iResolution;
    
    if(etape > nbU * size()) 
        etape = nbU;

    
    for(float i = 0.0f; i <= etape / nbU; i += 1.0f/nbU)
    {
        vec3 v = bezierCurveByCasteljauRec(*this, (float)i);
        vData.push_back(v);
    }

    if(etape / nbU == 1)
        vData.push_back(at(size() - 1, vec3()));
}

vec3 Curve::bezierCurveByCasteljauRec(crate<vec3> points, float i)
{
    if(points.size() == 1) 
        return points.at(0, vec3());
    
    crate<vec3> pts;
    for(unsigned int it = 0 ; it < points.size() - 1; it++)
    {
        vec3 vecteur = points.at(it + 1, vec3()) - points.at(it, vec3());
        vecteur = vecteur * i;
        pts.push_back(points.at(it, vec3()) + vecteur);
    }

    return bezierCurveByCasteljauRec(pts, i);
}

void Curve::movePoint(const unsigned int& index, const vec3& point)
{
    operator[](index) = point;
    updateData();
}

void Curve::addPoint(const vec3& point, bool update)
{
    push_back(point);
    if(update)
        updateData();
}

void Curve::removePoint(const int& index)
{
    erase(begin() + index);
    updateData();
}

//
// Setter
//
void Curve::setType(const CurveType& type) { this->iType = type; }

//
// Getter
//
Curve::CurveType Curve::getType() const           { return this->iType; }
crate<vec3> Curve::getData() const          { return vData; }
crate<vec3> Curve::getControlpoints() const { return (crate<vec3>)*this; }
unsigned int Curve::numPoints() const             { return (unsigned int)this->size(); }