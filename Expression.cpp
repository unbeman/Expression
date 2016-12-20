#include <iostream>
#include <cmath>
#include "Expression.h"
#include "Exception.h"
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
        case '/': if (lt / rt == 0.0){ throw DivByZeroErr();} else {return lt / rt;};
        case '^': return std::pow(lt, rt);
    
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

