//
// Created by USUARIO on 23/05/2026.
//

#ifndef PROYECTOFINAL_PROGRAMA_H
#define PROYECTOFINAL_PROGRAMA_H
#include <vector>
#include "NodoRule.h"
using namespace std;

// Nodo raiz del AST: lista de todas las reglas del programa.

class Programa {
public:
    vector<unique_ptr<NodoRule>> reglas;
};


#endif //PROYECTOFINAL_PROGRAMA_H