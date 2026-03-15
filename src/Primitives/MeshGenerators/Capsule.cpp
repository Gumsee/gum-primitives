#include "../Mesh.h"
#include <Essentials/Tools.h>

Mesh* Mesh::generateCapsule(float radius, float height, unsigned int slices, unsigned int stacks)
{
    if(slices < 3 || stacks < 3 || !(stacks % 2))
      return nullptr;

    const float cylinderHeight = height - radius - radius;
    if(cylinderHeight < 0.f)
      return nullptr;

    std::string name = "INTERNAL_CAPSULE_" + std::to_string(radius) + "_" + std::to_string(height) + "_" + std::to_string(slices) + "_" + std::to_string(stacks);
    if(Tools::mapHasKey(mLoadedMeshes, name))
        return mLoadedMeshes[name];

    Mesh* mesh = new Mesh(name);

    #ifdef GUM_PRIMITIVES_MESH_UP_Z
    mesh->vVertices.push_back(Vertex(vec3(0.f, 0.f, -height * 0.5f), vec2(0, 0), vec3(0.f, 0.f, -1.f)));
    #else
    mesh->vVertices.push_back(Vertex(vec3(0.f, -height * 0.5f, 0.0f), vec2(0, 0), vec3(0.f, -1.f, 0.f)));
    #endif

    for(unsigned int i = 1; i < stacks; ++i)
    {
      const bool lowerPart = i <= stacks / 2;
      const float z = -radius * std::cos(static_cast<float>(lowerPart ? i : i - 1) * GUM_PI / (stacks - 1));
      const float r = radius * std::sin(static_cast<float>(lowerPart ? i : i - 1) * GUM_PI / (stacks - 1));
      for(unsigned int j = 0; j < slices; ++j)
      {
        const float x = r * std::cos(static_cast<float>(j) * 2.f * GUM_PI / slices);
        const float y = r * std::sin(static_cast<float>(j) * 2.f * GUM_PI / slices);
        #ifdef GUM_PRIMITIVES_MESH_UP_Z
        vec3 position(x, y, z);
        position.z += (lowerPart ? -cylinderHeight : cylinderHeight) * 0.5f;
        #else
        vec3 position(x, z, y);
        position.y += (lowerPart ? -cylinderHeight : cylinderHeight) * 0.5f;
        #endif
        const vec3 normal = vec3::normalize(position);
        mesh->vVertices.push_back(Vertex(position, vec2(0,0), normal));
      }
    }
    #ifdef GUM_PRIMITIVES_MESH_UP_Z
    mesh->vVertices.push_back(Vertex(vec3(0.f, 0.f, height * 0.5f), vec2(0, 0), vec3(0.f, 0.f, 1.f)));
    #else
    mesh->vVertices.push_back(Vertex(vec3(0.f, height * 0.5f, 0.f), vec2(0, 0), vec3(0.f, 1.f, 0.f)));
    #endif

    
    for(unsigned int i = 0; i < slices; ++i)
    {
      mesh->vIndices.push_back(0);
      mesh->vIndices.push_back(((i + 1) % slices) + 1);
      mesh->vIndices.push_back(i + 1);
    }
    for(unsigned int i = 0; i < stacks - 2; ++i)
    {
      for(unsigned int j = 0; j < slices; ++j)
      {
        mesh->vIndices.push_back(j + i * slices + 1);
        mesh->vIndices.push_back(((j + 1) % slices) + i * slices + 1);
        mesh->vIndices.push_back(((j + 1) % slices) + (i + 1) * slices + 1);
        mesh->vIndices.push_back(((j + 1) % slices) + (i + 1) * slices + 1);
        mesh->vIndices.push_back(j + (i + 1) * slices + 1);
        mesh->vIndices.push_back(j + i * slices + 1);
      }
    }
    for(unsigned int i = 0; i < slices; ++i)
    {
      mesh->vIndices.push_back((stacks - 1) * slices + 1);
      mesh->vIndices.push_back(i + (stacks - 2) * slices + 1);
      mesh->vIndices.push_back(((i + 1) % slices) + (stacks - 2) * slices + 1);
    }

    return mesh;
}