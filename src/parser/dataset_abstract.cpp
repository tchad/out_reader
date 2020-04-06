
#include <parser/include/dataset_abstract.h>

namespace reader {
    DatasetAbstract::DatasetAbstract(const std::string &filepath,
                                     const std::string &name,
                                     const std::string &desc,
                                     DatasetVersion version) :
        filepath(filepath),
        name(name),
        desc(desc),
        version(version)
    {}
}

