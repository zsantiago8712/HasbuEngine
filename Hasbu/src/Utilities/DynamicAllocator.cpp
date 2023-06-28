#include "Utilities/DynamicAllocator.hpp"
#include "Utilities/Logger.hpp"

namespace Hasbu::Utils {

void DynamicAllocator::initDynamicAllocator(const std::size_t& size)
{
    getDynamicAllocator(size);
}

DynamicAllocator& DynamicAllocator::getDynamicAllocator(const std::size_t& size)
{
    HASBU_ASSERT(size < 0 && size > TO_GYGABYTES(4), "size must be greater than 0")
    static DynamicAllocator allocator(size);
    return allocator;
}

DynamicAllocator::DynamicAllocator(const std::size_t& size)
    : size(size)
    , offset_allocator(size)
{
    HASBU_ASSERT(this->size < 0 && this->size > TO_GYGABYTES(4), "size must be greater than 0, and less than 4 GigaBytes")
    this->block = ::operator new(size);

    if (this->block == nullptr) {
        HASBU_FATAL("Could allocate {} memory spcae", size);
        return;
    }

    this->freeStorage = size;
    HASBU_INFO("ALLOCATE SPACE FOR {} BYTES THE APPLICATION", size);
}

void* DynamicAllocator::_allocate(const std::size_t& size)
{
    HASBU_ASSERT(size < 0 && size > getDynamicAllocator().freeStorage, "Size must be grater than 0 and less than free storage")

    OffsetAllocator::Allocation allocation = getDynamicAllocator().offset_allocator.allocate(size);

    const auto find_it = std::ranges::find_if(getDynamicAllocator().allocations.begin(), getDynamicAllocator().allocations.end(), [allocation](OffsetAllocator::Allocation& s) {
        if (s.offset == allocation.offset) {
            s.offset = allocation.offset;
            s.metadata = allocation.metadata;
            return true;
        }

        return false;
    });

    if (find_it == getDynamicAllocator().allocations.end()) {
        getDynamicAllocator().allocations.push_back(allocation);
    }

    getDynamicAllocator().freeStorage -= size;

    return static_cast<char*>(getDynamicAllocator().block) + allocation.offset;
}

bool DynamicAllocator::_deallocate(void* ptr, const std::size_t& size)
{
    HASBU_ASSERT(ptr == nullptr, "Ptr must not be nullptr")
    const std::size_t offset_to_search = static_cast<char*>(ptr) - static_cast<char*>(getDynamicAllocator().block);

    const auto find_it = std::ranges::find_if(getDynamicAllocator().allocations.begin(), getDynamicAllocator().allocations.end(), [offset_to_search](OffsetAllocator::Allocation& s) {
        if (s.offset == offset_to_search) {
            return true;
        }
        return false;
    });

    if (find_it != getDynamicAllocator().allocations.end()) {
        getDynamicAllocator().offset_allocator.free(*find_it);
        getDynamicAllocator().allocations.erase(find_it);
        getDynamicAllocator().freeStorage += size;

        HASBU_INFO("Dealocated Allocation [{}] You still have #{} Allocations", ptr, getDynamicAllocator().allocations.size());

        return true;
    } else {
        HASBU_ERROR("Could find allocation [{}]", ptr);
        return false;
    }
}

DynamicAllocator::~DynamicAllocator()
{
    for (const auto& allocation : allocations) {
        offset_allocator.free(allocation);
    }

    ::operator delete(this->block);
    this->freeStorage = 0;
    this->size = 0;
    HASBU_INFO("DYNAMIC ALLCATOR DESTOYED");
}

void DynamicAllocator::getReport()
{
    HASBU_DEBUG("REPORT: TOTAL SIZE ALLOCATED [{} BYTES], TOTAL STORAGE FREE [{}] BYTES, TOTAL ALLOCATIONS [{}]", getDynamicAllocator().size, getDynamicAllocator().freeStorage, getDynamicAllocator().allocations.size());
}

}
