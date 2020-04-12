#include <iostream>
#include <sstream>
#include <limits>


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
        std::ostringstream os;
        os << "---Data Ananlysis Report---" << std::endl;
        os << "Id: " << Id() << std::endl;
        os << "Name: " << Name() << std::endl;
        os << "File: " << Filepath() << std::endl;
        os << "Desc: " << Desc() << std::endl;

        //Timespan
        os << "Timespan: " << data.begin()->t*1.0e-12 << "s : " 
            << data.rbegin()->t*1.0e-12 << "s" << std::endl;

        //Min Max PWR
        double min = std::numeric_limits<double>::max();
        double max = std::numeric_limits<double>::min();

        for (auto& r : data) {
            double tmp = r.d[PWR_IDX];
            if (tmp > max) {
                max = tmp;
            }

            if (tmp < min) {
                min = tmp;
            }
        }

        os << "Min PWR inst value: " << std::scientific << min << " [W]" << std::endl;
        os << "Peak PWR int value: " << std::scientific << max << " [W]" << std::endl;

        double sum = 0;

        //integral over the list
        if (data.size() <= 2) {
            //impractical case cannot compute range
            sum = 0;
        }
        else {
            //Note:
            //std::list<Record>::iterator next = data.begin();
            //std::list<Record>::iterator current = next;

            auto next = data.begin();
            auto current = next;
            next++;

            while (next != data.end()) {
                std::uint32_t tb = current->t;
                std::uint32_t te = next->t;
                double val = current->d[PWR_IDX];


                sum += val*((te-tb)*1.0e-12);

                current = next;
                next++;
            }
        }

        os << "Energy consumed per task: " << sum << " [J]" << std::endl;

        //avg PWR
        double avg_pwr = sum / ((data.rbegin()->t - data.begin()->t)*1.0e-12);

        os << "Average power: " << avg_pwr << " [W]" << std::endl;

        return os.str();

    }
}

