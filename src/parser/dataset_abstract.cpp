
#include <parser/include/dataset_abstract.h>

namespace reader {
    DatasetAbstract::DatasetAbstract(std::uint16_t id,
                                     const std::string &filepath,
                                     const std::string &name,
                                     const std::string &desc,
                                     DatasetVersion version) :
        id(id),
        filepath(filepath),
        name(name),
        desc(desc),
        version(version)
    {}
}

