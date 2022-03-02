//
// Created by Gavin on 1/18/2022.
//

#ifndef CS236PROJECT1_SCANNER_H
#define CS236PROJECT1_SCANNER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdio>
#include "Token.h"
using namespace std;

class Scanner {
private:
    unsigned int lineNum = 1;
    unsigned int permLineNum = 1;

public:
    string input = "";
    Scanner(const string& input) : input(input) {}
    [[nodiscard]] bool colonToken() const;
    [[nodiscard]] bool queriesToken() const;
    [[nodiscard]] bool schemesToken() const;
    [[nodiscard]] bool factsToken() const;
    [[nodiscard]] bool rulesToken() const;
    int identToken();
    int stringToken();
    int commentToken();
    char hashtag ();


    Token scanToken(int &total) {
        TokenType type = TokenType::UNDEFINED;
        string value = "";
        lineNum = permLineNum;
        int size = 1;
        if (input.empty()) {
            value = "";
            type = TokenType::E_O_F;
        } else if (!input.empty()) {
            while (isspace(input.at(0)) && !input.empty()) {
                if (input.at(0) == '\n') {
                    lineNum++;
                    permLineNum++;
                }
                    input = input.substr(1, input.size() - 1);
                if (input == "") {
                    value = "";
                    type = TokenType::E_O_F;
                    return Token(type, value, lineNum);
                }
            }
            char alpha = input.at(0);
            if (isalpha(alpha) && input.at(0) != 'Q' && input.at(0) != 'S' && input.at(0) != 'F' && input.at(0) != 'R'){
                if (input.size() == 1) {
                    size = input.size();
                    value = input.substr(0, size);
                    type = TokenType::ID;
                    return Token(type, value, lineNum);
                }
                else {
                    size = identToken();
                    type = TokenType::ID;
                    value = input.substr(0, size);
                    input = input.substr(size, input.size() - size);
                    return Token(type, value, lineNum);
                }
            }
            switch (input.at(0)) {
            /*COMMA ,*/
                case ',':
                    size = 1;
                    type = TokenType::COMMA;
                    break;

            /*PERIOD . */
                case '.':
                    size = 1;
                    type = TokenType::PERIOD;
                    break;

            /*Q_MARK ? */
                case '?':
                    size = 1;
                    type = TokenType::Q_MARK;
                    break;

            /*LEFT_PAREN ( */
                case '(':
                    size = 1;
                    type = TokenType::LEFT_PAREN;
                    break;

            /*RIGHT_PAREN ) */
                case ')':
                    size = 1;
                    type = TokenType::RIGHT_PAREN;
                    break;

            /*MULTIPLY * */
                case '*':
                    size = 1;
                    type = TokenType::MULTIPLY;
                    break;

            /*ADD + */
                case '+':
                    size = 1;
                    type = TokenType::ADD;
                    break;

            /*COLON : */
                case ':':
                    if (colonToken()) {
                        size = 2;
                        type = TokenType::COLON_DASH;
                    }
                    else if (!colonToken()) {
                        size = 1;
                        type = TokenType::COLON;
                    }
                    break;

            /*SCHEMES*/
                 case 'S':
                     if (schemesToken()) {
                         size = 7;
                         type = TokenType::SCHEMES;
                     }
                     else {
                         size = identToken();
                         type = TokenType::ID;
                     }
                    break;

            /*FACTS*/
                 case 'F':
                    if (factsToken()) {
                        size = 5;
                        type = TokenType::FACTS;
                    }
                    else {
                        size = identToken();
                        type = TokenType::ID;
                    }
                    break;

            /*RULES*/
                 case 'R':
                     if (rulesToken()) {
                        size = 5;
                        type = TokenType::RULES;
                    } else {
                         size = identToken();
                         type = TokenType::ID;
                    }
                    break;

            /*QUERIES*/
                 case 'Q':
                     if (queriesToken()) {
                         size = 7;
                         type = TokenType::QUERIES;
                     }
                     else {
                         size = identToken();
                         type = TokenType::ID;
                     }
                     break;

            /*COMMENT # */
                case '#':
                    lineNum = permLineNum;
                    size = commentToken();
                    if (size != -1) {
                        type = TokenType::COMMENT;
                    }
                    else {
                        size = input.size();
                        value = input.substr(0, size);
                        cout << "(" << "UNDEFINED" << "," << "\"" << value << "\"" << "," << lineNum << ")" << endl;
                        type = TokenType::E_O_F;
                        total++;
                        size = 0;
                        value = "";
                        input = "";
                        lineNum = permLineNum;
                    }
                    break;

            /*STRING '' */
                case '\'':
                    lineNum = permLineNum;
                    size = stringToken();
                    if (size != -1) {
                        type = TokenType::STRING;
                    }
                    else {
                        size = input.size();
                        value = input.substr(0, size);
                        cout << "(" << "UNDEFINED" << "," << "\"" << value << "\"" << "," << lineNum << ")" << endl;
                        type = TokenType::E_O_F;
                        total++;
                        size = 0;
                        value = "";
                        input = "";
                        lineNum = permLineNum;
                    }
                    break;
            }
            value = input.substr(0, size);
            if (input.size() >= 1) {
                input = input.substr(size, input.size() - size);
            }
        }
        return Token(type, value, lineNum);
    }
};


