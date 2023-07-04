#pragma once
#include "Renderer/Vertex.hpp"
#include "Utilities/DynamicAllocator.hpp"

namespace Hasbu::Render {

unsigned int createMesh(Utils::Vector<Vertex>& vertives, Utils::Vector<unsigned int>& indices, Utils::Vector<unsigned int>& textures);
void drawMesh(const unsigned int meshID, const unsigned int shaderID);

};
