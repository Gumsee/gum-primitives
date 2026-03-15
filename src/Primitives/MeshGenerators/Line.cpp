#include "../Mesh.h"
#include <Essentials/Tools.h>

Mesh* Mesh::generateLine(const vec3& start, const vec3& end)
{
    std::string name = "INTERNAL_LINE_" + start.toString("", "", "_") + "_" + end.toString("", "", "_");
    if(Tools::mapHasKey(mLoadedMeshes, name))
        return mLoadedMeshes[name];

    Mesh* mesh = new Mesh(name);
    mesh->addVertex(Vertex(start, vec2(0,0), vec3(0.f, 0.f, 1.f)));
    mesh->addVertex(Vertex(end, vec2(0,0), vec3(0.f, 0.f, 1.f)));
  

  return mesh;
}