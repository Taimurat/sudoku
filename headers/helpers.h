#ifndef HELPERS_H
#define HELPERS_H

#pragma once
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <iostream>
#include <fstream>
#ifndef str
#define str std::string
#endif //str

using std::cin;
using std::cout;
using std::endl;
using std::vector;


extern std::ofstream fout;

class MyException : public std::exception
{
public:
    MyException(str msg);

    const char* what() const noexcept override;

private:
    str message;
};

template<typename... Args>
void log(Args... args)
{
    fout << "LOG: ";
    ((fout << args << " "), ...);
    fout << endl;
}

template<typename... Args>
void warning(Args... args)
{
    fout << "WARNING: ";
    ((fout << args << " "), ...);
    fout << endl;
}

template<typename... Args>
void error(Args... args)
{
    fout << "ERROR: ";
    ((fout << args << " "), ...);
    fout << endl;
}

#endif //HELPERS_H