#ifndef __READER_DATASET_ABSTRACT__
#define __READER_DATASET_ABSTRACT__

#include <string>
#include <cstdint>
#include <memory>

#include <parser/include/defs.h>

namespace reader {

    class DatasetAbstract {

        public:

            virtual ~DatasetAbstract() = default;

            std::uint16_t Id() const noexcept;
            const std::string& Filepath() const noexcept;
            const std::string& Name() const noexcept;
            const std::string& Desc() const noexcept;
            DatasetVersion Version() const noexcept;

        protected:
            DatasetAbstract(std::uint16_t id,
                            const std::string &filepath,
                            const std::string &name,
                            const std::string &desc,
                            DatasetVersion version);
            
            
            //Members
            std::uint16_t id;
            std::string filepath;
            std::string name;
            std::string desc;
            DatasetVersion version;


        //Deleted implicit constructors and assignment operators
        public:
            DatasetAbstract( const DatasetAbstract &) = delete;
            DatasetAbstract( DatasetAbstract &&) = delete;

            DatasetAbstract& operator = ( const DatasetAbstract &) = delete;
            DatasetAbstract& operator = ( const DatasetAbstract &&) = delete;
    };


    using DatasetAbstractSharedPtr = std::shared_ptr<DatasetAbstract>;
    using DatasetAbstractWeakPtr = std::weak_ptr<DatasetAbstract>;


    //Inline defs
    inline std::uint16_t DatasetAbstract::Id() const noexcept
    {
        return id;
    }

    inline const std::string& DatasetAbstract::Filepath() const noexcept
    {
        return filepath;
    }

    inline const std::string& DatasetAbstract::Name() const noexcept
    {
        return name;
    }

    inline const std::string& DatasetAbstract::Desc() const noexcept
    {
        return desc;
    }

    inline DatasetVersion DatasetAbstract::Version() const noexcept
    {
        return version;
    }
}

#endif
