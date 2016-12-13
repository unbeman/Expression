#ifndef EXPRESSION_VISITOR_H
#define EXPRESSION_VISITOR_H


struct Visitor;
struct PrintVisitor;

struct Expression
{
    virtual double evaluate() const = 0;
    virtual ~Expression(){}

    virtual void visit(Visitor * visitor) const  = 0;
};

struct Number : Expression
{
    Number(double value);
    double evaluate() const;

    double get_value() const { return value; }

    void visit(Visitor * visitor) const;

private:
    double value;
};

struct BinaryOperation : Expression
{
    BinaryOperation(Expression const * left, char op, Expression const * right): left(left), op(op), right(right) {}
    double evaluate() const;
    ~BinaryOperation();

    Expression const * get_left()  const { return left; }
    Expression const * get_right() const { return right; }
    char get_op() const { return op; }

    void visit(Visitor * visitor) const;


private:
    Expression const * left;
    Expression const * right;
    char op;
};

struct UnaryOperation : Expression
{
    UnaryOperation(char op, Expression const * right) : op(op), right(right) {}
    double evaluate() const;
    ~UnaryOperation();

    Expression const * get_right() const { return right; }
    char get_op() const { return op; }

    void visit(Visitor * visitor) const;
private:
    Expression const * right;
    char op;
};

struct Visitor {
    virtual void visitNumber(Number const * number) = 0;
    virtual void visitBinaryOperation(BinaryOperation const * binary) = 0;
    virtual void visitUnaryOperation(UnaryOperation const * unary) = 0;
    virtual ~Visitor() { }
};

struct PrintVisitor : Visitor {
    void visitNumber(Number const * number);
    void visitBinaryOperation(BinaryOperation const * bop);
    void visitUnaryOperation(UnaryOperation const * uop);
};

Expression * get_expression(const std::string& str);

#endif