#ifndef __READER_READER__
#define __READER_READER__

#include <string>

#include <parser/include/defs.h>
#include <parser/include/dataset_abstract.h>
#include <parser/include/storage.h>

namespace reader {

    class Reader {

        public:
            Reader() = default;
            ~Reader() = default;

            void LoadFile(const std::string &filepath,
                          const std::string &name,
                          const std::string &desc);

            Storage& GetStorage() noexcept;
        private:
            Storage storage;

        //Deleted implicit constructors and assignment operators
        public:
            Reader(const Reader &) = delete;
            Reader(Reader &&) = delete;

            Reader& operator = (const Reader &) = delete;
            Reader& operator = (const Reader &&) = delete;
    };

    inline Storage& Reader::GetStorage() noexcept 
    {
        return storage;
    }
}

#endif

