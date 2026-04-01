#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <ostream>

using namespace std;

class Token {
public:
    // Tipos de token
    enum Type {
        PLUS,    // +
        MINUS,   // -
        MUL,     // *
        DIV,     // /
        POW,     // ^
        LPAREN,  // (
        RPAREN,  // )
        IDENTIFIER, // identificadores
        ASSIGN, // =
        NUM,     // Número
        SQRT, // raíz cuadrada
        ERR,     // Error
        END ,     // Fin de entrada

        //FOR ME
        SIN,
        COS,
        LOG,
        LESS_THAN,
        GREATER_THAN,
        EQUAL,
        NOT_EQUAL,
        TRUE,
        FALSE,
        BIN,
    };

    // Atributos
    Type type;
    string text;

    // Constructores
    Token(Type type); // for error and end 
    Token(Type type, char c); //for individual characters like +, -, *, /, (, )
    Token(Type type, const string& source, int first, int last);  // for numbers "1231321" and in the identifiers "var1", etc. or binary true or false

    // Sobrecarga de operadores de salida
    friend ostream& operator<<(ostream& outs, const Token& tok);
    friend ostream& operator<<(ostream& outs, const Token* tok);
};

#endif // TOKEN_H