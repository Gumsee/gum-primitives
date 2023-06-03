#include "Curve.h"
#include <Maths/Maths.h>

static float F1(float u) { return 2.0f*powf(u, 3.0f) - 3.0f*powf(u, 2.0f) + 1; }
static float F2(float u) { return -2.0f*powf(u, 3.0f) + 3.0f*powf(u, 2.0f); }
static float F3(float u) { return powf(u, 3.0f) - 2.0f*powf(u, 2.0f) + u; }
static float F4(float u) { return powf(u, 3.0f) - powf(u, 2.0f); }

static float polynomBernstein(double m, double i, double u)
{ 
    return Gum::Maths::binomialCoeff((float)m, (float)i)*powf((float)u, (float)i)*powf(1.0f-(float)u, (float)m-(float)i); 
}
	

Curve::Curve(const CurveType& type)
{
    this->iType = type;
    this->iResolution = 50;
    this->iIterations = iResolution;
}

Curve::Curve(const std::vector<vec3>& points, const CurveType& type)
    : Curve(type)
{
    insert(end(), points.begin(), points.end());

    if(size() > 2)
    {
        switch(iType)
        {
            case BEZIER_BERNSTEIN: bezierCurveByBernstein(); break;
            case BEZIER_CASTELJAU: bezierCurveByCasteljau(); break;
        };
    }
    else
    {
        vData.insert(vData.end(), begin(), end());
    }
}

Curve::~Curve()
{

}

// create Bezier curve using Bernstein coeff
void Curve::bezierCurveByBernstein()
{
    vData.clear();
    float etape = (float)iIterations;
    float nbU = (float)iResolution;
    double n = (double)size() - 1.0;

    if(etape > nbU * (float)size()) 
        etape = nbU;

    
    for(double i = 0.0; i <= etape / nbU; i += 1.0 / nbU)
    {
        vec3 p;
        for(int j = 0; j <= n; ++j)
            p += at(j) * polynomBernstein(n, j, i);
        vData.push_back(p);
    }

    if(etape / nbU == 1) 
        vData.push_back(at(n));
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
        vData.push_back(at(size() - 1));
}

vec3 Curve::bezierCurveByCasteljauRec(std::vector<vec3> points, float i)
{
    if(points.size() == 1) 
        return points.at(0);
    
    std::vector<vec3> pts;
    for(unsigned int it = 0 ; it < points.size() - 1; it++)
    {
        vec3 vecteur = points.at(it + 1) - points.at(it);
        vecteur = vecteur * i;
        pts.push_back(points.at(it) + vecteur);
    }

    return bezierCurveByCasteljauRec(pts, i);
}

void Curve::addPoint(const vec3& point)
{
    push_back(point);
}

void Curve::removePoint(const int& index)
{
    erase(begin() + index);
}

//
// Setter
//
void Curve::setType(const CurveType& type) { this->iType = type; }

//
// Getter
//
Curve::CurveType Curve::getType() const  { return this->iType; }
std::vector<vec3> Curve::getData() const { return vData; }
unsigned int Curve::numPoints() const    { return (unsigned int)this->size(); }