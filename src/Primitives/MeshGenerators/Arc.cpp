#include "../Mesh.h"
#include <Essentials/Tools.h>

Mesh* Mesh::generateArc(const vec2& dimensions, const double& angle, const unsigned int& resolution)
{
    std::string name = "INTERNAL_ARC_" + std::to_string(angle) + "_" + std::to_string(resolution);
    if(Tools::mapHasKey(mLoadedMeshes, name))
        return mLoadedMeshes[name];

    Mesh* mesh = new Mesh(name);

    double stepsize = angle / (double)resolution;
    for(double i = 0; i < angle; i += stepsize)
    {
        Vertex vert;
        vert.position = vec3(
            cos(Gum::Maths::toRadians(i)) * dimensions.x,
            0.0f,
            sin(Gum::Maths::toRadians(i)) * dimensions.y
        );
        mesh->addVertex(vert);
    }

    return mesh;
}

Mesh* Mesh::generateCircle(const vec2& dimensions, const unsigned int& resolution)
{
    return generateArc(dimensions, 360.0, resolution);
}