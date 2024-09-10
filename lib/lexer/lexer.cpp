#ifndef LEX_H
#define LEX_H

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

#endif