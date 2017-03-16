#pragma once
#include <string>
#include <stdexcept>

namespace ee
{

class MissingComponentException:
    public std::logic_error
{
    public:
        MissingComponentException():
            std::logic_error("Engine component is missing.")
        {
        }

        MissingComponentException(const std::string& description):
            std::logic_error{description}
        {
        }
};

}