bool Scanner::colonToken() const {
    if (input.size() >= 2) {
        string colon = input.substr(0, 2);
        if (colon == ":-") {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool Scanner::queriesToken() const {
    if (input.size() >= 7) {
        string queries = input.substr(0, 7);
        if (queries == "Queries") {
            if (input.size() >= 8 && !isalpha(input.at(7))) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    return false;
}

bool Scanner::schemesToken() const {
    if (input.size() >= 7) {
        string schemes = input.substr(0, 7);
        if (schemes == "Schemes") {
            if (input.size() >= 8) {
                if (!isalpha(input.at(7))) {
                    return true;
                } else if (isalpha(input.at(7))){
                    return false;
                }
            }
            else {
                return true;
            }
        } else {
            return false;
        }
    }
    return false;
}

bool Scanner::factsToken() const {
    if (input.size() >= 5) {
        string facts = input.substr(0, 5);
        if (facts == "Facts") {
            if (input.size() >= 6 && !isalpha(input.at(5))) {
                return true;
            }
            else {
                return false;
            }
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool Scanner::rulesToken() const {
    if (input.size() >= 5) {
        string rules = input.substr(0, 5);
        if (rules == "Rules") {
            if (input.size() >= 6 && !isalpha(input.at(5))) {
                return true;
            }
            else {
                return false;
            }
            return true;
        } else {
            return false;
        }
    }
    return false;
}

int Scanner::identToken() {
    int size = 0;
    string str;
    if (isdigit(input.at(0))) {
        size = 1;
        return size;
    }
    for (unsigned int i = 1; i < input.size() + 1; ++i) {
        if (isspace(input.at(i)) == true) {
            size = i;
            break;
        } else if (isalnum(input.at(i)) == false) {
            size = i;
            break;
        } else if (input.size() == i) {
            size = i;
            break;
        }
    }
    return size;
}

int Scanner::stringToken() {
    string str;
    int size = 0;
    for (unsigned int i = 1; i < input.size(); ++i) {
        str = input.substr(i,1);
        if (input.at(i) == '\n') {
            permLineNum++;
        }
        if (str == "'") {
            size = i + 1;
            break;
        }
        else if (input.size() - 1 == i) {
            size = -1;
            break;
        }
        else if (str == "") {
            size = -1;
            break;
        }
    }
    return size;
}

int Scanner::commentToken() {
    int size = 0;
    if (input.size() >= 2) {
        string str = input.substr(0, 2);
        if (str == "#|") {
            /* Block Comment */
            for (unsigned int i = 2; i < input.size() + 1; ++i) {
                str = input.substr(i, 1);
                if (input.at(0) == '\n') {
                    permLineNum++;
                }
                if (str == "|") {
                    char temp = input.at(i);
                    if (temp == '#') {
                        size = i + 2;
                        break;
                    } else {
                        size = -1;
                        break;
                    }
                } else if (i == input.size()) {
                    size = -1;
                    break;
                }
            }
        }
        else {
            /* Regular Comment */
            for (unsigned int i = 1; i < input.size() + 1; ++i) {
                str = input.substr(i, 1);
                if (str == "\n") {
                    size = i;
                    break;
                }
                else if (i == input.size()) {
                    size = i;
                    break;
                }
            }
        }
    }
    else if (input.size() == 1) {
        size = 1;
    }
    return size;
}



#endif //CS236PROJECT1_SCANNER_H
