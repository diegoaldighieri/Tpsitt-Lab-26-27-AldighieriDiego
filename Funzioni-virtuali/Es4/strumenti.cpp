#include <iostream>
#include <string>
using namespace std;

class Strumento {
public:
    string nome() const { return "strumento"; }
    virtual string suono() const { return "..."; }
    virtual int corde() const { return 0; }
    void presentati() const {
        cout << nome() << " fa " << suono()
             << " con " << corde() << " corde" << endl;
    }
};

class Chitarra : public Strumento {
public:
    string nome() const { return "chitarra"; }
    string suono() const override { return "dlin"; }
    int corde() const override { return 6; }
};

class ChitarraElettrica : public Chitarra {
public:
    string nome() const { return "chitarra elettrica"; }
    string suono() const override { return "dzzz"; }
    // corde() non viene ridefinito
};

int main() {
    ChitarraElettrica e;
    Chitarra c;

    Strumento* s = &e;
    s->presentati();                 // * (1) strumento fa dzzz con 6 corde

    Chitarra* pc = &e;
    cout << pc->nome() << endl;      // * (3) chitarra
    cout << pc->suono() << endl;     // * dzzz

    Strumento& r = c;
    r.presentati();                  // * (4) strumento fa dlin con 6 corde

    Strumento copia = e;
    copia.presentati();              // * (5) strumento fa ... con 0 corde

    e.presentati();                  // * (6) strumento fa dzzz con 6 corde
    cout << e.nome() << endl;        // * (7) chitarra elettrica
    return 0;
}

// Nella 1 corde è quella di Chitarra, perché ChitarraElettrica la eredita.
// 6 e 7 sono diverse perché dentro presentati this è uno Strumento* e nome non è virtual.
// Se nome fosse virtual cambierebbero:
// (1) chitarra elettrica fa dzzz con 6 corde
// (3) chitarra elettrica
// (4) chitarra fa dlin con 6 corde
// (6) chitarra elettrica fa dzzz con 6 corde
