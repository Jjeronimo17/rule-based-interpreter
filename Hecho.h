//
// Created by USUARIO on 23/05/2026.
//

#ifndef PROYECTOFINAL_HECHO_H
#define PROYECTOFINAL_HECHO_H
#include <string>
#include <memory>
#include <iostream>
#include "Condicion.h"
using namespace std;

// Condicion de tipo hecho: un identificador solo (ej. alert). Solo guarda su nombre.

class Hecho : public Condicion {
public:
    string identificador;

    Hecho(string id) : identificador(id) {}

    void imprimir() override {
        cout << identificador;
    }

    // Verdadero si el hecho esta en el conjunto de hechos activos. Solo consulta.

    bool evaluar(unordered_map<string, int> &variables, unordered_set<string> &hechos) override {
            return hechos.count(identificador) > 0;
    }

    string aTexto() override {
        return identificador;
    }
};


#endif //PROYECTOFINAL_HECHO_H