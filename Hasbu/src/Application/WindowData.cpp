#include "Application/WindowData.hpp"

namespace Hasbu {

WindowData::~WindowData()
{
    this->context.reset();
}

}
