#include <iostream>
#include "Expression.h"

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

   
BinaryOperation::BinaryOperation(Expression const * left, char op, Expression const * right)
    : left(left), op(op), right(right)
{ }

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
    
BinaryOperation::~BinaryOperation()
{
    delete left;
    delete right;
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
    cout << bop->get_op() << " ";
    bop->get_right()->visit(this);
    cout << ")";
}

Expression const * get_expression(){
    return new Number(0);
}