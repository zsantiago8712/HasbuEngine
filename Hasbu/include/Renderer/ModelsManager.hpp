#pragma once

#include <string_view>
#include "Components/MaterailComponents.hpp"

namespace Hasbu::Render {

unsigned int createModelEntity(const std::string_view& vsShaderFile, const std::string_view& fsShaderFile);
unsigned int createModelEntity();

void loadDynamicModelFromFile(const unsigned int modelID, const std::string_view& modelFile);
void loadStaticModelFromFile(const unsigned int modelID, const std::string_view& modelFile);
const Components::MaterialComponents& getModelMaterialComponents(const unsigned int modelID);

}
