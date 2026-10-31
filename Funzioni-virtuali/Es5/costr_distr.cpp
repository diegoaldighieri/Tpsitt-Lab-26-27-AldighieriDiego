#include <iostream>
using namespace std;

class Base {
public:
    Base() { cout << "B+ "; }
    virtual ~Base() { cout << "B- "; }
    virtual void f() const { cout << "Base::f "; }
    void g() const { cout << "Base::g "; f(); }
};

class Der : public Base {
public:
    Der() { cout << "D+ "; }
    ~Der() override { cout << "D- "; }
    void f() const override { cout << "Der::f "; }
    void g() const { cout << "Der::g "; f(); }
};

void perValore(Base b) { b.f(); }
void perPuntatore(const Base* p) { p->g(); }

int main() {
    {
        cout << "[1] "; Der d;             cout << endl;    // * B+ D+
        cout << "[2] "; perValore(d);      cout << endl;    // * Base::f B-
        cout << "[3] "; perPuntatore(&d);  cout << endl;    // * Base::g Der::f
        cout << "[4] "; d.g();             cout << endl;    // * Der::g Der::f
        cout << "[5] "; Base* p = new Der();                // * B+ D+
                        p->g();                             // * Base::g Der::f
                        delete p;          cout << endl;    // * D- B-
        cout << "[6] "; Base b = d;
                        b.g();             cout << endl;    // * Base::g Base::f
        cout << "[7] ";
    }                                                       // * B- D- B-
    cout << endl;
    return 0;
}

// [2] è la copia b del parametro, creata col costruttore di copia che non stampa niente.
// [3] e [4]: g non è virtual quindi conta il tipo statico, f è virtual quindi è sempre Der::f.
// [7] distrugge b e poi d, al contrario di come sono stati creati.
