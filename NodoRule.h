//
// Created by USUARIO on 23/05/2026.
//
#ifndef PROYECTOFINAL_NODORULE_H
#define PROYECTOFINAL_NODORULE_H
#include <memory>
#include "Condicion.h"
using namespace std;

// Nodo regla del AST: nombre, condicion y accion.
class NodoRule {
public:
    string nombre;
    unique_ptr<Condicion> condicion;
    string accion;

    NodoRule(string n, unique_ptr<Condicion> c, string acc) : nombre(n), condicion(move(c)), accion(move(acc)) {}
};


#endif //PROYECTOFINAL_NODORULE_H