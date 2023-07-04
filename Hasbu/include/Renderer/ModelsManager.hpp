#pragma once

#include <string_view>


namespace Hasbu::Render {


void drawModel(const unsigned int modelID, const unsigned int shaderID);
unsigned int loadModel(const std::string_view& fileModel);

}
