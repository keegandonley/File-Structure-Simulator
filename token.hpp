#include<iostream>
#include<cstring>

#ifndef __Token_hpp
#define __Token_hpp

class Token
{
public:
    // variable charToken represents a one-character token such as ( and ).
    // To create such token, use the constructor that accepts a character.

    // variable nameTokenValue represents an atom -- a sequence of character.
    // To create such a token, use the constructor that accepts a string.

    // To create an end-of-text token, create an instance of this
    // class using the contructor that doesn't take any arguments and
    // then, call function makeEndOfText() on that instance.

    Token(): charToken('\0'), nameTokenValue(""), endOfText(false) {}
    Token(char c): charToken(c), nameTokenValue(""), endOfText(false) {}
    Token(std::string st): charToken('\0'), nameTokenValue(st), endOfText(false) {}

    void makeLeftParen()  { charToken = '('; }
    void makeRightParen() { charToken = ')'; }
    void makeLeftBrace()  { charToken = '{'; }
    void makeRightBrace() { charToken = '}'; }
    void makeLeftBracket()  { charToken = '['; }
    void makeRightBracket() { charToken = ']'; }
    void makeEndOfText()  { endOfText = true; }

    bool isLeftParen()    { return charToken == '('; }
    bool isRightParen()   { return charToken == ')'; }
    bool isLeftBrace()    { return charToken == '{'; }
    bool isRightBrace()   { return charToken == '}'; }
    bool isLeftBracket()  { return charToken == '['; }
    bool isRightBracket() { return charToken == ']'; }
    bool isColon()        { return charToken == ':'; }
    bool isComma()        { return charToken == ','; }
    bool isName()         { return nameTokenValue != ""; }
    bool isEndOfText()    { return endOfText; }
    bool& isQuotedString() { return quotedString; }
    bool& isKey()         { return key; }

    std::string getName() { return nameTokenValue; }
    char getChar()        { return charToken; }

    void printToken();

private:
    char charToken;
    std::string nameTokenValue;
    bool endOfText;
    bool quotedString;
    bool key;
};

#endif
