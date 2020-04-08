#include <iostream>

#include <parser/include/dataset_v5_3.h>

namespace reader {
    DatasetV53::DatasetV53(const std::string &filepath,
                           const std::string &name,
                           const std::string &desc) :
        DatasetAbstract(filepath, name, desc, DatasetVersion::VER5_3)
    {
        std::clog << "Creating V53 set: path(" << filepath
                  << ") name(" << name
                  << ") desc(" << desc 
                  << "}\n";
    }
}
