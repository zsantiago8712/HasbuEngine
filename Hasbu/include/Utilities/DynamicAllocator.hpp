#pragma once
#include "defines.hpp"
#include "offsetAllocator.hpp"

#define TO_GYGABYTES(amount) ((amount)*1024ULL * 1024ULL * 1024ULL)
#define TO_MEGABYTES(amount) ((amount)*1024ULL * 1024ULL)
#define TO_KILOBYTES(amount) ((amount)*1024ULL)

namespace HasbuUtils {

class DynamicAllocator {

public:
    DynamicAllocator& operator=(const DynamicAllocator&) = delete;
    DynamicAllocator(DynamicAllocator&&) = delete;
    DynamicAllocator& operator=(DynamicAllocator&&) = delete;

    static void initDynamicAllocator(const std::size_t& size);
    static void getReport(void);

    template <class Type>
    HASBU_CONSTEXPR static Type* allocate(const std::size_t& size = 1)
    {
        return static_cast<Type*>(DynamicAllocator::_allocate(sizeof(Type) * size));
    }

    template <class T>
    HASBU_CONSTEXPR static void deallocate(T* ptr, const std::size_t& size = 1)
    {
        if (DynamicAllocator::_deallocate(ptr, sizeof(T) * size)) {
            ptr = nullptr;
        }
    }

private:
    explicit DynamicAllocator(const std::size_t& size);
    ~DynamicAllocator();

    static DynamicAllocator& getDynamicAllocator(const std::size_t& size = 1);

    static void* _allocate(const std::size_t& size);
    static bool _deallocate(void* ptr, const std::size_t& size);

    void* block = nullptr;
    std::size_t size = 0;
    std::size_t free_storage = 0;
    std::list<OffsetAllocator::Allocation> allocations;
    OffsetAllocator::Allocator offset_allocator;
};

// Allocator Addapter especilized for containers
template <class Type>
struct AllocatorAdapter {

    using value_type = Type;
    using pointer = Type*;
    using const_pointer = const Type*;
    using size = std::size_t;

    AllocatorAdapter() noexcept = default;
    AllocatorAdapter(const AllocatorAdapter&) = default;

    template <typename U>
    explicit AllocatorAdapter(const AllocatorAdapter<U>&) noexcept { }

    HASBU_CONSTEXPR pointer allocate(const size& _size)
    {
        return HasbuUtils::DynamicAllocator::allocate<Type>(_size);
    }

    HASBU_CONSTEXPR void deallocate(pointer _pointer, const size& _size) const
    {
        HasbuUtils::DynamicAllocator::deallocate(_pointer, _size);
    }
};

// Allocator Addapter especilized for maps
template <class Type>
struct AllocatorAdapterMaps {

    using value_type = Type;
    using pointer = Type*;
    using const_pointer = const Type*;
    using size = std::size_t;

    AllocatorAdapterMaps() noexcept = default;
    AllocatorAdapterMaps(const AllocatorAdapterMaps&) = default;

    template <typename U>
    explicit AllocatorAdapterMaps(const AllocatorAdapterMaps<U>&) noexcept { }

    HASBU_CONSTEXPR pointer allocate(const size& _size)
    {
        return static_cast<pointer>(HasbuUtils::DynamicAllocator::allocate<Type>(_size));
    }

    HASBU_CONSTEXPR void deallocate(pointer _pointer, const size& _size) const
    {
        HasbuUtils::DynamicAllocator::deallocate(_pointer, _size);
    }
};

template <class Type>
using Shared = std::shared_ptr<Type>;

template <class Type, class... Args>
HASBU_CONSTEXPR Shared<Type> createShared(Args&... args)
{
    return Shared<Type>(new (DynamicAllocator::allocate<Type>()) Type(std::forward<Args>(args)...), [](Type* ptr) {
        DynamicAllocator::deallocate(ptr);
        ptr->~Type();
    });
}

template <class Type>
using Unique = std::unique_ptr<Type, void (*)(Type*)>;

template <class Type, class... Args>
HASBU_CONSTEXPR Unique<Type> createUnique(Args&... args)
{
    return Unique<Type>(new (DynamicAllocator::allocate<Type>()) Type(std::forward<Args>(args)...), [](Type* ptr) {
        DynamicAllocator::deallocate(ptr);
        ptr->~Type();
    });
}

template <class Type>
using Vector = std::vector<Type, HasbuUtils::AllocatorAdapter<Type>>;

template <class Type, class TypeCompare = std::less<Type>>
using set = std::set<Type, std::less<Type>, HasbuUtils::AllocatorAdapter<Type>>;

template <class TypeKey, class TypeValue>
using AllocatorAdapterMap = HasbuUtils::AllocatorAdapterMaps<std::pair<const TypeKey, TypeValue>>;

template <class TypeKey, class TypeValue, class TypeCompare = std::less<TypeKey>>
using multimap = std::map<TypeKey, TypeValue, TypeCompare, HasbuUtils::AllocatorAdapterMap<TypeKey, TypeValue>>;

}
