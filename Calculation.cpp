//
// Created by a.kukuev on 20.12.16.
//
#include "Exception.h"
#include "Scanner.h"
#include "Expression.h"

Expression * _get_num(Scanner &s) {
    double res = 0.0;

    if (!isdigit(*s)){ throw DigitErr(*s);}// exception

    while (isdigit(*s)) {
        res *= 10.0;
        res += *s - '0';
        ++s;
    }
    if (*s == '.'){
        ++s;
        if(!isdigit(*s)){ throw DigitErr(*s);} // exception
        double step = 1.0;
        while (isdigit(*s)) {
            step /= 10.0;
            res += step * (*s - '0');
            ++s;
        }
    }
    return new Number(res);
}

Expression * _get_add_sub(Scanner &s);

Expression * _get_brackets(Scanner &s) {
    Expression * result = nullptr;
    if(*s == '(') {
        ++s;
        result = _get_add_sub(s);

        if(*s == ')') {
            ++s;
        }
        else{ throw CloseErr(*s); //exception
        }
    } else{
        result = _get_num(s);
    }
    return result;
}

Expression * _get_pow(Scanner &s){
    Expression * result = _get_brackets(s);
    if (*s == '^'){
        char op = *s;
        ++s;
        Expression * secondOp = _get_pow(s);
        result = new BinaryOperation(result, op, secondOp);
    }
    return result;
}

Expression * _get_unary(Scanner &s){
    Expression * result = nullptr;
    if (*s == '+' || *s == '-'){
        char op = *s;
        ++s;
        result = _get_unary(s);
        result = new UnaryOperation(op, result);
    } else{
        result = _get_pow(s);
    }
    return result;
}

Expression * _get_mul_div(Scanner &s) {
    Expression * result = _get_unary(s);
    while (*s == '*' || *s == '/') {
        char op = *s;
        ++s;
        Expression * secondOp = _get_unary(s);
        result = new BinaryOperation(result, op, secondOp);
    }
    return result;
}

Expression * _get_add_sub(Scanner &s)
{
    Expression* result = _get_mul_div(s);

    while (*s == '+' || *s == '-') {
        char op = *s;
        ++s;
        Expression * secondOp = _get_mul_div(s);
        result = new BinaryOperation(result, op, secondOp);
    }
    return result;

}

Expression * get_expression(const std::string& str){
    Scanner s(str);
    Expression* result = _get_add_sub(s);

    return result;
}
