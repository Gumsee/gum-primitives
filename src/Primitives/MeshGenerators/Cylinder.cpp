#include "../Mesh.h"
#include <Essentials/Tools.h>

Mesh* Mesh::generateCylinder(float radius, float height, unsigned int slices)
{
  if(slices < 3 || radius < 0.0f || height < 0.0f)
    return nullptr;

  std::string name = "INTERNAL_CYLINDER_" + std::to_string(radius) + "_" + std::to_string(height) + "_" + std::to_string(slices);
  if(Tools::mapHasKey(mLoadedMeshes, name))
      return mLoadedMeshes[name];

  Mesh* mesh = new Mesh(name);

  mesh->addVertex(Vertex(vec3(0.f, 0.f, -height * 0.5f), vec2(0.0f,0.0f), vec3(0.0f, 0.0f, -1.0f)));
  for(unsigned int i = 0; i < slices; ++i)
    mesh->addVertex(Vertex(vec3(radius * (float)std::cos(i * 2.0f * GUM_PI_F / slices), radius * (float)std::sin(i * 2.0f * GUM_PI_F / slices), -height * 0.5f), vec2(0.0f,0.0f), vec3(0.0f, 0.0f, -1.0f)));
  for(unsigned int i = 0; i < slices; ++i)
  {
    const float c = std::cos(static_cast<float>(i) * 2.0f * GUM_PI_F / static_cast<float>(slices));
    const float s = std::sin(static_cast<float>(i) * 2.0f * GUM_PI_F / static_cast<float>(slices));
    mesh->addVertex(Vertex(vec3(radius * c, radius * s, -height * 0.5f), vec2(0.0f,0.0f), vec3(c, s, 0.0f)));
  }
  for(unsigned int i = 0; i < slices; ++i)
  {
    const float c = std::cos(static_cast<float>(i) * 2.0f * GUM_PI_F / static_cast<float>(slices));
    const float s = std::sin(static_cast<float>(i) * 2.0f * GUM_PI_F / static_cast<float>(slices));
    mesh->addVertex(Vertex(vec3(radius * c, radius * s, height * 0.5f), vec2(0.0f,0.0f), vec3(c, s, 0.0f)));
  }
  for(unsigned int i = 0; i < slices; ++i)
    mesh->addVertex(Vertex(vec3(radius * (float)std::cos(i * 2.0f * GUM_PI_F / slices), radius * (float)std::sin(i * 2.0f * GUM_PI_F / slices), height * 0.5f), vec2(0.0f,0.0f), vec3(0.0f, 0.0f, 1.0f)));
  mesh->addVertex(Vertex(vec3(0.0f, 0.0f, height * 0.5f), vec2(0.0f,0.0f), vec3(0.0f, 0.0f, 1.0f)));
  

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

  return mesh;
}