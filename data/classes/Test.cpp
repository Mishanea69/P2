#include "Test.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


std::string sendError(std::string str){
    return "\033[0;31m"+str+"\033[0m";
}

Test::Test(const std::string& nume): nume(nume) {
    path = "data/teste/"+nume;
    std::ifstream f(path+"/test.txt");
    if(!f.is_open()){
        std::cout << "Acest test nu exista!";
        return;
    }

    char tip;
    std::string variante[5];
    int varianta_corecta;
    std::string raspuns_corect, intrebarea;

    f >> nr_intrebari; f.ignore();
    for(int i=0; i<nr_intrebari; i++){
        getline(f, intrebarea);
        f >> tip;
        if(tip=='G'){
            f >> varianta_corecta; f.ignore();
            for(int j=1; j<=4; j++){
                getline(f, variante[j]);
            } variante[0]=variante[varianta_corecta];
            intrebari.push_back(new IntrebareGrila(intrebarea,varianta_corecta, variante));
        } else {
            f.ignore(); getline(f,raspuns_corect);
            intrebari.push_back(new IntrebareText(intrebarea, raspuns_corect));
        }
    }

    f.close();
}

std::string Test::getName(){return nume;}
std::string Test::getPath(){return path;}
int Test::getNumarIntrebari(){return nr_intrebari;}

void Test::saveTest(){
    std::ofstream f(path+"/test.txt");
    f << nr_intrebari << std::endl;
    for(int i=0; i<nr_intrebari; i++){
        f << intrebari[i]->getQuestion() << std::endl;
        intrebari[i]->addFile(f);
    }

    f.close();
}

void Test::removeQuestion(int ord){
    if (!intrebari.empty()) {
        if(ord<1 || ord>nr_intrebari) {
            std::cout << sendError("Testul nu contie intrebare cu acest numar!\n");
            return;
        }
        intrebari.erase(intrebari.begin()+ord-1);
        nr_intrebari--;
        saveTest();
    } else {
        std::cout << sendError("Testul nu are nici o intrebare!\n");
    }
}

void Test::addQuestion(std::string intrebare, std::string raspuns){
    intrebari.push_back(new IntrebareText(intrebare, raspuns));
    nr_intrebari++;
    saveTest();
}
void Test::addQuestion(std::string intrebare, int raspuns, std::string variante[5]){
    intrebari.push_back(new IntrebareGrila(intrebare, raspuns, variante));
    nr_intrebari++;
    saveTest();
}