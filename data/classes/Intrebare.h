#pragma once

#include <string>

class Intrebare{
protected:
    std::string intrebare;

public:
    std::string getQuestion();

    Intrebare(std::string intrebare);

    static std::string toLowerCase(const std::string& str);
    virtual bool checkAnswer(std::string answer);
    virtual bool checkAnswer(int answer);
    
    virtual std::string getRaspuns();
    virtual std::ofstream& addFile(std::ofstream& f);
};

class IntrebareGrila: public Intrebare{
    int raspuns;
    std::string variante[5];
public:
    IntrebareGrila(std::string intrebare, int corect, std::string var[]);

    bool checkAnswer(std::string answer);
    bool checkAnswer(int answer);

    std::ofstream& addFile(std::ofstream& f);

    std::string getRaspuns();
};

class IntrebareText: public Intrebare{
    std::string raspuns;

public:
    IntrebareText(std::string intrebare, std::string corect);

    bool checkAnswer(std::string answer);

    std::string getRaspuns();

    std::ofstream& addFile(std::ofstream& f);
};