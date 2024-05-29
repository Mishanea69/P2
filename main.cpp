#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <conio.h>
#include "student1.cpp"
#include "student2.cpp"
using namespace std;


string menu[] = {"View Tests", "Create New Test", "Exit"};
string actions[] = {"Start Test", "Rename Test", "Edit Test", "Delete Test", "View Stats"};
string tests[20];

vector<Test> teste;
int nrTeste;

void TestMenu(){
    string selection, action;
    while(1){
        selection = InteractivePage("Tests", tests, nrTeste, true);
        if(selection=="") break;
        else {
            action = RightPanel("Tests", tests, nrTeste, "Actions", actions, 5);
            if(action=="Start Test"){
                Test_execute(tests[front_hilight]);
            }
        }
    }
    front_hilight = 0;
}

void Menu(){
    string selection;
    while(1){
        selection = InteractivePage(" Main Menu ", menu, 3);
        if(selection=="View Tests"){
            TestMenu();
        } else
        if(selection=="Exit"){
            if(ConfirmationPrompt("Are you sure?")) break;
        }
    }
}

void saveConfig(){
    ofstream file("data\\config.txt");
    file << teste.size() << endl;
    for(int i=0; i<teste.size(); i++){
        file << teste[i].getName() << endl;
        tests[i]=teste[i].getName();
    }

    file.close();
}
void setup(){
    ifstream file("data\\config.txt");
    string str;

    file >> nrTeste; file.ignore();
    for(int i=0; i<nrTeste; i++){
        getline(file, str);
        tests[i] = str;
        teste.emplace_back(str);
    }

    file.close();
}

int main()
{
    setup();
    Menu();
    return 0;
}