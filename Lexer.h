//
// Created by USUARIO on 20/05/2026.
//

#ifndef PROYECTOFINAL_LEXER_H
#define PROYECTOFINAL_LEXER_H
#include <iostream>
#include <string>
using namespace std;

// Clase son los tipos de tokens

enum class TokenType {
    RULE, IF, THEN, AND,
    COLON, GT, LT, EQ,
    ID, VALUE,
    END_OF_FILE,
    ERROR
};

// Estructura del token, contiene su tipo, el lexema y la linea y columna para reportar errores.

struct Token {
    TokenType type;
    string lexema;
    int linea;
    int columna;
};

// Contiene las funciones principales del analizador lexico o lexer.

class Lexer {
private:
    size_t indice;
    int linea;
    int columna;
    string text;


public:
    Lexer (string fuente) : text(fuente), linea(1), columna(1), indice(0) {

    }

    // metodo que devuelve el caracter actual. No hace nada con el solo lo mira. Lo utilizamos para saber cual estamos procesando

    char peek() const {
        if (indice < text.size()) {
            return text[indice];
        } else {
            return '\0';
        }
    }

    // metodo que consume el caracter y avanza el indice.

    char advance() {
        if (indice >= text.size()) {
            return '\0';
        }
        char actual = peek();
        if (actual == '\n') {
            linea++;
            columna = 1;
        } else {
            columna++;
        }
        indice++;
        return actual;
    }

    //Metodo que se encarga de ignorar espacios en blanco, necesario porque en el enunciado se establece

    void whitespace() {
        for (;peek() == ' ' || peek() == '\t' || peek() == '\n';) {
            advance();
        }
    }

// Recorremos toda la plabra sin importar si la palabra tiene digitos, letras o "_". En classifyWord es donde hacemos la distincion y clasificamos en keyword o identifier

    Token scanWord() {
        string lexema = "";
        for (;isalpha(peek()) || isdigit(peek()) || peek() =='_';) {
            lexema += advance();
        }
        return classifyWord(lexema);
    }

// Verficamos si la palabra construida coincide exactamente con las palabras de nuestra ENUM class, de no hacerlo hacemos validaciones de identifier y retonarnamos token

    Token classifyWord(string lexema) {
        if (lexema == "rule") {
            return Token{TokenType::RULE, lexema, linea, columna};
        }
        if (lexema == "if") {
            return Token{TokenType::IF, lexema, linea, columna};
        }
        if (lexema == "then") {
            return Token{TokenType::THEN, lexema, linea, columna};
        }
        if (lexema == "AND") {
            return Token{TokenType::AND, lexema, linea, columna};
        }
        if (!islower(lexema[0])) {
            return Token{TokenType::ERROR, lexema, linea, columna};
        }
        for (size_t i = 1; i < lexema.size(); i++) {
            if (!(islower(lexema[i]) || isdigit(lexema[i]) || lexema[i] == '_')) {
                return Token{TokenType::ERROR, lexema, linea, columna};
            }
        }
        return Token{TokenType::ID, lexema, linea, columna};
    }

// Metodo que construye el lexema solo con numeros si se encarga de retornar el token de VALUE

    Token scanNumber() {
        string lexema = "";
        for (;isdigit(peek());) {
            lexema += advance();
        }
        return Token{TokenType::VALUE, lexema, linea, columna};
    }

// Metodo que dependiendo del operator retorna su TOKEN correspondiente

    Token scanOperator() {
        char ad = advance();
        switch (ad) {
            case ':':
                return Token{TokenType::COLON, ":", linea, columna};
            case '>':
                return Token{TokenType::GT, ">", linea, columna};
            case '<':
                return Token{TokenType::LT, "<", linea, columna};
            case '=':
                return Token{TokenType::EQ, "=", linea, columna};
            default:
                return Token{TokenType::ERROR, "", linea, columna};
        }
    }

// Es el metodo que devuelve todos los TOKENS presentes en la palabra, comienza ignorando espacios en blanco y va llamando a los diferentes metodos segun corresponda

    Token next() {
        whitespace();
        char c = peek();
        if (isalpha(c) || c == '_' ) {
            return scanWord();
        }
        if (isdigit(c)) {
            return scanNumber();
        }
        if (c == ':' || c == '=' || c == '>' || c == '<') {
            return scanOperator();
        }
        if (c == '\0') {
            return Token{TokenType::END_OF_FILE, "", linea, columna};
        }
        advance();
        return Token{TokenType::ERROR, string(1, c), linea, columna};
    }






};








#endif //PROYECTOFINAL_LEXER_H