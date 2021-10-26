#include <fstream>
#include <iostream>
#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

int main(int argc, char* argv[])
{
    ifstream sourceCodeFile;
    LexicalAnalyzer* la;
    Token* nextToken;
    TokenCodes tc;

    std::string strPath = "example1.ada";
    sourceCodeFile.open(strPath, ifstream::in);
    if (sourceCodeFile.is_open())
    {
        la = new LexicalAnalyzer(&sourceCodeFile);
        do
        {
            nextToken = la->getNextToken();
            cout << *nextToken << endl;
            tc = nextToken->getTokenCode();
            delete nextToken;
        } while (tc != EOI);
        delete la;
    }
    else
        printf("ERROR - cannot open input file \n");

    return 0;
}
