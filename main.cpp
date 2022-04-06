#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Database.h"
#include "Interpreter.h"
using namespace std;

int main(int argc, char *argv[]) {
        // check command line arguments
        if (argc != 2) {
            cout << "usage: " << argv[0] << " input_file" << endl;
            return 1;
        }

        // open file
        string fileName = argv[1];
        ifstream ifs (fileName);
        //    cout << fileName << endl;
        ifs.open(fileName);
        if (!ifs.is_open()) {
            cout << "File " << fileName << " could not be found or opened." << endl;
            return 1;
        }
        else {
            //		cout << "File opened" << endl;
        }

        string scanLines;
        stringstream ss;
        ss << ifs.rdbuf(); // reading data
        scanLines = ss.str();


        Scanner scanner = scanLines;
        vector<Token> tokens;


        int total = 0;
        while (!scanner.input.empty()) {
            Token currToken = scanner.scanToken(total);
            if (currToken.getType() != TokenType::COMMENT) {
                tokens.push_back(currToken);
            }
        }

        Parser parser = Parser(tokens);
        parser.parse();
        DatalogProgram DataProg = parser.getDatalogProgram();
        Database database;
        Interpreter interpreter(DataProg, database);
        interpreter.run();

    return 0;
}
