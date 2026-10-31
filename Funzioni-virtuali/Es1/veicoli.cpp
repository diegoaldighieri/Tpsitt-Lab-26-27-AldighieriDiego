#include <iostream>
using namespace std;

class Veicolo {
public:
    void descrivi() const { cout << "Veicolo generico" << endl; }
    virtual void suono() const { cout << "..." << endl; }
};

class Auto : public Veicolo {
public:
    void descrivi() const { cout << "Automobile" << endl; }
    void suono() const override { cout << "Beep beep" << endl; }
};

class Moto : public Veicolo {
public:
    void descrivi() const { cout << "Motocicletta" << endl; }
    void suono() const override { cout << "Vroom" << endl; }
};

void presenta(Veicolo v) {
    v.descrivi();
    v.suono();
}

void presentaRif(const Veicolo& v) {
    v.descrivi();
    v.suono();
}

int main() {
    Auto a;
    Moto m;

    Veicolo* p = &a;
    p->descrivi();              // * (1) Veicolo generico
    p->suono();                 // * (2) Beep beep

    p = &m;
    p->descrivi();              // * (3) Veicolo generico
    p->suono();                 // * (4) Vroom

    presenta(m);                // * (5) Veicolo generico  (6) ...
    presentaRif(m);             // * (7) Veicolo generico  (8) Vroom

    a.descrivi();               // * (9) Automobile
    return 0;
}

// Tipo statico di p: Veicolo*. Tipo dinamico: Auto in 1 e 2, Moto in 3 e 4.
// descrivi usa il binding statico, suono il binding dinamico.
// 6 e 8 sono diverse per lo slicing: presenta riceve una copia che è solo un Veicolo.
