#include "../Mesh.h"
#include <Essentials/Tools.h>

Mesh* Mesh::generateCylinder(float radius, float height, unsigned int slices)
{
  if(slices < 3 || radius < 0.f || height < 0.f)
    return nullptr;

  std::string name = "INTERNAL_CYLINDER_" + std::to_string(radius) + "_" + std::to_string(height) + "_" + std::to_string(slices);
  if(Tools::mapHasKey(mLoadedMeshes, std::string(name)))
      return mLoadedMeshes[name];

  Mesh* mesh = new Mesh();
  mesh->name = name;

  mesh->addVertex(Vertex(vec3(0.f, 0.f, -height * 0.5f), vec2(0,0), vec3(0.f, 0.f, -1.f)));
  for(unsigned int i = 0; i < slices; ++i)
    mesh->addVertex(Vertex(vec3(radius * std::cos(i * 2.f * GUM_PI / slices), radius * std::sin(i * 2.f * GUM_PI / slices), -height * 0.5f), vec2(0,0), vec3(0.f, 0.f, -1.f)));
  for(unsigned int i = 0; i < slices; ++i)
  {
    const float c = std::cos(static_cast<float>(i) * 2.f * GUM_PI / static_cast<float>(slices));
    const float s = std::sin(static_cast<float>(i) * 2.f * GUM_PI / static_cast<float>(slices));
    mesh->addVertex(Vertex(vec3(radius * c, radius * s, -height * 0.5f), vec2(0,0), vec3(c, s, 0.f)));
  }
  for(unsigned int i = 0; i < slices; ++i)
  {
    const float c = std::cos(static_cast<float>(i) * 2.f * GUM_PI / static_cast<float>(slices));
    const float s = std::sin(static_cast<float>(i) * 2.f * GUM_PI / static_cast<float>(slices));
    mesh->addVertex(Vertex(vec3(radius * c, radius * s, height * 0.5f), vec2(0,0), vec3(c, s, 0.f)));
  }
  for(unsigned int i = 0; i < slices; ++i)
    mesh->addVertex(Vertex(vec3(radius * std::cos(i * 2.f * GUM_PI / slices), radius * std::sin(i * 2.f * GUM_PI / slices), height * 0.5f), vec2(0,0), vec3(0.f, 0.f, 1.f)));
  mesh->addVertex(Vertex(vec3(0.f, 0.f, height * 0.5f), vec2(0,0), vec3(0.f, 0.f, 1.f)));
  

  for(unsigned int i = 0; i < slices; ++i)
  {
    mesh->addIndex(0);
    mesh->addIndex(((i + 1) % slices) + 1);
    mesh->addIndex(i + 1);
  }
  for(unsigned int i = 0; i < slices; ++i)
  {
    mesh->addIndex(i + slices + 1);
    mesh->addIndex(((i + 1) % slices) + slices + 1);
    mesh->addIndex(((i + 1) % slices) + 2 * slices + 1);
    mesh->addIndex(((i + 1) % slices) + 2 * slices + 1);
    mesh->addIndex(i + 2 * slices + 1);
    mesh->addIndex(i + slices + 1);
  }
  for(unsigned int i = 0; i < slices; ++i)
  {
    mesh->addIndex(((i + 1) % slices) + 3 * slices + 1);
    mesh->addIndex(4 * slices + 1);
    mesh->addIndex(i + 3 * slices + 1);
  }

  mLoadedMeshes[name] = mesh;
  return mesh;
}