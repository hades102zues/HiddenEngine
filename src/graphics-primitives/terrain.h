#pragma once
#include "vertex.h"
#include <vector>


class Terrain {
private:
    int mNumVerticesAlongTerrainSide;
    int mNumTileSides;
    float mBaseRealX;
    float mBaseRealZ;
    float mTileLength;
    std::vector<Vertex> mVertices;
    std::vector<int> mIndices;

    void GenVertices();
    void GenIndices();

public:
    Terrain(float worldBaseX, float worldBaseZ, float lenTerrainSide, int numVerticesAlongTerrainSide);
    ~Terrain();

};