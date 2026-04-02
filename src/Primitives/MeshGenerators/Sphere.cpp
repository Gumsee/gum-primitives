#include "../Mesh.h"
#include <Essentials/Tools.h>

Mesh* Mesh::generateSphere(float radius, unsigned int slices, unsigned int stacks)
{
    if(slices < 3 || stacks < 2 || radius < 0.f)
      return nullptr;

    std::string name = "INTERNAL_SPHERE_" + std::to_string(radius) + "_" + std::to_string(slices) + "_" + std::to_string(stacks);
    if(Tools::mapHasKey(mLoadedMeshes, name))
        return mLoadedMeshes[name];

    Mesh* mesh = new Mesh(name);
    
    float z, xy;                     // vertex position
    float lengthInv = 1.0f / radius; // vertex normal

    float sectorStep = 2 * GUM_PI_F / slices;
    float stackStep = GUM_PI_F / stacks;
    float sectorAngle, stackAngle;

    for(unsigned int i = 0; i <= stacks; ++i)
    {
        stackAngle = GUM_PI_F / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // first and last vertices have same position and normal, but different tex coords
        for(unsigned int j = 0; j <= slices; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position
            #ifdef GUM_PRIMITIVES_MESH_UP_Z
            vec3 position(xy * cosf(sectorAngle), xy * sinf(sectorAngle), z);
            vec3 tangent(-xy * sinf(sectorAngle), 0, xy * cosf(sectorAngle));

            // vertex tex coord range between [0, 1]
            vec2 texcoords((float)j / slices, (float)i / stacks);
            #else
            vec3 position(xy * sinf(sectorAngle), z, xy * cosf(sectorAngle));
            vec3 tangent(-xy * cosf(sectorAngle), 0, xy * sinf(sectorAngle));

            // vertex tex coord range between [0, 1]
            vec2 texcoords((float)i / slices, (float)j / stacks);
            #endif

            // normalized vertex normal
            vec3 normal(position * lengthInv);

            mesh->addVertex(Vertex(position, texcoords, normal, tangent));
        }
    }

    unsigned int k1, k2;
    for(unsigned int i = 0; i < stacks; ++i)
    {
        k1 = i * (slices + 1);     // beginning of current stack
        k2 = k1 + slices + 1;      // beginning of next stack

        for(unsigned int j = 0; j < slices; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
              mesh->addTriangle(k1, k2, k1+1);

            // k1+1 => k2 => k2+1
            if(i != (stacks-1))
              mesh->addTriangle(k1+1, k2, k2+1);
        }
    }
    
    return mesh;
}

//Old version
/*Mesh* Mesh::generateUVSphere(const int& parallels, const int& meridians)
{
    std::string name = "INTERNAL_UV_SPHERE_" + std::to_string(parallels) + "_" + std::to_string(meridians);
    if(Tools::mapHasKey(mLoadedMeshes, std::string(name)))
        return mLoadedMeshes[name];

    Mesh* mesh = new Mesh();
    mesh->name = name;
    #ifndef GUM_PRIMITIVES_MESH_UP_Z
    mesh->vVertices.push_back(Vertex(vec3(0.0f, 1.0f, 0.0f), vec2(0,0), vec3(0,1,0)));
    #else
    mesh->vVertices.push_back(Vertex(vec3(0.0f, 0.0f, 1.0f), vec2(0,0), vec3(0,1,0)));
    #endif
	for (int j = 0; j < parallels - 1; ++j)
	{
		double const polar = GUM_PI_F * double(j+1) / double(parallels);
		double const sp = std::sin(polar);
		double const cp = std::cos(polar);
		for (int i = 0; i < meridians; ++i)
		{
			double const azimuth = 2.0 * GUM_PI_F * double(i) / double(meridians);
			double const sa = std::sin(azimuth);
			double const ca = std::cos(azimuth);
			double const x = sp * ca;
      #ifndef GUM_PRIMITIVES_MESH_UP_Z
			double const y = cp;
			double const z = sp * sa;
      #else
			double const y = sp * sa;
			double const z = cp;
      #endif
			mesh->vVertices.push_back(Vertex(vec3(x, y, z), vec2(0,0), vec3(x,y,z)));
		}
	}
    #ifndef GUM_PRIMITIVES_MESH_UP_Z
    mesh->vVertices.push_back(Vertex(vec3(0.0f, -1.0f, 0.0f), vec2(0,0), vec3(0,-1,0)));
    #else
    mesh->vVertices.push_back(Vertex(vec3(0.0f, 0.0f, -1.0f), vec2(0,0), vec3(0,-1,0)));
    #endif

	for (int i = 0; i < meridians; ++i)
	{
		int const a = i + 1;
		int const b = (i + 1) % meridians + 1;
		mesh->addTriangle(0, b, a);
	}

	for (int j = 0; j < parallels - 2; ++j)
	{
		int aStart = j * meridians + 1;
		int bStart = (j + 1) * meridians + 1;
		for (int i = 0; i < meridians; ++i)
		{
			const int a = aStart + i;
			const int a1 = aStart + (i + 1) % meridians;
			const int b = bStart + i;
			const int b1 = bStart + (i + 1) % meridians;
			mesh->addQuad(a, a1, b1, b);
		}
	}

	for (int i = 0; i < meridians; ++i)
	{
		int const a = i + meridians * (parallels - 2) + 1;
		int const b = (i + 1) % meridians + meridians * (parallels - 2) + 1;
		mesh->addTriangle(mesh->vVertices.size() - 1, a, b);
	}

    mLoadedMeshes[name] = mesh;
    return mesh;
}*/