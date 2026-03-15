#include "../Mesh.h"
#include <Essentials/Tools.h>

Mesh* Mesh::generatePlane(const vec2& dimensions)
{
    std::string name = "INTERNAL_PLANE_" + dimensions.toString("", "", "_");
    if(Tools::mapHasKey(mLoadedMeshes, name))
        return mLoadedMeshes[name];

    Mesh* mesh = new Mesh(name);
    mesh->vVertices = { 
        Vertex(vec3( dimensions.x, 0.0f,  dimensions.y), vec2(1, 1), vec3(0, 1, 0), vec3(1, 0, 0), vec3(0, 0, 1), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3( dimensions.x, 0.0f, -dimensions.y), vec2(1, 0), vec3(0, 1, 0), vec3(1, 0, 0), vec3(0, 0, 1), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3(-dimensions.x, 0.0f,  dimensions.y), vec2(0, 1), vec3(0, 1, 0), vec3(1, 0, 0), vec3(0, 0, 1), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3(-dimensions.x, 0.0f, -dimensions.y), vec2(0, 0), vec3(0, 1, 0), vec3(1, 0, 0), vec3(0, 0, 1), ivec3(0, 0, 0), vec3(0, 0, 0), 0)
    };
    mesh->vIndices = {0, 1, 2, 1, 3, 2};

	return mesh;
}