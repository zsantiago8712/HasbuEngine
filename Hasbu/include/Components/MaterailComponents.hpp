#pragma once
#include "Utilities/DynamicAllocator.hpp"

namespace Hasbu::Components {

struct MaterialComponents {

    Utils::Vector<unsigned int> textures;
    unsigned int shaderID;   
    
    std::string_view vsShader;
    std::string_view fsShader;

};

}
