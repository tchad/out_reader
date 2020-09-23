
#include <parser/include/storage.h>

namespace reader {

    bool Storage::Contains(std::uint16_t id) const noexcept
    {
        for (auto i : db) {
            if (i->Id() == id) {
                return true;
            }
        }

        return false;
    }

    DatasetAbstractWeakPtr Storage::Get(std::uint16_t id) noexcept
    {
        //Returns empty if does not exist
        for (auto i : db) {
            if (i->Id() == id) {
                return DatasetAbstractWeakPtr(i);
            }
        }

        return DatasetAbstractWeakPtr();
    }

    IdVectorSharedPtr Storage::GetIdVector() const noexcept
    {
        auto v = new IdVector();
        v->reserve(current_sz);

        for (DatasetAbstractSharedPtr p : db) {
            v->push_back(p->Id());
        }

        return IdVectorSharedPtr(v);
    }

    void Storage::Add(DatasetAbstract *p) noexcept
    {
        //Silent on duplicates
        if (!Contains(p->Id())) {
            p->id = NextId();
            db.push_front(DatasetAbstractSharedPtr(p));

            current_sz++;
        }
    }

    bool Storage::Remove(std::uint16_t id) noexcept
    {
        bool ret = false;

        if (db.empty()) {
            ret = false;
        } else if ((*db.cbegin())->Id() == id) {
            db.pop_front();
            ret =  true;
        } else {
            ret = false;

            auto next = db.cbegin();
            auto current = next++;

            while ( next != db.cend()) {
                if ((*next)->Id() == id) {
                    db.erase_after(current);
                    ret = true;
                    break;

                } else {
                    current = next++;
                }
            }
        }

        if(ret) {
            current_sz--;
        }

        return ret;
    }
}

