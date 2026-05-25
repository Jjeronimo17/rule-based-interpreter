//
// Created by USUARIO on 24/05/2026.
//

#ifndef PROYECTOFINAL_ENTRADA_H
#define PROYECTOFINAL_ENTRADA_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
using namespace std;

// Entrada: separa reglas del estado inicial y carga el estado.

class Entrada {

public:

    string recortar(const string& s) {
        size_t inicio = s.find_first_not_of(" \t");
        if (inicio == string::npos) return "";
        size_t fin = s.find_last_not_of(" \t");
        return s.substr(inicio, fin - inicio + 1);
    }

    // Parte la entrada usando "State:" como frontera: reglas arriba, estado abajo.

    void separarEntrada(const string& textoCompleto, string& textoReglas, vector<string>& lineasEstado) {
        stringstream flujo(textoCompleto);
        string linea;
        bool enEstado = false;

        while (getline(flujo, linea)) {
            if (recortar(linea) == "State:") {
                enEstado = true;
            } else if (enEstado) {
                lineasEstado.push_back(linea);
            } else {
                textoReglas += linea + "\n";
            }
        }
    }

    // Lee cada linea del estado: 'id = num' es variable, 'id' solo es hecho.

    void leerEstado(const vector<string>& lineasEstado, unordered_map<string, int>& variables, unordered_set<string>& hechos) {
        for (const string& linea : lineasEstado) {
            if (linea.empty()) continue;
            stringstream flujo(linea);
            string id;
            flujo >> id;

            char igual;
            if (flujo >> igual && igual == '=') {
                int valor;
                flujo >> valor;
                variables[id] = valor;
            } else {
                hechos.insert(id);
            }
        }
    }


};


#endif //PROYECTOFINAL_ENTRADA_H