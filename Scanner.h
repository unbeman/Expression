//
// Created by devernua on 13.12.16.
//

#ifndef CALCULATOR_SCANNER_H
#define CALCULATOR_SCANNER_H

#include <string>

class Scanner {
public:
    Scanner(const std::string& str): str(str) {}
    char operator*() const { return (char) ((pos <= str.size()) ? str[pos] : '\0'); }// проверка на переполнение
    Scanner& operator++() { pos++; return *this; }
    bool IsComplete() const{ return (pos >= str.size());}
private:
    const std::string& str;
    size_t pos = 0;
};


#endif //CALCULATOR_SCANNER_H
