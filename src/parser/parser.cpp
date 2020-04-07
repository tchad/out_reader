
#include <fstream>
#include <iostream>
#include <regex>

#include <parser/include/parser.h>
#include <parser/include/dataset_null.h>

namespace reader {

    DatasetAbstract* Parser::Load(ParserStatus &status,
                                  const std::string &filepath,
                                  const std::string &name,
                                  const std::string &desc)
    {
        std::regex format_tmpl(".*![ ]+output_format[ ]+([0-9]+\\.[0-9]+)$", std::regex::extended);

        std::ifstream file;
        file.open(filepath);

        if (file.is_open()) {
            std::string line;
            std::string ver_str;
            std::smatch ver_num_match;
            bool found = false;

            while (!file.eof()) {
                std::getline(file, line);  

                if (std::regex_match(line, ver_num_match, format_tmpl)) {
                    found = true;
                    ver_str = ver_num_match.str(1);
                    break;
                }
            }

            if (found) {
                if (ver_str == "5.3") {
                    file.seekg(0);
                    //Go back to the beginning of the file before passing to the engine
                    status = ParserStatus::SUCCESS;
                    return new DatasetNull(filepath, name, desc);
                }
                else {
                    status = ParserStatus::ERR_UNSUPPORTED_VERSION;
                    return nullptr;
                }
            }
            else {
                status = ParserStatus::ERR_WRONG_FILE_CONTENT;
                return nullptr;
            }
        }
        else {
            status = ParserStatus::ERR_FILE_MISSING;
            return nullptr;
        }
    }
}

