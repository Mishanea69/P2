#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <initializer_list>
#include "student1.cpp"
#include "student2.cpp"
using namespace std;


string menu[] = {"View Tests", "Create New Test", "Exit"};

void Menu(){
    string selection;
    while(1){
        selection = InteractivePage("Main Menu", menu, 3);
        if(selection=="Exit"){
            if(ConfirmationPrompt("Are you sure?")) break;
        }
    }
}


int main()
{
    Menu();
    return 0;
}