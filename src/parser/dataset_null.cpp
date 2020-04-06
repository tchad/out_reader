#include <iostream>

#include <parser/include/dataset_null.h>

namespace reader {
    DatasetNull::DatasetNull(const std::string &filepath,
                             const std::string &name,
                             const std::string &desc) :
        DatasetAbstract(filepath, name, desc, DatasetVersion::NULL_SET)
    {
        std::clog << "Creating null set: path(" << filepath
                  << ") name(" << name
                  << ") desc(" << desc 
                  << "}\n";
    }
}

