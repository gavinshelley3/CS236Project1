//
// Created by Gavin on 2/28/2022.
//

#ifndef CS236PROJECT1_TUPLE_H
#define CS236PROJECT1_TUPLE_H
#include <vector>
#include <string>
#include <sstream>
#include "Scheme.h"
using namespace std;

class Tuple : public vector<string> {

public:

    Tuple(vector<string> names) : vector<string>(names) { }

    Tuple() {}

    string toString(const Scheme& scheme) const {
        stringstream out;
        if (scheme.size() != size()) {
            out << "Scheme and Tuple are of different sizes" << endl;
        }
        for (unsigned i = 0; i < scheme.size(); i++) {
            if (i > 0) {
                out << ", ";
            }
            const string& name = scheme.at(i);
            const string& value = at(i);
            out << name << "=" << value;
        }
        return out.str();
    }
};

#endif //CS236PROJECT1_TUPLE_H
