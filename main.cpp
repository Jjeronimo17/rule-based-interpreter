#include <iostream>
#include <string>
#include <algorithm>
#include "Analisis.h"
#include "Entrada.h"
#include "Interprete.h"
#include "Lexer.h"
#include "Parser.h"

//Metodo para imprimir el nodo de regla

   void imprimirRule(NodoRule& regla) {
       cout << "Rule: " << regla.nombre << "\n";
       cout << "  Condicion: ";
       regla.condicion->imprimir();
       cout << "\n";
       cout << "  Accion: " << regla.accion << "\n";
   }


    void imprimirAST(Programa& programa) {
        cout << "=== AST ===\n";
        for (const auto& regla : programa.reglas) {
            imprimirRule(*regla);
        }
    }

void imprimirResultado(const unordered_set<string>& hechos) {
       if (hechos.empty()) {
           cout << "(no output)" << endl;
           return;
       }
       vector<string> ordenados(hechos.begin(), hechos.end());
       sort(ordenados.begin(), ordenados.end());
       for (const string& h : ordenados) {
           cout << h << endl;
       }
   }



int main() {
       Analisis analisis;

       Entrada entrada;


       string textoCompleto, linea;
       while (getline(cin, linea)) textoCompleto += linea + "\n";


       string textoReglas;
       vector<string> lineasEstado;
       entrada.separarEntrada(textoCompleto, textoReglas, lineasEstado);


       Lexer lexer(textoReglas);
       Parser parser(lexer);

       try {
           Programa programa = parser.parseProgram();


           unordered_map<string,int> variables;
           unordered_set<string> hechos;
           entrada.leerEstado(lineasEstado, variables, hechos);


           Interprete interprete;
           interprete.ejecutar(programa, variables, hechos);


           imprimirResultado(hechos);
           analisis.detectarConflictos(programa);
           analisis.detectarRedundancias(programa);
           analisis.detectarInactivas(programa, variables, hechos);

       } catch (const runtime_error& e) {
           cout << e.what() << endl;
       }
       return 0;
   }

