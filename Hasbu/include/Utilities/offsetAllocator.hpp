// (C) Sebastian Aaltonen 2023
// MIT License (see file: LICENSE)

// #define USE_16_BIT_OFFSETS

namespace OffsetAllocator {

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;

// 16 bit offsets mode will halve the metadata storage cost
// But it only supports up to 65536 maximum allocation count
#ifdef USE_16_BIT_NODE_INDICES
typedef uint16 NodeIndex;
#else
typedef uint32 NodeIndex;
#endif

static constexpr uint32 NUM_TOP_BINS = 32;
static constexpr uint32 BINS_PER_LEAF = 8;
static constexpr uint32 TOP_BINS_INDEX_SHIFT = 3;
static constexpr uint32 LEAF_BINS_INDEX_MASK = 0x7;
static constexpr uint32 NUM_LEAF_BINS = NUM_TOP_BINS * BINS_PER_LEAF;
static constexpr uint32 MAX_ALLOCS = 65536;

struct Allocation {
    static constexpr uint32 NO_SPACE = 0xffffffff;

    uint32 offset = NO_SPACE;
    NodeIndex metadata = NO_SPACE; // internal: node index
};

struct StorageReport {
    uint32 totalFreeSpace;
    uint32 largestFreeRegion;
};

struct StorageReportFull {
    struct Region {
        uint32 size;
        uint32 count;
    };

    Region freeRegions[NUM_LEAF_BINS];
};

class Allocator {
public:
    Allocator(uint32 size, uint32 maxAllocs = 128 * 1024);
    Allocator(Allocator&& other);
    ~Allocator();
    void reset();

    Allocation allocate(uint32 size);
    void free(Allocation allocation);

    uint32 allocationSize(Allocation allocation) const;
    StorageReport storageReport() const;
    StorageReportFull storageReportFull() const;

    NodeIndex* m_freeNodes;

private:
    uint32 insertNodeIntoBin(uint32 size, uint32 dataOffset);
    void removeNodeFromBin(uint32 nodeIndex);

    struct Node {
        bool used = false; // TODO: Merge as bit flag
        static constexpr NodeIndex unused = 0xffffffff;

        uint32 dataOffset = 0;
        uint32 dataSize = 0;
        NodeIndex binListPrev = unused;
        NodeIndex binListNext = unused;
        NodeIndex neighborPrev = unused;
        NodeIndex neighborNext = unused;
    };

    uint32 m_size;
    uint32 m_maxAllocs;
    uint32 m_freeStorage;

    uint32 m_usedBinsTop;

    Node* m_nodes;
    uint32 m_freeOffset;
    uint8 m_usedBins[NUM_TOP_BINS];
    NodeIndex m_binIndices[NUM_LEAF_BINS];
};
}
