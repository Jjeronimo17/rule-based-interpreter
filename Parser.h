//
// Created by USUARIO on 21/05/2026.
//

#ifndef PROYECTOFINAL_PARSER_H
#define PROYECTOFINAL_PARSER_H
#include "And.h"
#include "Comparacion.h"
#include "Condicion.h"
#include "Hecho.h"
#include "Lexer.h"
#include "NodoRule.h"
#include <vector>

#include "Programa.h"


/*GRAMÁTICA TRANSFORMADA A LL(1) (la que implementa este parser):
--------------------------------------------------------------------------
  Program  -> RuleList
  RuleList -> Rule RuleList | e
  Rule     -> rule id : if Cond then Action
  Cond     -> Atom Cond'
  Cond'    -> AND Atom Cond' | e        (elimina recursión izquierda)
  Atom     -> id Atom'
  Atom'    -> RelOp value | e           (factorización por la izquierda)
  RelOp    -> > | < | =
  Action   -> id

( e = epsilon = cadena vacía )
*/





class Parser {
private:
    Lexer& lexer;
    Token tokenActual;



    void avanzar() {
        tokenActual = lexer.next();
    }

public:



    Parser(Lexer& lex) : lexer(lex) {
        avanzar();
    }

// Metodo para consumir el token si concide con el que estamos esperando

    void match(TokenType esperado) {
        if (tokenActual.type == esperado) {
            avanzar();
        } else {
            throw runtime_error("Error de sintaxis en linea " + to_string(tokenActual.linea) + ": token inesperado");
        }
    }

// Nueve metodos. Hacen referencia a las reglas de produccion. Importante mencionar que fueron cambiadas para eliminar recursiones por izquierda o abstracciones
// Terminales como tokens, no-terminales se llama al metodo que simula su regla de produccion.

    // Metodo que simula la regla de produccion de rule
    // Tambien construye el Nodo de rule con sus tres datos: nombre, condicion y accion.

    unique_ptr<NodoRule> parseRule() {
        match(TokenType::RULE);
        string nombre = tokenActual.lexema;
        match(TokenType::ID);
        match(TokenType::COLON);
        match(TokenType::IF);
        unique_ptr<Condicion> cond = parseCond();
        match(TokenType::THEN);
        string accion = parseAction();
        return make_unique<NodoRule>(nombre, move(cond), accion);
    }

    // Metodo que simula la regla de produccion de Cond

    unique_ptr<Condicion> parseCond() {
        unique_ptr<Condicion>izquierda = parseAtom();
        return parseCondTail(move(izquierda));
    }

    // Metodo que simula la regla de produccion de Cond' Necesario porque se elimino la recursividad izquierda original que tenia Cond.
    // Recibe la condicion izquierda y decide: Si existe un and crea el nodo con la condicion izquierda y derecha. De lo contrario solo crea el nodo con la condicion original
    // Si existen mas and se llama asi mismo para crear los nodos
    // Decisión LL(1): si el token actual es AND (FIRST de la alternativa no vacía)
    // tomamos 'AND Atom Cond''; si no, aplicamos epsilon (el token está en FOLLOW).

    unique_ptr <Condicion> parseCondTail(unique_ptr <Condicion> izquierda) {
        if (tokenActual.type == TokenType::AND) {
            match(TokenType::AND);
            unique_ptr <Condicion> derecha = parseAtom();
            unique_ptr <Condicion> nodoAnd = make_unique<And>(move(izquierda), move(derecha));
            return parseCondTail(move(nodoAnd));
        }
        return izquierda;
    }

    // Metodo que simula la regla de produccion de Atom. Retorna el nodo que construyo parseAtomTail con el id capturado. Necesario para el AST

    unique_ptr<Condicion> parseAtom() {
        string id = tokenActual.lexema;
        match(TokenType::ID);
        return parseAtomTail(id);
    }

    // Metodo que simula la regla de produccion de Atom' nuevamente necesario para eliminar la recursividad por la izquierda original de Atom.
    // A su vez crea el nodo con el id, el operador y el valor ( ej : temp > 30). Tambien crea el nodo de un hecho(Si corresponde)

    unique_ptr<Condicion> parseAtomTail(string idLeido){
        if (tokenActual.type == TokenType::GT || tokenActual.type == TokenType::LT || tokenActual.type == TokenType::EQ) {
            string op = tokenActual.lexema;
            parseRelOp();
            int valor = stoi(tokenActual.lexema);
            match(TokenType::VALUE);
            return make_unique<Comparacion>(idLeido, op, valor);
        }
        return make_unique<Hecho>(idLeido);
    }

    // Metodo que simula la regla de produccion de Rel0p

    void parseRelOp() {
        if (tokenActual.type == TokenType::GT) {
            match(TokenType::GT);
        } else if (tokenActual.type == TokenType::LT) {
            match(TokenType::LT);
        } else if (tokenActual.type == TokenType::EQ) {
            match(TokenType::EQ);
        } else {
            throw runtime_error("Error de sintaxis en linea " + to_string(tokenActual.linea) + ": se esperaba un operador relacional");
        }
    }

    // Metodo que simula la regla de produccion de Action

    string parseAction() {
        string accion = tokenActual.lexema;
        match(TokenType::ID);
        return accion;
    }

    // Metodo que simula la regla de produccion de ruleList
    // Recibe un vector donde se iran almacenando de manera recursiva la lista de reglas del programa

    void parseRuleList(vector<unique_ptr<NodoRule>>& reglas) {
        if (tokenActual.type == TokenType::RULE) {
            reglas.push_back(parseRule());
            parseRuleList(reglas);
        }
    }

    // Metodo que simula la regla de produccion de Program

    Programa parseProgram() {
        Programa programa;
        parseRuleList(programa.reglas);
        match(TokenType::END_OF_FILE);   // verifica que no sobra entrada tras las reglas ($ del análisis LL(1))
        return programa;
    }




};



#endif //PROYECTOFINAL_PARSER_H