//
// Created by Gavin on 1/18/2022.
//

#ifndef CS236PROJECT1_TOKEN_H
#define CS236PROJECT1_TOKEN_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdio>
using namespace std;

enum class TokenType {
    COMMA, COLON, COMMENT, UNDEFINED, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, E_O_F
};

class Token {
private:
    TokenType type;
    string value;
    unsigned int lineNum;
public:
    Token(TokenType type, const string &value, unsigned int lineNum) : type(type), value(value), lineNum(lineNum) {}

    const string &getValue() const {
        return value;
    }

    void setValue(const string &value) {
        Token::value = value;
    }

    TokenType getType() const {
        return type;
    }

    void setType(TokenType type) {
        Token::type = type;
    }

    unsigned int getLineNum() const {
        return lineNum;
    }

    void setLineNum(unsigned int lineNum) {
        Token::lineNum = lineNum;
    }

    string toString () {
        stringstream outSS;
        outSS << "(" << tokenToString(type) << "," << "\"" << value << "\"" << "," << lineNum << ")";
        return outSS.str();
    }

    string tokenToString(TokenType t) {
        switch (t) {
            case TokenType::COMMA:
                return "COMMA";
            case TokenType::COLON:
                return "COLON";
            case TokenType::COMMENT:
                return "COMMENT";
            case TokenType::PERIOD:
                return "PERIOD";
            case TokenType::Q_MARK:
                return "Q_MARK";
            case TokenType::LEFT_PAREN:
                return "LEFT_PAREN";
            case TokenType::RIGHT_PAREN:
                return "RIGHT_PAREN";
            case TokenType::COLON_DASH:
                return "COLON_DASH";
            case TokenType::MULTIPLY:
                return "MULTIPLY";
            case TokenType::ADD:
                return "ADD";
            case TokenType::SCHEMES:
                return "SCHEMES";
            case TokenType::FACTS:
                return "FACTS";
            case TokenType::RULES:
                return "RULES";
            case TokenType::QUERIES:
                return "QUERIES";
            case TokenType::ID:
                return "ID";
            case TokenType::STRING:
                return "STRING";
            case TokenType::E_O_F:
                return "EOF";
            case TokenType::UNDEFINED:
                return "UNDEFINED";
            default:
                return "BAD TYPE";
        }
    }

    string typeName(TokenType &type) const {
        switch (type) {
        case TokenType::COMMA:
            return "COMMA";
        case TokenType::COLON:
            return "COLON";
        case TokenType::COMMENT:
            return "COMMENT";
		case TokenType::PERIOD:
            return "PERIOD";
		case TokenType::Q_MARK:
            return "Q_MARK";
		case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";
		case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";
		case TokenType::COLON_DASH:
            return "COLON_DASH";
		case TokenType::MULTIPLY:
            return "MULTIPLY";
		case TokenType::ADD:
            return "ADD";
		case TokenType::SCHEMES:
            return "SCHEMES";
		case TokenType::FACTS:
            return "FACTS";
		case TokenType::RULES:
            return "RULES";
		case TokenType::QUERIES:
            return "QUERIES";
		case TokenType::ID:
            return "ID";
		case TokenType::STRING:
            return "STRING";
		case TokenType::E_O_F:
            return "EOF";
        case TokenType::UNDEFINED:
            return "UNDEFINED";
        default:
            return "BAD TYPE";
        }
    }
};


#endif //CS236PROJECT1_TOKEN_H
