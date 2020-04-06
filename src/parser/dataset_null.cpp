#include <iostream>

#include <parser/include/dataset_null.h>

namespace reader {
    DatasetNull::DatasetNull(std::uint16_t id,
                             const std::string &filepath,
                             const std::string &name,
                             const std::string &desc) :
        DatasetAbstract(id, filepath, name, desc, DatasetVersion::NULL_SET)
    {
        std::clog << "Creating null set: id(" << id 
                  << ") path(" << filepath
                  << ") name(" << name
                  << ") desc(" << desc 
                  << "}\n";
    }
}

