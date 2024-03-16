#include "terrain.h"
#include "../engine-core/logger/logger.h"

#include <cmath>
#include <cstdlib>


Terrain::Terrain(float worldBaseX, float worldBaseZ, float lenTerrainSide, int numVerticesAlongTerrainSide) {
    mBaseRealX = worldBaseX * lenTerrainSide;
    mBaseRealZ = worldBaseZ * lenTerrainSide;
    mNumVerticesAlongTerrainSide = numVerticesAlongTerrainSide;
    mNumTileSides = numVerticesAlongTerrainSide - 1;
    mTileLength = lenTerrainSide / mNumTileSides; 

    if (mBaseRealZ > 0)
        HIDDEN_WARN("z-coordinates are being referenced in the positive direction.");

    if (mTileLength / floor(mTileLength) != 1)
        HIDDEN_WARN("Terrain Tile Lengths are not uniform and will be sheared");

    GenVertices();
    GenIndices();
    GenMesh();

}

void Terrain::GenVertices() {
 

    for (int iz = 0 ; iz < mNumVerticesAlongTerrainSide; iz++) {

        for (int ix = 0 ; ix < mNumVerticesAlongTerrainSide; ix++ ) {
            float xPosition = mBaseRealX + (ix * mTileLength);
            float zPosition = mBaseRealZ - (iz * mTileLength);
            float yPosition = static_cast<float>(1+(std::rand() % 100));

            Vertex vertex;
            vertex.Position = glm::vec3(xPosition, yPosition, zPosition);
            vertex.Normals = glm::vec3(0.0f, 0.0f, 0.0f);
            vertex.TextCoords = glm::vec2(0.0f, 0.0f);


            // float xPosition = mBaseRealX + (ix * mTileLength);
            // float zPosition = mBaseRealZ + (iz * mTileLength);
          
            // Vertex vertex;
            // vertex.Position = glm::vec3(xPosition, zPosition, 0.0f);
            // vertex.Normals = glm::vec3(0.0f, 0.0f, 0.0f);
            // vertex.TextCoords = glm::vec2(0.0f, 0.0f);

            mVertices.push_back(vertex);


        }
    }

    HIDDEN_INFO("Created {} new vertices.", std::to_string(mVertices.size()));
}

void Terrain::GenIndices() {

    int totalNumberOfVertices = mNumVerticesAlongTerrainSide * mNumVerticesAlongTerrainSide;

    
    int indexBase = 0;
    std::vector<unsigned int> ind;


    for (int i = 0; i < totalNumberOfVertices; i++) {

        // Not all vertex should be wound into a triangle. 
        // Vertices on the far-right of an edge || Vertcies with no row above
        if ( (indexBase + 1 ) % mNumVerticesAlongTerrainSide == 0 || indexBase + mNumVerticesAlongTerrainSide >= (totalNumberOfVertices)) {
            indexBase++;
            continue;
        }


        // Anti-Clockwise Wounding

        ind.push_back(indexBase);
        ind.push_back(indexBase + mNumVerticesAlongTerrainSide + 1);
        ind.push_back(indexBase + mNumVerticesAlongTerrainSide);

        ind.push_back(indexBase);
        ind.push_back(indexBase + 1);
        ind.push_back(indexBase + mNumVerticesAlongTerrainSide + 1);

        indexBase++;
    }

    // std::string list = "";
    // for (auto i : ind ){
    //     list = list +","+ std::to_string(i);
    // }

    
    // HIDDEN_INFO("Index Base {}. Total Number of indices {}", std::to_string(indexBase), std::to_string(ind.size()));
    // HIDDEN_INFO("Items in indices array: {}", list);

    mIndices = ind;
}

void Terrain::GenMesh() {
    mTerrainMesh = std::make_shared<Mesh>(mVertices, mIndices, GlDraw::MESH_INDEX_DRAW);
}

std::shared_ptr<Mesh>& Terrain::GetMesh() {
    return mTerrainMesh;
}

Terrain::~Terrain() {

}