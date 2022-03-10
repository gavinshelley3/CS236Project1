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
            string error = "Scheme and Tuple are of different sizes";
            cout << error << endl;
//            throw error;
        }
        for (unsigned i = 0; i < size(); i++) {
            if (i > 0)
                out << ", ";
            const string& name = scheme.at(i);
            const string& value = at(i);
            out << name << "=" << value;
        }
        return out.str();
    }
};

//class Tuple {
//
//private:
//
//  vector<string> values;
//
//public:
//
//  Tuple(vector<string> values) : values(values) { }
//
//  unsigned size() const {
//    return values.size();
//  }
//
//  const string& at(int index) const {
//    return values.at(index);
//  }
//
//  bool operator<(const Tuple t) const {
//    return values < t.values;
//  }
//
//  // TODO: add more delegation functions as needed
//
//};
#endif //CS236PROJECT1_TUPLE_H
