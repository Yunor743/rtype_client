#ifndef SNITCH_HPP
#define SNITCH_HPP

#include <iostream>
#include <string>

class Snitch {
public:
    static std::ostream &output;
    static std::string endl;
    static std::ostream &warn(const std::string &msg = "WARNING");
    static std::ostream &msg(const std::string &msg);
};

#endif
