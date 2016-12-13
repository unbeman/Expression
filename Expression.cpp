#include <iostream>
#include "Expression.h"
#include "Scanner.h"

using namespace std;

Number::Number(double value): value(value){}

double Number::evaluate() const
{ 
    return value;
}

void Number::visit(Visitor * visitor) const 
{ 
    visitor->visitNumber(this); 
}

double BinaryOperation::evaluate() const
{
    double lt = left->evaluate();
    double rt = right->evaluate();
    
    switch (op){
        case '+': return lt + rt;
        case '-': return lt - rt;
        case '*': return lt * rt;
        case '/': return lt / rt;
    
    }
    return 0;
}

double UnaryOperation::evaluate() const {
    double rt = right->evaluate();
    switch (op){
        case '+': return rt;
        case '-': return -rt;
    }
    return 0;
}

UnaryOperation::~UnaryOperation() {
    delete right;
}

BinaryOperation::~BinaryOperation()
{
    delete left;
    delete right;
}

void UnaryOperation::visit(Visitor *visitor) const
{
    visitor->visitUnaryOperation(this);
}

void BinaryOperation::visit(Visitor * visitor) const 
{ 
    visitor->visitBinaryOperation(this); 
}


void PrintVisitor::visitNumber(Number const * number)
{
    std::cout << number->get_value();
}

void PrintVisitor::visitBinaryOperation(BinaryOperation const * bop)
{   
    cout << "(";
    bop->get_left()->visit(this);
    cout << " " << bop->get_op() << " ";
    bop->get_right()->visit(this);
    cout << ")";
}

void PrintVisitor::visitUnaryOperation(UnaryOperation const *uop) {
    cout << "(";
    cout << uop->get_op();
    uop->get_right()->visit(this);
    cout << ")";
}

Expression * _get_num(Scanner &s) {
    double res = 0.0;
    //if(!isdigit(*s)) // exception
    while (isdigit(*s)) {
        res *= 10.0;
        res += *s - '0';
        ++s;
    }
    if (*s == '.'){
        ++s;
        //if(!isdigit(*s)) // exception
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
        else{
            //exception
        }

    } else{
        result = _get_num(s);
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
        result = _get_brackets(s);
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