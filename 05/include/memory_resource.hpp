#pragma once

#include <cstddef>
#include <memory_resource>
#include <vector>

namespace memory_resource {
class MemoryResource : public std::pmr::memory_resource {
  private:
    struct BlockInfo {
        void* ptr_;
        size_t sz_;
        size_t allignment_;
        bool operator==(const void* other) {
            return ptr_ == other;
        }
    };
    std::vector<BlockInfo> blocks_;
    std::vector<void*> empty_bloks_;
    size_t block_size_;
    std::pmr::memory_resource* alloc_;
  public:
    MemoryResource(size_t block_sz, std::pmr::memory_resource* alloc = std::pmr::get_default_resource());
    ~MemoryResource();
    MemoryResource(const MemoryResource&) = delete;
    MemoryResource(MemoryResource&&) = delete;
    MemoryResource& operator=(const MemoryResource&) = delete;
    MemoryResource& operator=(MemoryResource&&) = delete;
  protected:
    void* do_allocate(size_t sz, size_t allignment) override;
    void do_deallocate(void* ptr, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};
}