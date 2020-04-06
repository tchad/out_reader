#ifndef __READER_STORAGE__
#define __READER_STORAGE__

#include <forward_list>
#include <memory>
#include <vector>

#include <parser/include/dataset_abstract.h>

namespace reader {

    using IdVector = std::vector<std::uint16_t>;
    using IdVectorSharedPtr = std::shared_ptr<IdVector>;
    
    class Storage final {

        public:
            Storage() = default;
            ~Storage() = default;

            std::uint32_t Size() const noexcept;
            bool Contains(std::uint16_t id) const noexcept;

            DatasetAbstractWeakPtr Get(std::uint16_t id) noexcept;
            IdVectorSharedPtr GetIdVector() const noexcept;
            
            void Add(DatasetAbstract *p) noexcept;
            bool Remove(std::uint16_t id) noexcept;

            std::uint16_t NextId() noexcept;

        private:
            std::forward_list<DatasetAbstractSharedPtr> db;
            std::uint16_t id = 0;
            std::uint32_t current_sz = 0;

        //Deleted implicit constructors and assignment operators
        public:
            Storage( const Storage & ) = delete;
            Storage( Storage && ) = delete;

            Storage& operator = ( const Storage &) = delete;
            Storage& operator = ( const Storage &&) = delete;
    };


    inline std::uint16_t Storage::NextId() noexcept
    {
        return ++id;
    }
    
    inline std::uint32_t Storage::Size() const noexcept
    {
        return current_sz;
    }
}

#endif

