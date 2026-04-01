#include <iostream>
#include <cstring>
#include <fstream>
#include "token.h"
#include "scanner.h"

using namespace std;

// -----------------------------
// Constructor
// -----------------------------
Scanner::Scanner(const char* s): input(s), first(0), current(0) { 
    }

// -----------------------------
// Función auxiliar
// -----------------------------

bool is_white_space(char c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

// -----------------------------
// nextToken: obtiene el siguiente token
// -----------------------------



/* Token* Scanner::nextToken() {
    Token* token;

    // Saltar espacios en blanco
    while (current < input.length() && is_white_space(input[current])) 
        current++;

    // Fin de la entrada
    if (current >= input.length()) 
        return new Token(Token::END);

    char c = input[current];

    first = current;

    // Números
    if (isdigit(c)) {
        current++;
        while (current < input.length() && isdigit(input[current]))
            current++;
        token = new Token(Token::NUM, input, first, current - first);
    }

    // Operadores
    else if (strchr("+/-*", c)) {
        switch (c) {
            case '+': token = new Token(Token::PLUS,  c); break;
            case '-': token = new Token(Token::MINUS, c); break;
            case '*': token = new Token(Token::MUL,   c); break;
            case '/': token = new Token(Token::DIV,   c); break;
        }
        current++;
    }

    // Carácter inválido
    else {
        token = new Token(Token::ERR, c);
        current++;
    }

    return token;
}
 */


Token* Scanner::nextToken() {
    Token* token;
    char c;
    state = 0;
    first = current;
    string lexema;

    while (1) {
        switch (state) {
            case 0: 
                c = nextChar();
                if (is_white_space(c)) { first = current; state = 0; }
                //for me 
                //im gonna add support for comments
                else if (c == '#'){
                    while (c != '\n' && c != '\0') c = nextChar();
                    first = current;
                    state = 0;
                } else if (c == '0') state = 14; // para el caso de BIN (0b)

                else if (c == '\0') return new Token(Token::END);
                else if(isalpha(c)) state = 11; // para el caso de identificadores
                else if (c == '(') state = 1;
                else if (c == ')') state = 2;
                else if (c == '+') state = 3;
                else if (c == '-') state = 4;
                else if (c == '*') state = 10;
                else if (c == '/') state = 6;
                else if (c == '=') state = 13;
                else if (c == '!') state = 17;
                else if (c == '<') state = 18;
                else if (c == '>') state = 19;
                else if (isdigit(c)) state = 8;
                else return new Token(Token::ERR, c);
                break;

            case 1: return new Token(Token::LPAREN, '(');
            case 2: return new Token(Token::RPAREN, ')');
            case 3: return new Token(Token::PLUS, c);
            case 4: return new Token(Token::MINUS, c);
            
            
            case 6: return new Token(Token::DIV, c);

            case 8: 
                c = nextChar();
                if (isdigit(c)) state = 8;
                else state = 9;
                break;

            case 9: 
                rollBack();
                return new Token(Token::NUM, input, first, current - first);
            case 10:
                return new Token(Token::MUL, c);
            
            case 11:
                c = nextChar();
                if (isalnum(c)) state = 11;
                else state = 12;
                break;
            case 12:
                rollBack();
                lexema = input.substr(first, current - first);
                if (lexema == "sqrt"){
                    return new Token(Token::SQRT, input, first, current - first);
                } else if (lexema == "sin"){
                    return new Token(Token::SIN, input, first, current - first);
                } else if (lexema == "cos"){
                    return new Token(Token::COS, input, first, current - first);
                } else if (lexema == "log"){
                    return new Token(Token::LOG, input, first, current - first);
                } else if (lexema == "True"){
                    return new Token(Token::TRUE, input, first, current - first);
                } else if (lexema == "False"){
                    return new Token(Token::FALSE, input, first, current - first);
                }
                
                return new Token(Token::IDENTIFIER, input, first, current - first);
            case 13:
                c = nextChar();
                if (c == '=') {
                    return new Token(Token::EQUAL, input, first, current - first);
                }
                return new Token(Token::ASSIGN,input, first, current - first);
            //For me
            case 14:
                c = nextChar();
                if (c == 'b') state = 15; // para el caso de BIN (0b)
                else if (isdigit(c)) {
                    rollBack();
                    state = 8; // para el caso de NUM que empieza con 0
                } else {
                    rollBack();
                    return new Token(Token::NUM, input, first, current - first);
                }
                break;
            case 15:
                c = nextChar();
                if (c == '0' || c == '1') state = 15;
                else state = 16;
                break; 
            case 16:
                rollBack();
                return new Token(Token::BIN, input, first, current - first);
            case 17:
                c = nextChar();
                if (c == '=') {
                    return new Token(Token::NOT_EQUAL, c);
                }
                return new Token(Token::ERR, c);
            case 18:
                return new Token(Token::LESS_THAN, c);
            case 19:
                return new Token(Token::GREATER_THAN, c);
        }

        
    }
}


void Scanner::rollBack() {
    if (input[current] != '\0')
        current--;
}

char Scanner::nextChar() {
    int c = input[current];
    if (c != '\0') current++;
    return c;
}



// -----------------------------
// Destructor
// -----------------------------
Scanner::~Scanner() { }

// -----------------------------
// Función de prueba
// -----------------------------

void ejecutar_scanner(Scanner* scanner, const string& InputFile) {
    Token* tok;

    // Crear nombre para archivo de salida
    string OutputFileName = InputFile;
    size_t pos = OutputFileName.find_last_of(".");
    if (pos != string::npos) {
        OutputFileName = OutputFileName.substr(0, pos);
    }
    OutputFileName += "_tokens.txt";

    ofstream outFile(OutputFileName);
    if (!outFile.is_open()) {
        cerr << "Error: no se pudo abrir el archivo " << OutputFileName << endl;
        return;
    }

    outFile << "Iniciando Scanner para archivo: " << InputFile << endl << endl;

    while (true) {
        tok = scanner->nextToken();

        if (tok->type == Token::END) {
            outFile << *tok << endl;
            delete tok;
            outFile << "\nScanner exitoso" << endl << endl;
            outFile.close();
            return;
        }

        if (tok->type == Token::ERR) {
            outFile << *tok << endl;
            delete tok;
            outFile << "Caracter invalido" << endl << endl;
            outFile << "Scanner no exitoso" << endl << endl;
            outFile.close();
            return;
        }

        outFile << *tok << endl;
        delete tok;
    }
}
