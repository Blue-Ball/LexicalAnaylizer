#include <iostream>
#include <fstream>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

LexicalAnalyzer::LexicalAnalyzer(ifstream *scf)
{
  sourceCodeFile = scf;
  m_pTokenLink = NULL;
  m_pFirstTokenLink = NULL;
  parse();
}

void LexicalAnalyzer::AddLink(Token *pToken)
{
  if(m_pFirstTokenLink == NULL)
  {
    TOKEN_LINK *pTokenLink = new TOKEN_LINK;
    pTokenLink->pNext = NULL;
    pTokenLink->pToken = pToken;
    m_pTokenLink = pTokenLink;
    m_pFirstTokenLink = pTokenLink;
  }
  else
  {
    TOKEN_LINK *pTokenLink = new TOKEN_LINK;
    pTokenLink->pNext = NULL;
    pTokenLink->pToken = pToken;
    m_pTokenLink->pNext = pTokenLink;
    m_pTokenLink = pTokenLink;
  }
}

void LexicalAnalyzer::parse()
{
  Token *t;

  string strLine;
  while(getline(*sourceCodeFile, strLine))
  {
    string strTrim;
    if (strLine.length() == 0)
        strTrim = "";
    else
        strTrim = trim(strLine);
    if(strTrim == "")
    {
      t = new Token();
      t->setTokenCode(NEWLINE);
      AddLink(t);
    }
    else
    {
      int left = 0, right = 0;
      
      char *str = (char *)strTrim.c_str();

      int len = strlen(str);
  
      while (right <= len && left <= right) {
        if(isDelimiter(str[right]) == false && (left == right || isDelimiter(str[left]) == false))
        {
          right++;
          continue;
        }
        else if(isDelimiter(str[right]) == true && (left == right || isDelimiter(str[left]) == true))
        {
          right++;
          continue;
        }

        if(isDelimiter(str[right]) == false && left != right)
        {
          char* subStr = subString(str, left, right - 1);

          trim(subStr);
          if (strlen(subStr) == 0)
          {
              
          }
          else
          {
            int nCode = getSymbolCodeFromString(subStr);
            if (nCode != -1)
            {
                t = new Token();
                t->setTokenCode((TokenCodes)nCode);
                t->setLexemeString(subStr);
                AddLink(t);
            }
            else
            {
                t = new Token();
                t->setTokenCode(NAL);
                AddLink(t);
            }
          }
          left = right;
        }
        else if(isDelimiter(str[right]) == true && left != right)
        {
          char* subStr = subString(str, left, right - 1);

          int nCode = getKeywordCodeFromString(subStr);
          if(nCode != -1)
          {
            t = new Token();
            t->setTokenCode((TokenCodes)nCode);
            t->setLexemeString(subStr);
            AddLink(t);
          }
          else
          {
            if(isIdentifier(subStr))
            {
              t = new Token();
              t->setTokenCode(IDENT);
              t->setLexemeString(subString(subStr, 0, MIN(9, strlen(subStr))));
              AddLink(t);
            }
            else if(isNumeric(subStr))
            {
              t = new Token();
              t->setTokenCode(NUMLIT);
              //t->setLexemeString(subString(subStr, 0, MIN(9, strlen(subStr))));
              t->setLexemeNumber(atoi(subStr));
              AddLink(t);
            }
            else
            {
              t = new Token();
              t->setTokenCode(NAL);
              AddLink(t);
            }
          }
          left = right;
        }
        else
        {
          right++;
        }
      }
    }
  }

  t = new Token();
  t->setTokenCode(EOI);
  AddLink(t);
  
  m_pTokenLink = m_pFirstTokenLink;
  
  // pToken->setLexemeString(strTrim);
}

bool LexicalAnalyzer::isIdentifier(char *str){
  if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
   str[0] == '3' || str[0] == '4' || str[0] == '5' ||
   str[0] == '6' || str[0] == '7' || str[0] == '8' ||
   str[0] == '9' || isDelimiter(str[0]) == true)
    return false;
   return true;
}

bool LexicalAnalyzer::isInteger(char* str)
{
    int i, len = strlen(str);
 
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}
 
bool LexicalAnalyzer::isRealNumber(char* str)
{
    int i, len = strlen(str);
    bool hasDecimal = false;
 
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||
            (str[i] == '-' && i > 0))
            return false;
        if (str[i] == '.')
            hasDecimal = true;
    }
    return (hasDecimal);
}

bool LexicalAnalyzer::isNumeric(char *str){
  if(isInteger(str) || isRealNumber(str))
    return true;

  return false;
}

int LexicalAnalyzer::getCurrentCharPositionNumber()
{
    return 0;
}

const string LexicalAnalyzer::codesToString(TokenCodes v)
{
  switch (v)
    {
        case PLUS:   return "PLUS";
        case MINUS:   return "MINUS";
        case TIMES: return "TIMES";
        case EQL: return "EQL";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case COMMA: return "COMMA";
        case SEMICOLON: return "SEMICOLON";
        case SLASH: return "SLASH";
        case NEQ: return "NEQ";
        case COLON: return "COLON";
        case BECOMES: return "BECOMES";
        case LSS: return "LSS";
        case LEQ: return "LEQ";
        case GTR: return "GTR";
        case GEQ: return "GEQ";
        case BEGINSYM: return "BEGINSYM";
        case BOOLSYM: return "BOOLSYM";
        case ELSESYM: return "ELSESYM";
        case ENDSYM: return "ENDSYM";
        case FALSESYM: return "FALSESYM";
        case GETSYM: return "GETSYM";
        case IFSYM: return "IFSYM";
        case ISSYM: return "ISSYM";
        case INTSYM: return "INTSYM";
        case LOOPSYM: return "LOOPSYM";
        case NEWLINE: return "NEWLINE";
        case NOTSYM: return "NOTSYM";
        case NULLSYM: return "NULLSYM";
        case PROCSYM: return "PROCSYM";
        case PUTSYM: return "PUTSYM";
        case REMSYM: return "REMSYM";
        case THENSYM: return "THENSYM";
        case TRUESYM: return "TRUESYM";
        case WHILESYM: return "WHILESYM";
        case IDENT: return "IDENT";
        case NUMLIT: return "NUMLIT";
        case EOI: return "EOI";
        case NAL: return "NAL";
        default:      return "NAL";
    }
}

