#ifndef LEXER_H
#define LEXER_H

#include <string>

// Operators
const std::string PLUS = "+";
const std::string MINUS = "-";
const std::string ASTERISK = "*";
const std::string SLASH = "/";
const std::string LT = "<";
const std::string GT = ">";
const std::string ASSIGN = "=";
const std::string BANG = "!";
const std::string EQ = "==";
const std::string NOT_EQ = "!=";

// Delimiters
const std::string COMMA = ",";
const std::string SEMICOLON = ";";
const std::string LPAREN = "(";
const std::string RPAREN = ")";
const std::string LBRACE = "{";
const std::string RBRACE = "}";

using TokenType = std::string;

// Structure for tokens
struct Token
{
    TokenType type;
    std::string text; // Holds the literal value of the token

    Token(std::string text, TokenType type) : text(text), type(type) {}
};

class Lexer
{
public:
    char curChar;       // Current character in the source string.
    int curPos = -1;    // Current position in the source string.
    std::string source; // Source code to lexer as a string.

    // curChar is set to the first char in the source string and curPos is set to 0
    // when nextChar() is called for the first time.

    // Constructor
    Lexer(const std::string &source) : source(source)
    {
        nextChar();
    };

    // Process the next character.
    void nextChar()
    {
        curPos += 1;

        if (curPos >= source.length())
        {
            curChar = '\0'; // EOF
        }
        else
        {
            curChar = source[curPos];
        }
    };
};

#endif