//
// Created by a.kukuev on 20.12.16.
//

#ifndef EXPRESSION_EXEPTION_H
#define EXPRESSION_EXEPTION_H

#include <stdexcept>

class MathError: public std::exception {
public:
    virtual ~MathError() throw() {}
    virtual const char * what() const throw(){ return "Calc - Expression calculation error";}
};

class CloseErr: public MathError{
private:
    char badchar;
public:
    CloseErr(char badchar): badchar(badchar){}
    const char * what() const throw(){ return "Calc - ')' expected"; }
    const char badc() const { return badchar; }
};


class DigitErr: public MathError {
private:
    char badchar;
public:
    DigitErr(char badchar): badchar(badchar){}

    const char * what() const throw(){ return "Calc - Digit expected"; }
    const char badc() const { return badchar; }
};

class DivByZeroErr: public MathError{
public:
    const char * what() const throw(){return "Calc - Division by zero"; }
};

#endif //EXPRESSION_EXEPTION_H
