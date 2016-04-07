
#include "../../../adt/source/include/Box.hpp"
#include "../include/MapInterface.hpp"

namespace r2d2
{
    BoxInfo::BoxInfo(bool has_obstacle, bool has_unknown, bool has_navigatable) :
        has_obstacle{ has_obstacle },
        has_unknown{ has_unknown },
        has_navigatable{ has_navigatable }
    {}

    bool BoxInfo::operator==(BoxInfo & rhs)
    {
        return has_obstacle == rhs.has_obstacle && has_unknown == rhs.has_unknown && has_navigatable == rhs.has_navigatable;
    }

    bool BoxInfo::operator!=(BoxInfo & rhs)
    {
        return !operator==(rhs);
    }

    bool BoxInfo::get_has_obstacle(){
        return BoxInfo::has_obstacle;
    }
    bool BoxInfo::get_has_unknown(){
        return BoxInfo::has_unknown;
    }
    bool BoxInfo::get_has_navigatable(){
        return BoxInfo::has_navigatable;
    }

}

