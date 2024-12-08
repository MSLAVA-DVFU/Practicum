#include <iostream>
#include <fstream>
#include <string>
#include "quadratic.h"  // Подключаем файл для работы с квадратными уравнениями
#include "complex.h"    // Подключаем файл для работы с комплексными числами

using namespace std;

int main() {
    //Выбор способа ввода
    cout << "Choose input method: (1 - keyboard, 2 - file): ";
    int input_mode;
    cin >> input_mode;
    cin.ignore(); // Очистка буфера
    // Выбор задачи
    int choice;
    cout << "Choose mode: 1 - quadratic equation, 2 - complex numbers: ";
    cin >> choice;
    cin.ignore(); // Очистка буфера
    if (choice == 1) {
        string equation;
        if (input_mode == 1) {
            cout << "Input quadratic equation like ax2+bx+c: ";
            getline(cin, equation);
            solveQuadraticEquation(equation);
        }
        else if (input_mode == 2) {
            cout << "Input filename: ";
            string filename;
            cin >> filename;
            ifstream file(filename);
            if (!file) {
                cerr << "Error: failed to open file." << endl;
                return 1;
            }
            getline(file, equation);
            solveQuadraticEquation(equation);
            file.close();
        }
        else {
            cerr << "Incorrect choice." << endl;
            return 1;
        }
    }
    else if (choice == 2) {
        string input1, operation, input2;
        if (input_mode == 1) {
            cout << "Input first complex number (a+bi): ";
            getline(cin, input1);
            cout << "Input operation (+, -, *, /): ";
            getline(cin, operation);
            cout << "Input second complex number (a+bi): ";
            getline(cin, input2);
            ComplexOperation(input1, operation, input2);
        }
        else if (input_mode == 2) {
            cout << "Input filename: ";
            string filename;
            cin >> filename;
            ifstream file(filename);
            if (!file) {
                cerr << "Error: failed to open file." << endl;
                return 1;
            }
            getline(file, input1);
            getline(file, operation);
            getline(file, input2);
            ComplexOperation(input1, operation, input2);
            file.close();
        }
        else {
            cerr << "Incorrect choice." << endl;
            return 1;
        }
    }
    else {
        cout << "Incorrect choice." << endl;
    }

    return 0;
}