#include <iostream>
#include <vector>
using namespace std;


class Personaggio {
    public:
    virtual ~Personaggio(){};
    virtual void attacca() = 0;
    virtual void presentati() = 0;
};

class Guerriero :public Personaggio {
  public:
    void  attacca() override {std::cout<<"attacca il guerriero"<<std::endl;};
    void presentati() override {std::cout<<"presentato il guerriero"<<std::endl;};
};

class Mago :public Personaggio {
public:
    void  attacca() override {std::cout<<"attacca il mago"<<std::endl;};
    void presentati() override {std::cout<<"presentato il mago"<<std::endl;};
};

class Arciere :public Personaggio {
public:
    void  attacca() override {std::cout<<"attacca l'arciere"<<std::endl;};
    void presentati() override {std::cout<<"presentato l'arciere"<<std::endl;};
};

void turno(Personaggio *p) {
    p->attacca();
    p->presentati();
}


int main() {

    std::vector<Personaggio*> squadra;
    squadra.push_back(new Guerriero());
    squadra.push_back(new Mago());
    squadra.push_back(new Arciere());
    squadra.push_back(new Guerriero());

    for (Personaggio *p : squadra) {
        turno(p);
    }

    for (Personaggio *p : squadra) {
        delete p;
    }


    return 0;
}
