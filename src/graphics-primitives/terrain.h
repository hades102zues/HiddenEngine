#pragma once
#include "vertex.h"
#include <vector>
#include "mesh.h"
#include <memory>



class Terrain {
private:
    int mNumVerticesAlongTerrainSide;
    int mNumTileSides;
    float mBaseRealX;
    float mBaseRealZ;
    float mTileLength;

    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
    std::shared_ptr<Mesh> mTerrainMesh;

    void GenVertices();
    void GenIndices();
    void GenMesh();

public:
    Terrain(float worldBaseX, float worldBaseZ, float lenTerrainSide, int numVerticesAlongTerrainSide);
    std::shared_ptr<Mesh>& GetMesh();
    ~Terrain();

};