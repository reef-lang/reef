#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <map>

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

// Keywords
const std::string FUNCTION = "FUNCTION";
const std::string LET = "LET";
const std::string TRUE = "TRUE";
const std::string FALSE = "FALSE";
const std::string IF = "IF";
const std::string ELSE = "ELSE";
const std::string RETURN = "RETURN";

// Data types
const std::string INT = "INT";

// Miscellaneous
const std::string EOf = "EOF";
const std::string IDENT = "IDENT";
const std::string ILLEGAL = "ILLEGAL";

std::map<std::string, TokenType> keywords = {
    {"if", IF},
    {"let", LET},
    {"else", ELSE},
    {"true", TRUE},
    {"false", FALSE},
    {"fn", FUNCTION},
    {"return", RETURN},
};

using TokenType = std::string;

// Structure for tokens
struct Token
{
    TokenType type;
    std::string text; // Holds the literal value of the token

    Token() : text(), type() {}
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

    // Returns the next token.
    Token nextToken()
    {
        Token token;

        // By calling skipWhitespace() at the beginning of the function,
        // we make sure our lexer is not trying to tokenize a whitespace.
        skipWhitespace();

        // Operators
        if (curChar == '+')
        {
            token = Token("+", PLUS);
        }
        else if (curChar == '-')
        {
            token = Token("-", MINUS);
        }
        else if (curChar == '*')
        {
            token = Token("*", ASTERISK);
        }
        else if (curChar == '/')
        {
            token = Token("/", SLASH);
        }
        else if (curChar == '<')
        {
            token = Token("<", LT);
        }
        else if (curChar == '>')
        {
            token = Token(">", GT);
        }

        else if (curChar == '=')
        {
            // Checking if this token is supposed to be = or ==
            if (peek() == '=')
            {
                nextChar();
                token = Token("==", EQ);
            }
            else
            {
                token = Token("=", ASSIGN);
            }
        }

        else if (curChar == '!')
        {
            // Checking if this token is supposed to be ! or !=
            if (peek() == '=')
            {
                nextChar();
                token = Token("!=", NOT_EQ);
            }
            else
            {
                token = Token("!", BANG);
            }
        }

        // Delimiters
        else if (curChar == ',')
        {
            token = Token(",", COMMA);
        }
        else if (curChar == ';')
        {
            token = Token(";", SEMICOLON);
        }
        else if (curChar == '(')
        {
            token = Token("(", LPAREN);
        }
        else if (curChar == ')')
        {
            token = Token(")", RPAREN);
        }
        else if (curChar == '{')
        {
            token = Token("{", LBRACE);
        }
        else if (curChar == '}')
        {
            token = Token("}", RBRACE);
        }
        else if (curChar == '\0')
        {
            token = Token("", EOf);
        }

        // Keyword or identifier
        else if (isalpha(curChar))
        {
            std::string tokenText = gatherCharacters();

            // Keyword
            if (keywords.find(tokenText) != keywords.end())
            {
                token = Token(tokenText, keywords[tokenText]);
            }
            else
            { // Identifier
                token = Token(tokenText, IDENT);
            }
        }

        // Int
        else if (isdigit(curChar))
        {
            token = Token(gatherDigits(), INT);
        }

        // Illegal character
        else
        {
            // Since curChar is typed as `char` and Token takes in `std::string`,
            // converted illegal character to a string.
            token = Token(std::string(1, curChar), ILLEGAL);
        };

        nextChar();
        return token;
    }

    // Processes the next character.
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
    }

    // Peeks and returns the upcoming character.
    char peek()
    {
        if (curPos + 1 >= source.length())
        {
            return '\0'; // EOF
        }

        return source[curPos + 1];
    }

    // Skips whitespace (includes tabs, newlines and carriage returns)
    void skipWhitespace()
    {
        while (curChar == ' ' || curChar == '\t' || curChar == '\n' || curChar == '\r')
        {
            nextChar();
        }
    }

    // Gathers the characters for identifier or keyword
    std::string gatherCharacters()
    {
        int startPosition = curPos;

        while (isalnum(peek()))
        {
            nextChar();
        }

        return source.substr(startPosition, curPos - startPosition + 1); // Getting the substring.
    }

    // Gathers the digits
    std::string gatherDigits()
    {
        int startPosition = curPos;

        while (isdigit(peek()))
        {
            nextChar();
        }

        return source.substr(startPosition, curPos - startPosition + 1); // Getting the substring.
    }
};

#endif