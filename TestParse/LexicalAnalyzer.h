#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <fstream>

#include "Token.h"
#include "TokenCodes.h"

using namespace std;

typedef struct _TOKEN_LINK_
{
  Token *pToken;
  _TOKEN_LINK_ *pNext;
} TOKEN_LINK;

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

class LexicalAnalyzer
{
  private:
    ifstream *sourceCodeFile;


  public:
    LexicalAnalyzer(ifstream*);
    int getCurrentCharPositionNumber();
    Token* getNextToken();

  private:
    TOKEN_LINK *m_pFirstTokenLink;
    TOKEN_LINK *m_pTokenLink;

    const string codesToString(TokenCodes v);
    int getKeywordCodeFromString(char* str);
    bool isDelimiter(char chInput);
    int getSymbolCodeFromString(char* str);
    string trim(string &s);
    void trim(char* str);
    char* subString(char* str, int left, int right);
    void setToken(Token *pToken, string strInput);
    bool isIdentifier(char *str);
    bool isNumeric(char *str);
    bool isInteger(char* str);
    bool isRealNumber(char* str);
    void parse();
    void AddLink(Token *pToken);

};

#endif
