
#ifndef __READER_DATASET_NULL__
#define __READER_DATASET_NULL__

#include <parser/include/dataset_abstract.h>
#include <iostream>

namespace reader {

    class DatasetNull : public DatasetAbstract {

        public:
            DatasetNull(const std::string &filepath,
                        const std::string &name,
                        const std::string &desc);

            virtual ~DatasetNull() = default;

        virtual DatasetAbstract::SimpleDPoint1DListSharedPtr SimplePowerData() override;
        virtual std::string DataAnalysisReport() override;

        //Deleted implicit constructors and assignment operators
        public:
            DatasetNull( const DatasetNull &) = delete;
            DatasetNull( DatasetNull &&) = delete;

            DatasetNull& operator = ( const DatasetNull &) = delete;
            DatasetNull& operator = ( const DatasetNull &&) = delete;
    };
}

#endif

