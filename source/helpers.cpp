#include "../headers/helpers.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

std::ofstream fout("logs.txt");

MyException::MyException(str msg) : std::exception(), message(msg) {}

const char* MyException::what() const noexcept {
    return message.c_str();
}