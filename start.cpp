//
// Created by unbeman on 13.12.16.
//

#include <iostream>
#include "Expression.h"
#include "Exception.h"

int main()
{
    std::string exp;
    std::cout << "Expression:" << std::endl;
    std::cin >> exp;
    try {
        Expression *a = get_expression(exp);
        std::cout << "Input: ";
        Visitor *v = new PrintVisitor();
        a->visit(v);
        std::cout << std::endl;
        std::cout << "Result: " << a->evaluate() << std::endl;
    }
    catch (DigitErr e){
        std::cout << e.what()<< std::endl;
    }
    catch (CloseErr e){
        std::cout << e.what()<< std::endl;
    }
    catch (DivByZeroErr e){
        std::cout << e.what()<< std::endl;
    }
    catch (MathError e){
        std::cout << e.what()<< std::endl;
    }
    catch (SyntaxError e){
        std::cout << e.what()<< std::endl;
    }


    return 0;
}