#include <iostream>
using namespace std;

class Intrebare{
protected:
    string intrebare;
    int numar;

public:
    string getQuestion(){return intrebare;}
    int getNumber(){return numar;}

    Intrebare(string intrebare, int nr): intrebare(intrebare), numar(nr){}

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

};

class IntrebareGrila: public Intrebare{
    string raspuns;
    string variante[4];
public:
    bool checkAnswer(string answer){return true;}

};

class IntrebareText: public Intrebare{
    string raspuns;

public:
    bool checkAnswer(string answer){
        bool check=false;
        if(Intrebare::toLowerCase(answer) == Intrebare::toLowerCase(raspuns)) check = true;
        return check;
    }
};