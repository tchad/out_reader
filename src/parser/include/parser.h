#ifndef __READER_PARSER__
#define __READER_PARSER__

#include <string>

#include <parser/include/defs.h>
#include <parser/include/dataset_abstract.h>

namespace reader {

    class Parser {
        public:
            static DatasetAbstract* Load(ParserStatus &status,
                                         const std::string &filepath,
                                         const std::string &name,
                                         const std::string &desc);

    };
}

#endif

