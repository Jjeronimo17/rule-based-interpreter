//
// Created by USUARIO on 23/05/2026.
//

#ifndef PROYECTOFINAL_AND_H
#define PROYECTOFINAL_AND_H
#include <string>
#include <memory>
#include <iostream>
#include "Condicion.h"
using namespace std;

// Condicion de tipo AND: conjuncion de dos condiciones. Guarda punteros a sus dos hijos.

class And : public Condicion {
public:
    unique_ptr<Condicion> izquierda;
    unique_ptr<Condicion> derecha;

    And(unique_ptr<Condicion> iz, unique_ptr<Condicion> der) : izquierda(move(iz)), derecha(move(der)) {}


    // Delega en los hijos, la recursion recorre el arbol.
    void imprimir() override {
        izquierda->imprimir();
        cout << " AND ";
        derecha->imprimir();
    }


    // Verdadero solo si ambos hijos lo son.
    bool evaluar(unordered_map<string, int> &variables, unordered_set<string> &hechos) override {
        if (izquierda->evaluar(variables, hechos) && derecha->evaluar(variables, hechos)) {
            return true;
        }
        return false;
    }

    string aTexto() override {
        return izquierda->aTexto() + "AND" + derecha->aTexto();
    }
};


#endif //PROYECTOFINAL_AND_H