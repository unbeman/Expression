//
// Created by devernua on 13.12.16.
//

#include <iostream>
#include "Expression.h"

int main()
{
    std::string exp;
    std::cin >> exp;
    Expression *a = get_expression(exp);

    Visitor *v = new PrintVisitor();
    a->visit(v);
    std::cout << std::endl;
    std::cout << a->evaluate() << std::endl;
    return 0;
}