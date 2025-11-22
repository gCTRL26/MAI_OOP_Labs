#include "memory_resource.hpp"
#include <algorithm>
#include <new>

namespace memory_resource {
MemoryResource::MemoryResource(size_t sz, std::pmr::memory_resource* alloc) 
    : block_size_(sz), alloc_(alloc) {}

MemoryResource::~MemoryResource() {
    for (const auto& block : blocks_) {
        alloc_->deallocate(block.ptr_, block_size_, block.allignment_);
    }
}

void* MemoryResource::do_allocate(size_t sz, size_t allignment) {
    if (sz > block_size_) {
        throw std::bad_alloc();
    }

    if (!empty_bloks_.empty()) {
        void* ptr = empty_bloks_.back();
        empty_bloks_.pop_back();
        return ptr;
    }

    void* new_block = alloc_->allocate(sz, allignment);
    blocks_.push_back({new_block, block_size_, allignment});
    return new_block;
}

void MemoryResource::do_deallocate(void* ptr, size_t bytes, size_t alignment) {
    auto it = std::find(blocks_.begin(), blocks_.end(), ptr);
    if (it != blocks_.end()) {
        empty_bloks_.push_back(ptr);
    }
}

bool MemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}
}