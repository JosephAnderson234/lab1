#include <iostream>
#include "token.h"

using namespace std;

// -----------------------------
// Constructores
// -----------------------------

Token::Token(Type type) 
    : type(type), text("") { }

Token::Token(Type type, char c) 
    : type(type), text(string(1, c)) { }

Token::Token(Type type, const string& source, int first, int last) 
    : type(type), text(source.substr(first, last)) { }

// -----------------------------
// Sobrecarga de operador <<
// -----------------------------

// Para Token por referencia
ostream& operator<<(ostream& outs, const Token& tok) {
    switch (tok.type) {
        case Token::PLUS:   outs << "TOKEN(PLUS, \""   << tok.text << "\")"; break;
        case Token::MINUS:  outs << "TOKEN(MINUS, \""  << tok.text << "\")"; break;
        case Token::MUL:    outs << "TOKEN(MUL, \""    << tok.text << "\")"; break;
        case Token::DIV:    outs << "TOKEN(DIV, \""    << tok.text << "\")"; break;
        case Token::NUM:    outs << "TOKEN(NUM, \""    << tok.text << "\")"; break;
        case Token::POW:    outs << "TOKEN(POW, \""    << tok.text << "\")"; break;
        case Token::IDENTIFIER: outs << "TOKEN(IDENTIFIER, \"" << tok.text << "\")"; break;
        case Token::ASSIGN: outs << "TOKEN(ASSIGN, \"" << tok.text << "\")"; break;
        case Token::SQRT:   outs << "TOKEN(SQRT, \""   << tok.text << "\")"; break;
        case Token::ERR:    outs << "TOKEN(ERR, \""    << tok.text << "\")"; break;
        case Token::END:    outs << "TOKEN(END)"; break;
        case Token::SIN: outs << "TOKEN(SIN, \"" << tok.text << "\")"; break;
        case Token::COS: outs << "TOKEN(COS, \"" << tok.text << "\")"; break;
        case Token::LOG: outs << "TOKEN(LOG, \"" << tok.text << "\")"; break;
        case Token::OPREL: outs << "TOKEN(OPREL, \"" << tok.text << "\")"; break;
        case Token::BIN: outs << "TOKEN(BIN, \"" << tok.text << "\")"; break;
        case Token::BOOL: outs << "TOKEN(BOOL, \"" << tok.text << "\")"; break;
    }
    return outs;
}

// Para Token puntero
ostream& operator<<(ostream& outs, const Token* tok) {
    if (!tok) return outs << "TOKEN(NULL)";
    return outs << *tok;  // delega al otro
}