int LexicalAnalyzer::getKeywordCodeFromString(char* str)
{
    int   nReturn = -1;
    if(!strcmp(str, "begin")) nReturn = BEGINSYM;
    if(!strcmp(str, "boolean")) nReturn = BOOLSYM;
    if(!strcmp(str, "else")) nReturn = ELSESYM;
    if(!strcmp(str, "end")) nReturn = ENDSYM;
    if(!strcmp(str, "false")) nReturn = FALSESYM;
    if(!strcmp(str, "get")) nReturn = GETSYM;
    if(!strcmp(str, "if")) nReturn = IFSYM;
    if(!strcmp(str, "is")) nReturn = ISSYM;
    if(!strcmp(str, "integer")) nReturn = INTSYM;
    if(!strcmp(str, "loop")) nReturn = LOOPSYM;
    if(!strcmp(str, "not")) nReturn = NOTSYM;
    if(!strcmp(str, "null")) nReturn = NULLSYM;
    if(!strcmp(str, "procedure")) nReturn = PROCSYM;
    if(!strcmp(str, "put")) nReturn = PUTSYM;
    if(!strcmp(str, "rem")) nReturn = REMSYM;
    if(!strcmp(str, "then")) nReturn = THENSYM;
    if(!strcmp(str, "true")) nReturn = TRUESYM;
    if(!strcmp(str, "while")) nReturn = WHILESYM;
    return nReturn;
}

int LexicalAnalyzer::getSymbolCodeFromString(char* str)
{
    int   nReturn = -1;
    if(!strcmp(str, "+")) nReturn = PLUS;
    if(!strcmp(str, "-")) nReturn = MINUS;
    if(!strcmp(str, "*")) nReturn = TIMES;
    if(!strcmp(str, "=")) nReturn = EQL;
    if(!strcmp(str, "(")) nReturn = LPAREN;
    if(!strcmp(str, ")")) nReturn = RPAREN;
    if(!strcmp(str, ",")) nReturn = COMMA;
    if(!strcmp(str, ";")) nReturn = SEMICOLON;
    if(!strcmp(str, "/")) nReturn = SLASH;
    if(!strcmp(str, "/=")) nReturn = NEQ;
    if(!strcmp(str, ":")) nReturn = COLON;
    if(!strcmp(str, ":=")) nReturn = BECOMES;
    if(!strcmp(str, "<")) nReturn = LSS;
    if(!strcmp(str, "<=")) nReturn = LEQ;
    if(!strcmp(str, ">")) nReturn = GTR;
    if(!strcmp(str, ">=")) nReturn = GEQ; 
    return nReturn;
}

char* LexicalAnalyzer::subString(char* str, int left, int right)
{
    int i;
    char* subStr = (char*)malloc(
                  sizeof(char) * (right - left + 2));
 
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}

bool LexicalAnalyzer::isDelimiter(char chInput)
{
    bool   bReturn = false;
    if(chInput == ' ') bReturn = true;
    if(chInput == '+') bReturn = true;
    if(chInput == '-') bReturn = true;
    if(chInput == '*') bReturn = true;
    if(chInput == '=') bReturn = true;
    if(chInput == '(') bReturn = true;
    if(chInput == ')') bReturn = true;
    if(chInput == ',') bReturn = true;
    if(chInput == ';') bReturn = true;
    if(chInput == '/') bReturn = true;
    if(chInput == ':') bReturn = true;
    if(chInput == '<') bReturn = true;
    if(chInput == '>') bReturn = true;
    if (chInput == '.') bReturn = true;
    return bReturn;
}

void LexicalAnalyzer::trim(char* str) {
    int start = 0; // number of leading spaces
    char* buffer = str;
    while (*str && *str++ == ' ') ++start;
    while (*str++); // move to end of string
    int end = str - buffer - 1;
    while (end > 0 && buffer[end - 1] == ' ') --end; // backup over trailing spaces
    buffer[end] = 0; // remove trailing spaces
    if (end <= start || start == 0) return; // exit if no leading spaces or string is now empty
    str = buffer + start;
    while ((*buffer++ = *str++));  // remove leading spaces: K&R
}

string LexicalAnalyzer::trim(string &s)
{
    auto start = s.begin();
    while (start != s.end() && isspace(*start)) {
        start++;
    }
 
    auto end = s.end();
    do {
        end--;
    } while (distance(start, end) > 0 && isspace(*end));
 
    return string(start, end + 1);
}

void LexicalAnalyzer::setToken(Token *pToken, string strInput)
{
  string strTrim = trim(strInput);
  if(strTrim == "")
  {
    pToken->setTokenCode(NEWLINE);
  }
  else
  {
    pToken->setTokenCode(IDENT);
  }
  pToken->setLexemeString(strTrim);
}

Token* LexicalAnalyzer::getNextToken()
{
  Token *t;
  t = NULL;

  if(m_pTokenLink != NULL)
  {
    t = m_pTokenLink->pToken;
    if(m_pTokenLink->pNext)
    {
      m_pTokenLink = m_pTokenLink->pNext;
    }
  }
  return t;
}

