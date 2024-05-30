#include <iostream>
#include <fstream>
using namespace std;

class Intrebare{
protected:
    string intrebare;

public:
    string getQuestion(){return intrebare;}

    Intrebare(string intrebare): intrebare(intrebare){}

    static string toLowerCase(const string& str) {
        string result = str;
        for (size_t i = 0; i < result.size(); ++i) {
            if (result[i] >= 'A' && result[i] <= 'Z') {
                result[i] = result[i] + ('a' - 'A');
            }
    }
    return result;
}
    virtual bool checkAnswer(string answer){return false;}
    
    virtual string getRaspuns(){return "";}
    virtual ofstream& addFile(ofstream& f){return f;}
};

class IntrebareGrila: public Intrebare{
    int raspuns;
    string variante[5];
public:
    IntrebareGrila(string intrebare, int corect, string var[]): Intrebare(intrebare), raspuns(corect){
        for(int i=0; i<5; i++) variante[i]=var[i];
    }

    bool checkAnswer(string answer){
        if(answer==variante[0]) return true; 
        else return false;
    }
    bool checkAnswer(int answer){
        if(variante[0]==variante[answer]) return true;
        else return false;
    }

    ofstream& addFile(ofstream& f){
        f << "G " << raspuns << endl;
        f << variante[1] << endl;
        f << variante[2] << endl;
        f << variante[3] << endl;
        f << variante[4] << endl;
        return f;
    }

    string getRaspuns(){return variante[0];}
};

class IntrebareText: public Intrebare{
    string raspuns;

public:
    IntrebareText(string intrebare, string corect): Intrebare(intrebare), raspuns(corect){}

    bool checkAnswer(string answer){
        bool check=false;
        if(Intrebare::toLowerCase(answer) == Intrebare::toLowerCase(raspuns)) check = true;
        return check;
    }

    string getRaspuns(){return raspuns;}

    ofstream& addFile(ofstream& f){
        f << "T " << raspuns << endl;
        return f;
    }
};