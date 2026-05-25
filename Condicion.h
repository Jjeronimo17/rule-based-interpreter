//
// Created by USUARIO on 23/05/2026.
//

#ifndef PROYECTOFINAL_CONDICION_H
#define PROYECTOFINAL_CONDICION_H
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// Clase base abstracta de toda condicion. No guarda datos, solo define la interfaz comun.
// Metodos virtuales puros: cada hija los implementa (polimorfismo).

class Condicion {
public:
    virtual void imprimir() = 0;
    virtual bool evaluar(unordered_map<string,int>& variables, unordered_set<string>& hechos) = 0;
    virtual string aTexto() = 0;
    virtual ~Condicion() {}
};


#endif //PROYECTOFINAL_CONDICION_H