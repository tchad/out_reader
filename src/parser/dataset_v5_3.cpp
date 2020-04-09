#include <iostream>

#include <parser/include/dataset_v5_3.h>

namespace reader {
    bool DatasetV53::Record::operator < (const Record &r) const 
    {
        return (t < r.t);
    }

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

    bool DatasetV53::ContainsRecordAtTime(std::uint32_t t) const noexcept
    {
        for(const auto& r : data) {
            if(r.t == t) {
                return true;
            }
        }

        return false;
    }
}

