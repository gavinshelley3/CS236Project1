//
// Created by Gavin on 2/28/2022.
//

#ifndef CS236PROJECT1_SCHEME_H
#define CS236PROJECT1_SCHEME_H
#include <vector>
#include <string>
using namespace std;

class Scheme : public vector<string> {

public:

    Scheme(vector<string> names) : vector<string>(names) {}

    Scheme() {}
};

#endif //CS236PROJECT1_SCHEME_H
