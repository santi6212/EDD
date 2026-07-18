#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Miembro {
    int id;
    string name;
    string last_name;
    char gender;
    int age;
    int id_boss;
    bool is_dead;
    bool in_jail;
    bool was_boss;
    bool is_boss;

    Miembro* izquierdo = nullptr;
    Miembro* derecho = nullptr;
    Miembro* padre = nullptr;
};
