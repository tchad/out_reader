#ifndef __READER_PARSER_ENGINE_V5_3__
#define __READER_PARSER_ENGINE_V5_3__

#include <fstream>
#include <regex>
#include <string>

#include <parser/include/defs.h>
#include <parser/include/dataset_v5_3.h>

namespace reader {

    class ParserEngineV53 {
        public:
            static constexpr const char* ENGINE_NAME = "ENGINE V5.3 (PTPX)";

            static const std::regex REGEX_VERSION;
            static const std::regex REGEX_COMMENT;
            static const std::regex REGEX_TIME_RESOLUTION;
            static const std::regex REGEX_HIER_SEPARATOR;
            static const std::regex REGEX_INDEX;
            static const std::regex REGEX_VAR_INDEPENDENT;
            static const std::regex REGEX_VAR_INDEXED;

            static ParserStatus Parse(std::ifstream &fs, DatasetV53 *dset);
    };
}

#endif

