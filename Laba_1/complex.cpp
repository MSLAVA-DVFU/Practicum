#include "complex.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace std;

// Структура для хранения комплексного числа
struct ComplexNumber {
    double real = 0;  // Действительная часть
    double imag = 0;  // Мнимая часть
};

// Функция для парсинга комплексного числа
ComplexNumber parseComplex(const string& input) {
    ComplexNumber result;
    size_t plusPos = input.find('+');
    size_t minusPos = input.find_last_of('-'); // Последний минус (для мнимой части)
    size_t iPos = input.find('i');

    if (iPos == string::npos) {
        throw invalid_argument("Not a complex number: without 'i'");
    }

    string realPart, imagPart;

    if (plusPos != string::npos) {
        realPart = input.substr(0, plusPos);
        imagPart = input.substr(plusPos + 1, iPos - plusPos - 1);
    }
    else if (minusPos > 0) { // Минус для мнимой части
        realPart = input.substr(0, minusPos);
        imagPart = input.substr(minusPos, iPos - minusPos);
    }
    else {
        throw invalid_argument("Not a correct complex number");
    }

    result.real = realPart.empty() ? 0 : stod(realPart);
    result.imag = imagPart.empty() ? 0 : stod(imagPart);
    return result;
}

// Функции для операций с комплексными числами
ComplexNumber add(const ComplexNumber& a, const ComplexNumber& b) {
    return { a.real + b.real, a.imag + b.imag };
}

ComplexNumber subtract(const ComplexNumber& a, const ComplexNumber& b) {
    return { a.real - b.real, a.imag - b.imag };
}

ComplexNumber multiply(const ComplexNumber& a, const ComplexNumber& b) {
    return {
        a.real * b.real - a.imag * b.imag,  // Действительная часть
        a.real * b.imag + a.imag * b.real   // Мнимая часть
    };
}

ComplexNumber divide(const ComplexNumber& a, const ComplexNumber& b) {
    double denominator = b.real * b.real + b.imag * b.imag;
    if (denominator == 0) {
        throw invalid_argument("Error: division by zero.");
    }
    return {
        (a.real * b.real + a.imag * b.imag) / denominator,  // Действительная часть
        (a.imag * b.real - a.real * b.imag) / denominator   // Мнимая часть
    };
}

// Функция для выбора операции
ComplexNumber chooseOperation(const ComplexNumber& a, const string& op, const ComplexNumber& b) {
    if (op == "+") {
        return add(a, b);
    }
    else if (op == "-") {
        return subtract(a, b);
    }
    else if (op == "*") {
        return multiply(a, b);
    }
    else if (op == "/") {
        return divide(a, b);
    }
    else {
        throw invalid_argument("Incorrect operation.");
    }
}

// Основная функция для работы с комплексными числами
void ComplexOperation(const string& input1, const string& operation, const string& input2) {
    try {
        ComplexNumber num1 = parseComplex(input1);
        ComplexNumber num2 = parseComplex(input2);

        ComplexNumber result = chooseOperation(num1, operation, num2);

        cout << "Result: " << result.real;
        if (result.imag >= 0) cout << "+";
        cout << result.imag << "i" << endl;

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}