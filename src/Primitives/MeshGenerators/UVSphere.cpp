#include "../Mesh.h"
#include <Essentials/Tools.h>

Mesh* Mesh::generateUVSphere(const int& parallels, const int& meridians)
{
    std::string name = "INTERNAL_UV_SPHERE_" + std::to_string(parallels) + "_" + std::to_string(meridians);
    if(Tools::mapHasKey(mLoadedMeshes, std::string(name)))
        return mLoadedMeshes[name];

    Mesh* mesh = new Mesh();
    mesh->name = name;
    mesh->vVertices.push_back(Vertex(vec3(0.0f, 1.0f, 0.0f), vec2(0,0), vec3(0,1,0)));
	for (int j = 0; j < parallels - 1; ++j)
	{
		double const polar = M_PI * double(j+1) / double(parallels);
		double const sp = std::sin(polar);
		double const cp = std::cos(polar);
		for (int i = 0; i < meridians; ++i)
		{
			double const azimuth = 2.0 * M_PI * double(i) / double(meridians);
			double const sa = std::sin(azimuth);
			double const ca = std::cos(azimuth);
			double const x = sp * ca;
			double const y = cp;
			double const z = sp * sa;
			mesh->vVertices.push_back(Vertex(vec3(x, y, z), vec2(0,0), vec3(x,y,z)));
		}
	}
	mesh->vVertices.push_back(Vertex(vec3(0.0f, -1.0f, 0.0f), vec2(0,0), vec3(0,-1,0)));

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
}