#include <iostream>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13

class Intrebare{
protected:
    string intrebare;
    int numar;

public:
    string getQuestion(){return intrebare;}
    int getNumber(){return numar;}

    Intrebare(string intrebare, int nr): intrebare(intrebare), numar(nr){}

};

class IntrebareGrila: public Intrebare{
    char raspuns;
public:
    void display(){
        cout << intrebare;
    }

};

class IntrebareText: public Intrebare{
    string raspuns;

};

class Test{
    string nume;
    string path;
    int nr_intrebari;
    vector<Intrebare*> intrebari;
public:
    string getName(){return nume;}
    string getPath(){return path;}
    int getNumarIntrebari(){return nr_intrebari;}
    Test(string nume, int nr_intrebari): nume(nume), nr_intrebari(nr_intrebari){path = "data\\"+nume+"\\test.txt";}


    void creazaTest(){
        
    }
};

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
        cout << setColour("---== "+title+" ==---\n", "cyan");
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
