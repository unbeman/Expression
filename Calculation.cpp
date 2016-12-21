//
// Created by unbeman on 20.12.16.
//
#include "Exception.h"
#include "Scanner.h"
#include "Expression.h"

// формирование числа
Expression * _get_num(Scanner &s) {
    //самый высокий приоритет
    //вершина рекурси

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
        while (isdigit(*s)) { //обработка вещественных чисел
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
        // если встретили открывающую скобку,
        // значит начинаем весь цикл сначала (с наименьшего приоритета)
        // с текущего элемента
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

//формирование возведения в степень, правоассоциативно
Expression * _get_pow(Scanner &s){
    Expression * result = _get_brackets(s); // получаем первый операнд - из выражений с более высоким приоритетом
    if (*s == '^'){
        char op = *s;
        ++s;
        Expression * secondOp = _get_pow(s); // следующий операнд
        result = new BinaryOperation(result, op, secondOp);
    }
    return result;
}

//формирование унарных операций
Expression * _get_unary(Scanner &s){
    Expression * result = nullptr;
    if (*s == '+' || *s == '-'){
        char op = *s;
        ++s;
        result = _get_unary(s);
        result = new UnaryOperation(op, result);
    } else{
        result = _get_pow(s); //если текущий знак не +/- значит не унарная операция, переходим к следующему приоритету
    }
    return result;
}

//формирование умножения и деления
Expression * _get_mul_div(Scanner &s) {
    Expression * result = _get_unary(s); // получаем первый операнд - из выражений с более высоким приоритетом
    while (*s == '*' || *s == '/') { // до тех пор пока можем найти операцию с данным приоритетом
        char op = *s;
        ++s;
        Expression * secondOp = _get_unary(s); // следующий операнд
        result = new BinaryOperation(result, op, secondOp); // формируем BinaryOperation из двух операндов и операции
    }
    return result; // возвращаем полученное поддерево
}

// формирование сложения и вычитания
Expression * _get_add_sub(Scanner &s)
{
    Expression* result = _get_mul_div(s); // получаем первый операнд - из выражений с более высоким приоритетом

    while (*s == '+' || *s == '-') { // до тех пор пока можем найти операцию с данным приоритетом
        char op = *s;
        ++s;
        Expression * secondOp = _get_mul_div(s); // следующий операнд
        result = new BinaryOperation(result, op, secondOp); // формируем BinaryOperation из двух операндов и операции
    }
    return result; // возвращаем полученное поддерево

}

//функция рекурсивного обхода выражения и формирования класса Expression
Expression * get_expression(const std::string& str){
    Scanner s(str);
    Expression* result = _get_add_sub(s); // входим в рекурсию, идем в операцию с наименьшим приоритетом
    if (!s.IsComplete()){ throw SyntaxError();} // не дошли до конца строки
    return result;
}
