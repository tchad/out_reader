#include <iostream>

#include <parser/include/dataset_v5_3.h>

namespace reader {
    bool DatasetV53::Record::operator < (const Record &r) const 
    {
        return (t < r.t);
    }

    DatasetV53::DatasetV53(const std::string &filepath,
                           const std::string &name,
                           const std::string &desc) :
        DatasetAbstract(filepath, name, desc, DatasetVersion::VER5_3)
    {
        std::clog << "Creating V53 set: path(" << filepath
                  << ") name(" << name
                  << ") desc(" << desc 
                  << "}\n";
    }

    bool DatasetV53::ContainsRecordAtTime(std::uint32_t t) const noexcept
    {
        for(const auto& r : data) {
            if(r.t == t) {
                return true;
            }
        }

        return false;
    }

    DatasetAbstract::SimpleDPoint1DListSharedPtr DatasetV53::SimplePowerData()
    {
        auto lst = new DatasetAbstract::SimpleDPoint1DList;

        for (auto re = data.rbegin(); re != data.rend(); re++) {
            DatasetAbstract::SimpleDPoint1D p{re->t, re->d[DatasetV53::PWR_IDX]};
            lst->push_front(p);
        }

        return DatasetAbstract::SimpleDPoint1DListSharedPtr(lst);
    }
 
    std::string DatasetV53::DataAnalysisReport()
    {
        return "SUP";
    }
}

