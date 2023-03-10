#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include "json.hpp"
using json = nlohmann::json;

class Human {
public:
    Human() {}
    Human(std::string name_, std::string surname_, size_t age_, double height_, double weight_) :
        name(name_), surname(surname_), age(age_), height(height_), weight(weight_) {}

    json create_json() {
        json data = {
            {"name", name},
            {"surname", surname},
            {"age", age},
            {"height", height},
            {"weight", weight},
        };

        return data;
    }

    friend std::istream& operator>>(std::istream& is, Human& obj);
    friend std::ostream& operator<<(std::ostream& os, const Human& obj);

private:
    std::string name = "None";
    std::string surname = "None";
    size_t age = -1;
    double height = -1.0;
    double weight = -1.0;
};

std::istream& operator>>(std::istream& is, Human& obj) {
    std::cout << "Ввод параметров:" << std::endl;

    std::cout << "name: ";
    std::cin >> obj.name;

    std::cout << "surname: ";
    std::cin >> obj.surname;

    std::cout << "age: ";
    std::cin >> obj.age;

    std::cout << "height: ";
    std::cin >> obj.height;

    std::cout << "weight: ";
    std::cin >> obj.weight;

    return is;
}

std::ostream& operator<<(std::ostream& os, const Human& obj) {
    std::cout << "Human parametrs:" << std::endl;
    std::cout << "name: " << obj.name << std::endl;
    std::cout << "surname: " << obj.surname << std::endl;
    std::cout << "age: " << obj.age << std::endl;
    std::cout << "height: " << obj.height << std::endl;
    std::cout << "weight: " << obj.weight << std::endl;

    return os;
}

int main() {
    std::filesystem::path folder = "data";

    Human man;
    Human woman;

    std::cin >> man;
    std::cout << std::endl;
    std::cin >> woman;

    std::filesystem::create_directories(folder);

    std::fstream man_file(folder/"man.json", std::ios::out);
    man_file << man.create_json();
    man_file.close();

    std::fstream woman_file(folder/"woman.json", std::ios::out);
    woman_file << woman.create_json();
    woman_file.close();

    return 0;
}
