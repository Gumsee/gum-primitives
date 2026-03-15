#include "../Mesh.h"
#include <Essentials/Tools.h>

Mesh* Mesh::generateCube(const vec3& dimensions)
{
    std::string name = "INTERNAL_CUBE_" + dimensions.toString("", "", "_");
    if(Tools::mapHasKey(mLoadedMeshes, name))
        return mLoadedMeshes[name];

    Mesh* mesh = new Mesh(name);
    mesh->vVertices = { 
        Vertex(vec3(-dimensions.x,  dimensions.y,  dimensions.z) * 0.5f, vec2(1, 1), vec3( 0,  0,  1), vec3(-1, 0, 0), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3( dimensions.x, -dimensions.y,  dimensions.z) * 0.5f, vec2(0, 0), vec3( 0,  0,  1), vec3(-1, 0, 0), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3( dimensions.x,  dimensions.y,  dimensions.z) * 0.5f, vec2(0, 1), vec3( 0,  0,  1), vec3(-1, 0, 0), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3( dimensions.x, -dimensions.y,  dimensions.z) * 0.5f, vec2(0, 0), vec3( 0, -1,  0), vec3( 0, 0, 1), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3(-dimensions.x, -dimensions.y, -dimensions.z) * 0.5f, vec2(1, 1), vec3( 0, -1,  0), vec3( 0, 0, 1), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3( dimensions.x, -dimensions.y, -dimensions.z) * 0.5f, vec2(0, 1), vec3( 0, -1,  0), vec3( 0, 0, 1), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3(-dimensions.x, -dimensions.y,  dimensions.z) * 0.5f, vec2(1, 0), vec3(-1,  0,  0), vec3( 0, 0, 1), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3(-dimensions.x,  dimensions.y, -dimensions.z) * 0.5f, vec2(0, 1), vec3(-1,  0,  0), vec3( 0, 0, 1), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3(-dimensions.x, -dimensions.y, -dimensions.z) * 0.5f, vec2(1, 1), vec3(-1,  0,  0), vec3( 0, 0, 1), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3( dimensions.x,  dimensions.y, -dimensions.z) * 0.5f, vec2(1, 1), vec3( 0,  0, -1), vec3( 1, 0, 0), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3(-dimensions.x, -dimensions.y, -dimensions.z) * 0.5f, vec2(0, 0), vec3( 0,  0, -1), vec3( 1, 0, 0), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3(-dimensions.x,  dimensions.y, -dimensions.z) * 0.5f, vec2(0, 1), vec3( 0,  0, -1), vec3( 1, 0, 0), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3( dimensions.x,  dimensions.y,  dimensions.z) * 0.5f, vec2(0, 0), vec3( 1,  0,  0), vec3( 0, 0, 1), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3( dimensions.x, -dimensions.y, -dimensions.z) * 0.5f, vec2(1, 1), vec3( 1,  0,  0), vec3( 0, 0, 1), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3( dimensions.x,  dimensions.y, -dimensions.z) * 0.5f, vec2(0, 1), vec3( 1,  0,  0), vec3( 0, 0, 1), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3(-dimensions.x,  dimensions.y,  dimensions.z) * 0.5f, vec2(1, 0), vec3( 0,  1,  0), vec3( 0, 0, 1), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3( dimensions.x,  dimensions.y, -dimensions.z) * 0.5f, vec2(0, 1), vec3( 0,  1,  0), vec3( 0, 0, 1), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3(-dimensions.x,  dimensions.y, -dimensions.z) * 0.5f, vec2(1, 1), vec3( 0,  1,  0), vec3( 0, 0, 1), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3(-dimensions.x, -dimensions.y,  dimensions.z) * 0.5f, vec2(1, 0), vec3( 0,  0,  1), vec3(-1, 0, 0), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3(-dimensions.x, -dimensions.y,  dimensions.z) * 0.5f, vec2(1, 0), vec3( 0, -1,  0), vec3( 0, 0, 1), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3(-dimensions.x,  dimensions.y,  dimensions.z) * 0.5f, vec2(0, 0), vec3(-1,  0,  0), vec3( 0, 0, 1), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3( dimensions.x, -dimensions.y, -dimensions.z) * 0.5f, vec2(1, 0), vec3( 0,  0, -1), vec3( 1, 0, 0), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3( dimensions.x, -dimensions.y,  dimensions.z) * 0.5f, vec2(1, 0), vec3( 1,  0,  0), vec3( 0, 0, 1), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0), 
        Vertex(vec3( dimensions.x,  dimensions.y,  dimensions.z) * 0.5f, vec2(0, 0), vec3( 0,  1,  0), vec3( 0, 0, 1), vec3(0, 0, 0), ivec3(0, 0, 0), vec3(0, 0, 0), 0)
    };
    mesh->vIndices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 0, 18, 1, 3, 19, 4, 6, 20, 7, 9, 21, 10, 12, 22, 13, 15, 23, 16};

	return mesh;
}