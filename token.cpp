#include <iostream>
#include "token.hpp"

void Token::printToken()
{
    if (isName()) {
        std::cout << nameTokenValue;
    } else {
        std::cout << charToken;
    }

}
