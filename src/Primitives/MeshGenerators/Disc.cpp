#include "../Mesh.h"
#include <Essentials/Tools.h>


Mesh* Mesh::generateDisk(const float& inner, const float& outer, const unsigned int& slices)
{
  if(slices < 3 || inner < 0.f || outer < 0.f)
    return nullptr;

  std::string name = "INTERNAL_DISC_" + std::to_string(inner) + "_" + std::to_string(outer) + "_" + std::to_string(slices);
  if(Tools::mapHasKey(mLoadedMeshes, std::string(name)))
      return mLoadedMeshes[name];

  Mesh* mesh = new Mesh();
  mesh->name = name;

  
  for(unsigned int i = 0; i < slices; ++i)
  {
    const float c = std::cos(static_cast<float>(i) * 2.f * GUM_PI / static_cast<float>(slices));
    const float s = std::sin(static_cast<float>(i) * 2.f * GUM_PI / static_cast<float>(slices));
    const float xInner = c * inner;
    const float yInner = s * inner;
    const float xOuter = c * outer;
    const float yOuter = s * outer;
    mesh->addVertex(Vertex(vec3(xInner, yInner, 0.f), vec2(0,0), vec3(0.f, 0.f, 1.f)));
    mesh->addVertex(Vertex(vec3(xOuter, yOuter, 0.f), vec2(0,0), vec3(0.f, 0.f, 1.f)));
    mesh->addVertex(Vertex(vec3(xInner, yInner, 0.f), vec2(0,0), vec3(0.f, 0.f, -1.f)));
    mesh->addVertex(Vertex(vec3(xOuter, yOuter, 0.f), vec2(0,0), vec3(0.f, 0.f, -1.f)));
  }
  
  for(unsigned int side = 0; side < 2; ++side)
  {
    for(unsigned int i = 0; i < slices; ++i)
    {
      mesh->addIndex(4 * i + side + 2 * side);
      mesh->addIndex(4 * i + (1 - side) + 2 * side);
      mesh->addIndex(4 * ((i + 1) % slices) + side + 2 * side);
      mesh->addIndex(4 * ((i + 1) % slices) + side + 2 * side);
      mesh->addIndex(4 * ((i + 1) % slices) + (1 - side) + 2 * side);
      mesh->addIndex(4 * i + side + 2 * side);
    }
  }

  mLoadedMeshes[name] = mesh;
	return mesh;
}