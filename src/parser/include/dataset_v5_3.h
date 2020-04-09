#ifndef __READER_DATASET_V5_3__
#define __READER_DATASET_V5_3__

#include <cstdint>
#include <string>
#include <map>
#include <list>

#include <parser/include/dataset_abstract.h>

/*
 * Default units:
 * Time: ps
 * Power: Watt
 * Power index 1
 */

namespace reader {
    class ParserEngineV53;

    class DatasetV53 : public DatasetAbstract {
        public:
            using IdxId = std::uint32_t;

            struct Index {
                IdxId idx;
                std::string name;
                std::string units;
            };

            struct Record {
                std::uint32_t t;
                std::map<IdxId, double> d;

                bool operator < ( const Record &r) const;
            };

            static constexpr IdxId PWR_IDX = 1;

            DatasetV53(const std::string &filepath,
                       const std::string &name,
                       const std::string &desc);

            virtual ~DatasetV53() = default;

            bool ContainsRecordAtTime(std::uint32_t t) const noexcept;

        protected:
            std::string hier_separation;
            std::string time_resolution;
            std::list<Record> data;
            std::map<IdxId, Index> index_map;


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

