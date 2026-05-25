//
// Created by USUARIO on 23/05/2026.
//

#ifndef PROYECTOFINAL_COMPARACION_H
#define PROYECTOFINAL_COMPARACION_H
#include <string>
#include <memory>
#include <iostream>

#include "Condicion.h"
using namespace std;

// Condicion de tipo comparacion: id operador valor (ej. temp > 30). Guarda los tres datos.


class Comparacion : public Condicion {
public:
    string identificador;
    string operador;
    int valor;

    Comparacion (string id, string op, int valor) : identificador(id), operador(op), valor(valor){}

    void imprimir() override {
        cout << identificador << " " << operador << " " << valor;
    }

    // Busca la variable y comprueba la comparacion. Si no existe la variable, false.

    bool evaluar(unordered_map<string, int> &variables, unordered_set<string> &hechos) override {
        if (variables.count(identificador) == 0) {
            return false;
        }
        int valorVariable = variables.at(identificador);
        if (operador == ">") {
            return valorVariable > valor;
        } else if (operador == "<") {
            return valorVariable < valor;
        } else if (operador == "=") {
            return valorVariable == valor;
        }
        return false;
    }

    string aTexto() override {
        return identificador + operador + to_string(valor);
    }
};


#endif //PROYECTOFINAL_COMPARACION_H