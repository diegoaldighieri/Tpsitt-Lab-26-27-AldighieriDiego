#include <iostream>

#include "../../../../../../cygwin64/lib/gcc/x86_64-pc-cygwin/14/include/c++/iostream"
#include "../../../../../../cygwin64/lib/gcc/x86_64-pc-cygwin/14/include/c++/iostream"

class Veicoli {
    public:
    virtual void Muovi() = 0;
    virtual void Descrizione() = 0;
    virtual ~Veicoli(){}
};

class Auto : public Veicoli {
    public:
    void Muovi() override {std::cout<<"L'auto accelera sul asfalto"<<std::endl;}
    void Descrizione() override{ std::cout << "Questa è un'auto"<< std::endl; }
};

class Treno : public Veicoli {
  public:
   void Muovi() override{std::cout<< "Il treno parte dal binario"<<std::endl; }
    void Descrizione() override{std::cout<<"Questo è un treno" << std::endl; }
};

class Bicicletta : public Veicoli {
  public:
    void Muovi() override{std::cout<< "La bici si pedala"<<std::endl; }
    void Descrizione() override{std::cout<<"Questo è una bici "<< std::endl; }
};

int main() {
    Veicoli* v1 = new Auto();
    Veicoli* v2 = new Bicicletta();
    Veicoli* v3 = new Treno();

    v1->Descrizione();
    v1->Muovi();

    v2->Descrizione();
    v2->Muovi();

    v3->Descrizione();
    v3->Muovi();

    delete v1;
    delete v2;
    delete v3;

    return 0;
}
