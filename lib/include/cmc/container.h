#ifndef CMC_CONTAINER_H
#define CMC_CONTAINER_H

#include <string>
#include <list>
#include <tuple>
#include <vector>

namespace cmc {

    struct Enum {

    	Enum(const std::string& name_ = std::string()) : name(name_) {}

        typedef std::tuple<std::string, int> Value;
        std::vector<Value> values;
        std::string name;

        bool operator==(const Enum& other) const {
            return name == other.name and values == other.values;
        }
    };

	bool operator<(const Enum::Value& lhs, const Enum::Value& rhs) {
		return std::get<1>(lhs) < std::get<1>(rhs);
    }
}


#endif