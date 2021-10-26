#include <iostream>
#include <string>
#include "Token.h"
#include "TokenCodes.h"

Token::Token()
{
  setTokenCode(NAL);
  setLexemeString("");
  setLexemeNumber(-1);
}

Token::Token(TokenCodes tc, string ls, int ln)
{
  setTokenCode(tc);
  setLexemeString(ls);
  setLexemeNumber(ln);
}

int Token::getLexemeNumber()
{
  return lexemeNumber;
}

void Token::setLexemeNumber(int ln)
{
  lexemeNumber = ln;
}

string Token::getLexemeString()
{
  return lexemeString;
}

void Token::setLexemeString(string ls)
{
  lexemeString = ls;
}

TokenCodes Token::getTokenCode()
{
  return tokenCode;
}

void Token::setTokenCode(TokenCodes tc)
{
  tokenCode = tc;
}

ostream& operator<<(ostream& os, const Token& t)
{
  string tcs[] =
  { "IDENT", "NUMLIT", "PLUS", "MINUS", "TIMES", "SLASH", "REMSYM", "TRUESYM", "FALSESYM", "NOTSYM",
    "EQL", "NEQ", "LSS", "LEQ", "GTR", "GEQ", "LPAREN", "RPAREN", "COMMA", "COLON", "SEMICOLON",
    "BECOMES", "BEGINSYM", "ENDSYM", "IFSYM", "THENSYM", "ELSESYM", "WHILESYM", "LOOPSYM",
    "GETSYM", "PUTSYM", "NEWLINE", "NULLSYM", "BOOLSYM", "INTSYM", "ISSYM", "PROCSYM", "NAL", "EOI"
  };

  os << "Next token is: " << tcs[t.tokenCode] << ", lexeme string is \"" << t.lexemeString;
  os << "\", lexeme number is: " << t.lexemeNumber;

  return os;
}
