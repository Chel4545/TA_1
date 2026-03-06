#ifndef LAB1_IPARS_H
#define LAB1_IPARS_H

#include <string>
#include <string_view>

class IPars {
public:
    virtual ~IPars() = default;
    virtual bool pars(std::string_view line) = 0;
};

#endif
