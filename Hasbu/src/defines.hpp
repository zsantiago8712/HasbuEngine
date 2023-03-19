#pragma once

#include <memory>
#include <utility>

#define HB_API __attribute__((visibility("default")))
#define HASBU_CONSTEXPR constexpr

namespace Hasbu {

template <class T>
using Unique = std::unique_ptr<T>;

template <class T, class... Args>
HASBU_CONSTEXPR Unique<T> createUnique(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <class T>
using Shared = std::shared_ptr<T>;

template <class T, class... Args>
HASBU_CONSTEXPR Shared<T> createShared(Args&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

}