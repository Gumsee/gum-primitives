#pragma once
#include "Essentials/SerializationData.h"
#include <gum-maths.h>
#include <Essentials/Serialization.h>

struct Vertex : public Serialization
{
    vec3 position;
    vec2 textureCoord;
    vec3 normal, tangent, bitangent;

    //Skeletal (bone info)
    ivec4 JointIDs;
    vec4 Weights;
    int BaseVertex;


    Vertex() 
    {
        this->position = vec3(0,0,0);
        this->textureCoord = vec2(0,0);
        this->normal = vec3(0,0,0);
        this->tangent = vec3(0,0,0);
        this->bitangent = vec3(0,0,0);
        this->JointIDs = ivec4(-1,-1,-1,-1);
        this->Weights = vec4(0,0,0,0);
        this->BaseVertex = 0;
    }

    
    Vertex(vec3 pos, vec2 textureCoord = vec2(0,0), vec3 normal = vec3(0,0,0), vec3 tangent = vec3(0,0,0), vec3 bitangent = vec3(0,0,0), ivec4 jointIDs = ivec4(-1,-1,-1,-1), vec4 weights = vec4(0,0,0,0), int basevertex = 0)
    {
        this->position = pos;
        this->textureCoord = textureCoord;
        this->normal = normal;
        this->tangent = tangent;
        this->bitangent = bitangent;
        this->JointIDs = jointIDs;
        this->Weights = weights;
        this->BaseVertex = basevertex;
    }

    virtual ~Vertex() {}

    std::string toString(std::string vec3Prefix = "", std::string vec2Prefix = "")
    {
        return "Vertex(" + 
            position.toString(vec3Prefix) + ", " +
            textureCoord.toString(vec2Prefix)         + ", " +
            normal.toString(vec3Prefix)               + ", " +
            tangent.toString(vec3Prefix)              + ", " +
            bitangent.toString(vec3Prefix)            + ", " +
            JointIDs.toString("i" + vec3Prefix)       + ", " +
            Weights.toString(vec3Prefix)              + ", " +
            std::to_string(BaseVertex)                +
        ")";
    }

    SerializationData& serialize(SerializationData& data) override
    {
        return data & position & textureCoord & normal & tangent & JointIDs & Weights & BaseVertex;
    }
};