#include "../Mesh.h"
#include <Essentials/Tools.h>

Mesh* Mesh::generatePyramid(const vec2& footprint, const float& height)
{
    std::string name = "INTERNAL_PYRAMID_" + footprint.toString("", "", "_") + std::to_string(height);
    if(Tools::mapHasKey(mLoadedMeshes, name))
        return mLoadedMeshes[name];

    Mesh* mesh = new Mesh();
    mesh->name = name;
  
  mesh->addVertex(Vertex(vec3(0.f, 0.f, 0.f), vec2(0,0), vec3(0.f, 0.f, 1.f)));
  mesh->addVertex(Vertex(vec3(footprint.x, -footprint.y * 0.5f, -height * 0.5f), vec2(0,0), vec3(0.f, 0.f, 1.f)));
  mesh->addVertex(Vertex(vec3(footprint.x, -footprint.y * 0.5f, height * 0.5f), vec2(0,0), vec3(0.f, 0.f, 1.f)));
  mesh->addVertex(Vertex(vec3(footprint.x, footprint.y * 0.5f, height * 0.5f), vec2(0,0), vec3(0.f, 0.f, 1.f)));
  mesh->addVertex(Vertex(vec3(footprint.x, footprint.y * 0.5f, -height * 0.5f), vec2(0,0), vec3(0.f, 0.f, 1.f)));

  for(unsigned int i = 1; i <= 4; ++i)
  {
    mesh->addIndex(0);
    mesh->addIndex(i);
  }
  for(unsigned int i = 1; i <= 4; ++i)
  {
    mesh->addIndex(i);
    mesh->addIndex((i % 4) + 1);
  }

  mLoadedMeshes[name] = mesh;
	return mesh;
}