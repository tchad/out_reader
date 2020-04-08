#ifndef __READER_DATASET_V5_3__
#define __READER_DATASET_V5_3__

#include <parser/include/dataset_abstract.h>

namespace reader {

    class ParserEngineV53;

    class DatasetV53 : public DatasetAbstract {
        public:
            DatasetV53(const std::string &filepath,
                        const std::string &name,
                        const std::string &desc);

            virtual ~DatasetV53() = default;

        //Deleted implicit constructors and assignment operators
        public:
            DatasetV53( const DatasetV53 &) = delete;
            DatasetV53( DatasetV53 &&) = delete;

            DatasetV53& operator = ( const DatasetV53 &) = delete;
            DatasetV53& operator = ( const DatasetV53 &&) = delete;


        friend class ParserEngineV53;
    };
}


#endif

