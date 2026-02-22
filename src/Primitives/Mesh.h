#pragma once
#include "Essentials/SerializationData.h"
#include "Vertex.h"
#include <Essentials/Serialization.h>
#include <map>
#include <Essentials/Crate.h>
#include <string>

class Mesh : public Serialization
{
public:
    static std::map<std::string, Mesh*> mLoadedMeshes;

private:
    crate<Vertex> vVertices;
    crate<unsigned int> vIndices;

public:
    Mesh();
    ~Mesh() {};

    mat4 offsetMatrix; //For scene imports
	int iMatIndex;
    std::string name;

    void addVertex(const Vertex& vertex);
    void addVertices(const crate<Vertex>& vertices);
    void addIndex(const unsigned int& index);
    void addIndices(const crate<unsigned int>& indices);
    void addTriangle(const int& a, const int& b, const int& c);
    void addQuad(const int& a, const int& b, const int& c, const int& d);
    void addMesh(Mesh *mesh);

    //Static methods
    static Mesh* generateUVSphere(const int& parallels, const int& meridians);
    static Mesh* generateCube(const vec3& dimensions);
    static Mesh* generatePlane(const vec2& dimensions);
    static Mesh* generateCircle(const vec2& dimensions, const unsigned int& resolution = 32);
    static Mesh* generateArc(const vec2& dimensions, const double& angle, const unsigned int& resolution = 32);

	void writeMeshInfoToFile(std::string filename);

    //Getter
    unsigned int numVertices() const;
    unsigned int numIndices() const;
    Vertex& getVertex(const unsigned int& index);
    unsigned int getIndex(const unsigned int& index) const;
    crate<Vertex> getVertexBuffer() const;
    crate<unsigned int> getIndexBuffer() const;

    SerializationData& serialize(SerializationData& data) override;
};