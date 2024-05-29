#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <initializer_list>
#include "student1.cpp"
#include "student2.cpp"
#include <fstream>
using namespace std;


string menu[] = {"View Tests", "Create New Test", "Statistici","Rulare","Exit"};
string test="./data/teste/Test1/test.txt";
void Menu(){
    string selection;
    while(1){
        selection = InteractivePage("Main Menu", menu, 4);
        if(selection=="Exit"){
            if(ConfirmationPrompt("Are you sure?")) break;
        } else if(selection=="Rulare"){
           ifTest_execute(test)
        }
    }
}


int main()
{
    Menu();
    return 0;
}