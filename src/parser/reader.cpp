
#include <parser/include/reader.h>
#include <parser/include/dataset_null.h>

namespace reader {
    void Reader::LoadFile(const std::string &filepath,
                          const std::string &name,
                          const std::string &desc)
    {
        //Initial Test version
        auto ptr = new DatasetNull(storage.NextId(), filepath, name, desc);
        storage.Add(ptr);
    }
}

