//
// Created by Gavin on 2/8/2022.
//

#ifndef CS236PROJECT1_PARAMETER_H
#define CS236PROJECT1_PARAMETER_H
#include <iostream>
#include <string>
#include <sstream>

class Parameter {
    //parameter	->	STRING | ID
public:
    string data;
    bool isConstant = true;
    Parameter(const string &data) : data(data) {}
    Parameter() {}

    void setValue(string value) {
        data = value;
        return;
    }

    string getValue() {
        return data;
    }

    Parameter getParameters() {
        return data;
    }

    const char &at(unsigned int index) const
    {
        return data.at(index);
    }

    string toString() {
        stringstream ss;
        ss << data;
        return ss.str();
    }
};


#endif //CS236PROJECT1_PARAMETER_H
