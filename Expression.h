#ifndef EXPRESSION_VISITOR_H
#define EXPRESSION_VISITOR_H

//forward declaration
struct Visitor;
struct PrintVisitor;

// абстрактный класс Expression
// паттерн фабричный метод
struct Expression
{
    virtual double evaluate() const = 0; //посчитать выражение
    virtual ~Expression(){}

    // Паттерн Visitor для обхода дерева Expression и печати выражения
    virtual void visit(Visitor * visitor) const  = 0;
};

// Выражение - число
struct Number : Expression
{
    Number(double value);
    double evaluate() const;

    double get_value() const { return value; } // функция геттер

    void visit(Visitor * visitor) const;

private:
    double value;
};

//Выражение - бинарная операция
struct BinaryOperation : Expression
{
    BinaryOperation(Expression const * left, char op, Expression const * right): left(left), op(op), right(right) {}
    double evaluate() const;
    ~BinaryOperation();

    Expression const * get_left()  const { return left; } // левый операнд
    Expression const * get_right() const { return right; } // правый операнд
    char get_op() const { return op; } // операция

    void visit(Visitor * visitor) const;


private:
    Expression const * left;
    Expression const * right;
    char op;
};

//Выражение - унарная операция
struct UnaryOperation : Expression
{
    UnaryOperation(char op, Expression const * right) : op(op), right(right) {}
    double evaluate() const;
    ~UnaryOperation();

    Expression const * get_right() const { return right; } // вернуть операнд
    char get_op() const { return op; }

    void visit(Visitor * visitor) const;
private:
    Expression const * right;
    char op;
};

//Класс Visitor - реализация паттерна посетитель для обхода дерева Expression
struct Visitor {
    virtual void visitNumber(Number const * number) = 0;
    virtual void visitBinaryOperation(BinaryOperation const * binary) = 0;
    virtual void visitUnaryOperation(UnaryOperation const * unary) = 0;
    virtual ~Visitor() { }
};

//Класс - применение паттерна посетитель для печати выражения
struct PrintVisitor : Visitor {
    void visitNumber(Number const * number);
    void visitBinaryOperation(BinaryOperation const * bop);
    void visitUnaryOperation(UnaryOperation const * uop);
};

// функция для формирования выражения из строки
Expression * get_expression(const std::string& str);

#endif