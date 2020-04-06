
#include <parser/include/parser.h>
#include <parser/include/dataset_null.h>

namespace reader {

    DatasetAbstract* Parser::Load(ParserStatus &status,
                                  const std::string &filepath,
                                  const std::string &name,
                                  const std::string &desc)
    {
        //Initial Test version
        status = ParserStatus::SUCCESS;
        return new DatasetNull(filepath, name, desc);
    }
}

