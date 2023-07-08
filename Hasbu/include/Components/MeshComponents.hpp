#pragma once

#include "DynamicAllocator.hpp"
#include "Vertex.hpp"

namespace Hasbu::Components {

struct MeshComponents {
    unsigned int meshID;
    unsigned int totalIndexCount = 0;
    unsigned int totalVertexCount = 0;

    Utils::Vector<unsigned int> subMeshIds;
    Utils::Vector<unsigned int> indexCountBySubMesh;
    Utils::Vector<Utils::Vector<Render::Vertex>> vertices;
};

}