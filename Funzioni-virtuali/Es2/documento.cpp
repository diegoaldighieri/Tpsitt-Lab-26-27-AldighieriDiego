#include <iostream>
using namespace std;

class Documento {
public:
    Documento() { cout << "Costruttore Documento" << endl; }
    virtual ~Documento() { cout << "Distruttore Documento" << endl; }   // * aggiunto virtual
    virtual void stampa() const { cout << "Documento vuoto" << endl; }
};

class Lettera : public Documento {
    int* righe; // memoria allocata dinamicamente
public:
    Lettera() {
        righe = new int[100];
        cout << "Costruttore Lettera (alloco 100 righe)" << endl;
    }
    ~Lettera() {
        delete[] righe;
        cout << "Distruttore Lettera (libero 100 righe)" << endl;
    }
    void stampa() const override { cout << "Gentile cliente, ..." << endl; }
};

int main() {
    Documento* d = new Lettera();   // * Costruttore Documento, Costruttore Lettera
    d->stampa();                    // * Gentile cliente, ...
    delete d;                       // * Distruttore Lettera, Distruttore Documento
    return 0;
}

// Senza virtual il warning è: deleting object of polymorphic class type 'Documento'
// which has non-virtual destructor might cause undefined behavior.
// Viene chiamato solo ~Documento, ~Lettera non parte e restano 400 byte (100 * 4).
// Con virtual i distruttori vanno al contrario dei costruttori: prima Lettera, poi Documento.
