
#include <parser/include/reader.h>
#include <parser/include/parser.h>

namespace reader {
    ParserStatus Reader::LoadFile(const std::string &filepath,
                                  const std::string &name,
                                  const std::string &desc)
    {
        ParserStatus status;
        DatasetAbstract *ptr;

        ptr = Parser::Load(status, filepath, name, desc);

        if(status == ParserStatus::SUCCESS) {
            storage.Add(ptr);
        }

        return status;
    }
}

