//
// Created by USUARIO on 24/05/2026.
//

#ifndef PROYECTOFINAL_INTERPRETE_H
#define PROYECTOFINAL_INTERPRETE_H
#include "Programa.h"
using namespace std;


// Interprete: ejecuta el programa por punto fijo.
class Interprete {
public:
    // Aplica las reglas repetidamente hasta que no se activen hechos nuevos.
    // El estado va por referencia (unico y compartido). do-while: minimo una pasada.
    void ejecutar(Programa& programa, unordered_map<string, int >& variables, unordered_set<string>& hechos) {
        bool cambio;
        do {
            cambio = false; // se reinicia cada pasada
            for (const auto& regla : programa.reglas) {
                if (regla->condicion->evaluar(variables, hechos)) {
                    auto resultado = hechos.insert(regla->accion);
                    if (resultado.second) {  // .second: true si el hecho era nuevo
                        cambio = true;
                    }
                }
            }
        } while (cambio);
    }





};


#endif //PROYECTOFINAL_INTERPRETE_H