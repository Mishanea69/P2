#pragma once

#include "Intrebare.h"
#include <vector>
#include <string>

class Test{
    std::string nume;
    std::string path;
    int nr_intrebari;

public:
    std::vector<Intrebare*> intrebari;
    Test(const std::string& nume);

    std::string getName();
    std::string getPath();
    int getNumarIntrebari();

    void saveTest();

    void removeQuestion(int ord);

    void addQuestion(std::string intrebare, std::string raspuns);
    void addQuestion(std::string intrebare, int raspuns, std::string variante[5]);
};
