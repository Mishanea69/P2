#include "Intrebare.h"
#include <iostream>
#include <fstream>

std::string Intrebare::getQuestion(){return intrebare;}

Intrebare::Intrebare(std::string intrebare): intrebare(intrebare){}

std::string Intrebare::toLowerCase(const std::string& str) {
    std::string result = str;
    for (size_t i = 0; i < result.size(); ++i) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = result[i] + ('a' - 'A');
        }
    }
    return result;
}
bool Intrebare::checkAnswer(std::string answer){return false;}

std::string Intrebare::getRaspuns(){return "";}
std::string Intrebare::getRaspuns(int x){return "";}
std::ofstream& Intrebare::addFile(std::ofstream& f){return f;}



IntrebareGrila::IntrebareGrila(std::string intrebare, int corect, std::string var[]): Intrebare(intrebare), raspuns(corect){
    for(int i=0; i<5; i++) variante[i]=var[i];
}

bool IntrebareGrila::checkAnswer(std::string answer){
    if(answer==variante[0]) return true; 
    else return false;
}
bool IntrebareGrila::checkAnswer(int answer){
    if(variante[0]==variante[answer]) return true;
    else return false;
}

std::ofstream& IntrebareGrila::addFile(std::ofstream& f){
    f << "G " << raspuns << std::endl;
    f << variante[1] << std::endl;
    f << variante[2] << std::endl;
    f << variante[3] << std::endl;
    f << variante[4] << std::endl;
    return f;
}

std::string IntrebareGrila::getRaspuns(){return variante[0];}
std::string IntrebareGrila::getRaspuns(int x){return variante[x];}



IntrebareText::IntrebareText(std::string intrebare, std::string corect): Intrebare(intrebare), raspuns(corect){}

bool IntrebareText::checkAnswer(std::string answer){
    bool check=false;
    if(Intrebare::toLowerCase(answer) == Intrebare::toLowerCase(raspuns)) check = true;
    return check;
}

std::string IntrebareText::getRaspuns(){return raspuns;}

std::ofstream& IntrebareText::addFile(std::ofstream& f){
    f << "T " << raspuns << std::endl;
    return f;
}
