#include "Mesh.h"
#include <fstream>
#include <string>
#include "Essentials/Tools.h"
#include <assert.h>

Mesh::Mesh(std::string name)
  : name(name)
{
  offsetMatrix = mat4(1);
  iMatIndex = -1;

  assert(!name.empty());

  mLoadedMeshes[name] = this;
};

Mesh::~Mesh()
{
  if(Tools::mapHasKey(mLoadedMeshes, name))
    mLoadedMeshes.erase(name);
}


void Mesh::addVertex(const Vertex& vertex)
{
  this->vVertices.push_back(vertex);
}

void Mesh::addIndex(const unsigned int& index)
{
  this->vIndices.push_back(index);
}

void Mesh::addVertices(const crate<Vertex>& vertices)
{
  for(size_t i = 0; i < vertices.size(); i++)
    addVertex(vertices[i]);
}

void Mesh::addIndices(const crate<unsigned int>& indices)
{
  for(size_t i = 0; i < indices.size(); i++)
    addIndex(indices[i]);
}

void Mesh::addTriangle(const int& a, const int& b, const int& c)
{
  vIndices.push_back(a);
  vIndices.push_back(b);
  vIndices.push_back(c);
}

void Mesh::addQuad(const int& a, const int& b, const int& c, const int& d)
{
  vIndices.push_back(a);
  vIndices.push_back(b);
  vIndices.push_back(c);
  vIndices.push_back(a);
  vIndices.push_back(c);
  vIndices.push_back(d);
}

void Mesh::addMesh(Mesh *mesh)
{
  int IndexOffset = (int)this->vVertices.size();
  for(size_t i = 0; i < mesh->vVertices.size(); i++)
    this->vVertices.push_back(mesh->vVertices[i]);

  for(size_t i = 0; i < mesh->vIndices.size(); i++)
    this->vIndices.push_back(mesh->vIndices[i] + IndexOffset);
}


//Side Functions
void Mesh::writeMeshInfoToFile(std::string filename)  //Move to fileparser
{
	//Gum::Output::info("Writing Mesh Info " + getName() + " to " + filename);
	std::ofstream file(filename);

	//General Info
	file << "//General Information\n";
	file << "std::string Name = " << name << ";\n";

	//Vertex Info
	std::string verticesString;
	for(unsigned int i = 0; i < numVertices(); i++) { verticesString += getVertex(i).toString("vec3(", "vec2(") + ", \n"; };

	std::string indicesString;
	for(unsigned int i = 0; i < numIndices(); i++) { indicesString += std::to_string(getIndex(i)) + ", "; };
	
	file << "\n//Vertices Information\n";
	file << "crate<Vertex> vertices = { \n" << verticesString << "};\n";
	file << "crate<int> indices = {" << indicesString << "};\n";

	/*file << "\n#Transformation Information\n";
	file << "Position: " << Tools::Vec3ToString(this->pProperties->getPosition()) << "\n";
	file << "Rotation: " << Tools::Vec3ToString(this->pProperties->getRotationEuler()) << "\n";
	file << "Scale: " << Tools::Vec3ToString(this->pProperties->getScale()) << "\n";*/

	file.close();
}


//Getters
unsigned int Mesh::numVertices() const                       { return (unsigned int)this->vVertices.size(); }
unsigned int Mesh::numIndices() const                        { return (unsigned int)this->vIndices.size(); }
Vertex& Mesh::getVertex(const unsigned int& index)           { return this->vVertices[index]; }
unsigned int Mesh::getIndex(const unsigned int& index) const { return this->vIndices[index]; }
crate<Vertex> Mesh::getVertexBuffer() const                  { return this->vVertices; }
crate<unsigned int> Mesh::getIndexBuffer() const             { return this->vIndices; }


SerializationData& Mesh::serialize(SerializationData& data)
{
  return data & name & vVertices & vIndices;
}


Mesh* Mesh::getMesh(std::string name)
{
  if(Tools::mapHasKey(mLoadedMeshes, name))
      return mLoadedMeshes[name];
  
  return new Mesh(name);
}

void Mesh::destroyAllMeshes()
{
  while(mLoadedMeshes.size() > 0)
    Gum::_delete(mLoadedMeshes.begin()->second);
}