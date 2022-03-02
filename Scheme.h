//
// Created by Gavin on 2/28/2022.
//

#ifndef CS236PROJECT1_SCHEME_H
#define CS236PROJECT1_SCHEME_H
#include <vector>
#include <string>
//#include "Tuple.h"
using namespace std;

class Scheme : public vector<string> {

public:

    Scheme(vector<string> names) : vector<string>(names) {}

    Scheme() {}
};

//class Scheme {
//private:
//    vector<string> attributes;
//public:
//    string at (unsigned int index) {
//        return attributes. at(index);
//    }
//
//    unsigned int size() {
//        return attributes.size();
//    }
//
//    void push_back(string newAttribute) {
//        attributes.push_back(newAttribute);
//    }
//
//     bool operator<(const Schemes s) {
//          return this->attributes < s.attributes;
//
//};




#endif //CS236PROJECT1_SCHEME_H
