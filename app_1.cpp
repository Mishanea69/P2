#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include "data/classes/Test.cpp"
#include "data/classes/Intrebare.cpp"


using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13

//Make a string coloured 
string setColour(string str, string colour){
    if(colour == "red"){
        str = "\033[0;31m"+str+"\033[0m";
    } else
    if(colour == "green"){
        str = "\033[0;32m"+str+"\033[0m";
    } else
    if(colour == "yellow"){
        str = "\033[0;33m"+str+"\033[0m";
    } else
    if(colour == "blue"){
        str = "\033[0;34m"+str+"\033[0m";
    } else
    if(colour == "purple"){
        str = "\033[0;35m"+str+"\033[0m";
    } else
    if(colour == "cyan"){
        str = "\033[0;36m"+str+"\033[0m";
    } else
    if(colour == "white"){
        str = "\033[0;37m"+str+"\033[0m";
    } else
    if(colour == "black"){
        str = "\033[0;30m"+str+"\033[0m";
    }
    return str;

}

//Display an interactive Page that returns the selection
int front_hilight;
string InteractivePage(string title, const string menu[], int list_size, bool back_button = false){
    int selection = front_hilight;
    auto showPage = [&](){
        system("cls");
        cout << setColour("---=="+title+"==---\n", "cyan");
        for(int i=0; i<list_size; i++){
            if(selection == i) cout << setColour(">>"+menu[i], "red") << endl;
            else cout << menu[i] << endl;
        }
        if(back_button){
            cout << endl;
            if(selection == list_size) cout << setColour("<--[Back]", "red") << endl;
            else cout << "[Back]" << endl;
        }

        cout << "\n\n";
    };

    showPage(); int ch;
    while ((ch = getch()) != ENTER) {
        if (ch == 0 || ch == 224)
        switch (getch()) {
            case KEY_UP:
                if(selection > 0) {
                    selection--;
                }
                break;
            case KEY_DOWN:
                if(selection < list_size) {
                    selection++;
                    if(!back_button && selection==list_size) selection--;
                }
                break;
        }
        showPage();
    }
    system("cls");
    front_hilight = selection;
    if(selection<list_size) return menu[selection];
    else return "";
}
string RightPanel(string left_title, const string left_menu[], int left_list_size, string title, const string menu[], int list_size){
    int selection = 0;
    auto showPage = [&](){
        int space = 20;
        system("cls");
        cout << setColour("---=="+left_title+"==---", "cyan"); space-=10+left_title.length();
        for(int c=1; c<=space; c++) cout << ' '; cout << "| ";
        cout << setColour("---=="+title+"==---\n", "cyan");

        for(int i=0; i<list_size; i++){
            space = 20;
            
            if(i<left_list_size){
                if(front_hilight == i) cout << setColour(left_menu[i], "green");
                else cout << left_menu[i]; space-=left_menu[i].length();
            } 
            for(int c=1; c<=space; c++) cout << ' '; cout << "| ";
            
            if(selection == i) cout << setColour(">>"+menu[i], "red") << endl;
            else cout << menu[i] << endl;
        }
        for(int c=1; c<=space; c++) cout << ' '; cout << "| \n";
        for(int c=1; c<=space; c++) cout << ' '; cout << "| ";
        if(selection==list_size) cout << setColour("<--[Cancel]", "red");
        else cout << "[Cancel]";

        cout << "\n\n";
    };

    showPage(); int ch;
    while ((ch = getch()) != ENTER) {
        if (ch == 0 || ch == 224)
        switch (getch()) {
            case KEY_UP:
                if(selection > 0) {
                    selection--;
                }
                break;
            case KEY_DOWN:
                if(selection <= list_size) {
                    selection++;
                }
                break;
        }
        showPage();
    }
    system("cls");
    if(selection<list_size) return menu[selection];
    else return "";
}

bool ConfirmationPrompt(string question){
    int ch; 
    int pos=0;
    auto ShowPage = [&](){
        if(pos==0){
            system("cls");
            cout << setColour(question, "cyan") << endl << endl;
            cout << setColour("[No]", "green") << "    [Yes]";
        } else {
            system("cls");
            cout << setColour(question, "cyan") << endl << endl;
            cout  << "[No]    " << setColour("[Yes]", "red");
        }
    };

    ShowPage();
    while ((ch = getch()) != ENTER) {
        switch (getch()) {
            case 75:
                if(pos) {
                    pos = 0;
                }
                break;
            case 77:
                if(!pos) {
                    pos = 1;
                }
                break;
        }
        
        ShowPage();
    }
    return pos;
}


int main(int argc, char* argv[]){
    cout << Intrebare::toLowerCase("ASA ceva eu nu AM Vazut!");


    
    return 0;
}