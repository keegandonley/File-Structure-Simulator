
#include "lex.hpp"
#include <ctype.h>
#include <cstdlib>

enum { LPAREN = '(', RPAREN = ')', LBRACKET = '[', RBRACKET = ']', LBRACE = '{', RBRACE = '}', COMMA = ',', COLON = ':', QUOTE = '\'', BACKSLASH = '\\'};

Lex::Lex(std::string input): inputToTokenize(input), whereToStart(0), haveAnUngottenToken(false), lastToken("") {
}

int Lex::skipWhiteSpaces()
{
    // Scan the inputToTokenize string until either we exhaust the input or we find a non-black character.
    while( whereToStart < inputToTokenize.length() && isspace(inputToTokenize[whereToStart]) )
        whereToStart++;
    return whereToStart;
}

std::string Lex::parseName()
{
    // precondition: whereToStart < inputToTokenize.length() is true.
    // That is, there is at least one non-space character (may or many not be a name character)
    // left in inputToTokenize.

    std::string name = "";

    unsigned int idx = whereToStart;
    while( idx < inputToTokenize.length() && isalpha( inputToTokenize[idx] ) ) {
        name += inputToTokenize[idx];
        idx++;
    }

    if( idx - whereToStart == 0 ) {  // inputToTokenize[whereToStart] must havenot been a letter.
        std::cout << "Unexpected character in input. The character is ->" << inputToTokenize[whereToStart]
                  << "<-" << std::endl;
        exit(1);
    }

    whereToStart = idx;
    return name;
}

Token Lex::getToken()
{
    if( haveAnUngottenToken ) {
        haveAnUngottenToken = false;
        return lastToken;
    }

    skipWhiteSpaces();
    if( whereToStart == inputToTokenize.length() ) {
        Token token;
        token.makeEndOfText();
        return lastToken = token;
    }

    if( inputToTokenize[whereToStart] == LPAREN || inputToTokenize[whereToStart] == RPAREN ||
        inputToTokenize[whereToStart] == LBRACKET || inputToTokenize[whereToStart] == RBRACKET ||
        inputToTokenize[whereToStart] == LBRACE || inputToTokenize[whereToStart] == RBRACE ||
        inputToTokenize[whereToStart] == COMMA || inputToTokenize[whereToStart] == COLON ) {
        lastToken = Token(inputToTokenize[whereToStart]);
        whereToStart++;
        return lastToken;
    }

    if (inputToTokenize[whereToStart] == QUOTE){
        std::string string = parseString();
        lastToken = Token(string);
        lastToken.isQuotedString() = true;
        return lastToken;
    }

    std::string name = parseName();
    lastToken = Token(name);
    lastToken.isKey() = true;
    return lastToken;
}

void Lex::ungetToken()
{
    haveAnUngottenToken = true;
}

std::string Lex::parseString()
{
    std::string word = "";

    unsigned int idx = whereToStart + 1;
    while (inputToTokenize[idx] != QUOTE)
    {
        if (inputToTokenize[idx] == BACKSLASH) {
            word += "\\";
            word += inputToTokenize[idx + 1];
            idx = idx + 2;
        }
        word += inputToTokenize[idx];
        idx++;
    }

    whereToStart = idx + 1;
    return word;
}
