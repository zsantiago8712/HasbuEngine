#pragma once
#include "Components/RenderComponents.hpp"
#include "Renderer/Vertex.hpp"
#include "Utilities/DynamicAllocator.hpp"

namespace Hasbu::Render {

unsigned int createStaticMesh();
unsigned int createDynamicMesh();

unsigned int createSubMeshs(const unsigned int meshID, const Utils::Vector<Vertex>& vertices, const Utils::Vector<unsigned int>& indices, const Utils::Vector<unsigned int>& textures);

void updateStaticMesh(const unsigned int meshID);
void updateDynamicMesh(const unsigned int meshID);

void drawMesh(const unsigned int meshID, const unsigned int shaderID);

struct MeshManager {

    static unsigned int createDynamicMesh(Components::RenderComponents& components);
    static unsigned int createDynamicMesh(Components::RenderComponents& components, const std::span<Vertex> vertices, const std::span<unsigned int> indices);

    static unsigned int createStaticMesh(Components::RenderComponents& components);
    static unsigned int createStaticMesh(Components::RenderComponents& components, const std::span<Vertex> vertices, const std::span<unsigned int> indices);
    static unsigned int nextMeshID;
};

};
