
#include <parser/include/parser_engine_v5_3.h>
#include <iostream>

namespace reader {
    ParserStatus ParserEngineV53::Parse(std::ifstream &fs, DatasetV53 *dset)
    {

        std::string line;
        std::string tmp;
        std::smatch match;

        std::clog << ENGINE_NAME << std::endl;

        while (!fs.eof()) {
            std::getline(fs, line);  

            if (std::regex_match(line, match, REGEX_VERSION)) {
                std::clog << "\tfound version: " << match.str(1) << std::endl;

            }
            else if (std::regex_match(line, match, REGEX_COMMENT)) {
                std::clog << "\tfound comment " << std::endl;
            }
            else if (std::regex_match(line, match, REGEX_TIME_RESOLUTION)) {
                std::clog << "\tfound time_resolution: " << match.str(1) << std::endl;
            }
            else if (std::regex_match(line, match, REGEX_HIER_SEPARATOR)) {
                std::clog << "\tfound hier_separator: " << match.str(1) << std::endl;
            }
            else if (std::regex_match(line, match, REGEX_INDEX)) {
                std::clog << "\tfound index: " 
                    << " Name: " << match.str(1)
                    << " Idx ID: " << match.str(2)
                    << " Unit: " << match.str(3) << std::endl;
            }
            else if (std::regex_match(line, match, REGEX_VAR_INDEPENDENT)) {
                static bool once = false;
                if(!once) {
                    std::clog << "\tfound var independent: " << match.str(1) << std::endl;
                    once = true;
                }
            }
            else if (std::regex_match(line, match, REGEX_VAR_INDEXED)) {
                static int cnt = 0;
                if(cnt < 5 ) {
                    std::clog << "\tfound var indexed: " 
                        << " Idx: " << match.str(1)
                        << " Val: " << match.str(2) << std::endl;
                    cnt++;
                }
            }
        }

        return ParserStatus::SUCCESS;
    }

    const std::regex ParserEngineV53::REGEX_VERSION = std::regex(
            ".*![ ]+output_format[ ]+([0-9]+\\.{0,1}[0-9]+)$",
            std::regex::extended);

    const std::regex ParserEngineV53::REGEX_COMMENT = std::regex(
            "^;.*",
            std::regex::extended);

    const std::regex ParserEngineV53::REGEX_TIME_RESOLUTION = std::regex(
            "^\\.time_resolution[ ]+([0-9]+\\.{0,1}[0-9]+)$",
            std::regex::extended);

    const std::regex ParserEngineV53::REGEX_HIER_SEPARATOR = std::regex(
            "^\\.hier_separator[ ]+(.+)",
            std::regex::extended);

    const std::regex ParserEngineV53::REGEX_INDEX = std::regex(
            "^\\.index[ ]+(.+)[ ]+([0-9]+)[ ]+(.+)",
            std::regex::extended);

    const std::regex ParserEngineV53::REGEX_VAR_INDEPENDENT = std::regex(
            "^([0-9]+)",
            std::regex::extended);

    //Might need stronger
    const std::regex ParserEngineV53::REGEX_VAR_INDEXED = std::regex(
            //"^([0-9]+)[ ]+(.+)",
            //Second element captures scientific notation
            "^([0-9]+)[ ]+(-{0,1}[0-9]+\\.{0,1}[0-9]*e{0,1}-{0,1}[0-9]*)",
            //"^([0-9]+)[ ]+([0-9\\.\\-e]+)",
            std::regex::extended);

}

