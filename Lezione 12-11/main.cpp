#include <string>
#include <iostream>

class Persona {
    int id;
    std::string nome;
public:
    Persona(const int i = 0, std::string n = "ugone") : id (i), nome (std::move(n)) {
        std::cout << "Persona" << id << "creata" << std::endl;
    }

};




int main() {

    Persona p(9, "Federico");

    return 0;

}