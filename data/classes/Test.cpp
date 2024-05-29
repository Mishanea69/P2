#include <string>
using namespace std;

class Test{
    string nume;
    string path;
    int nr_intrebari;

public:
    Test(const string& nume): nume(nume) {this->path = "data\\"+nume;}
    string getName(){return nume;}
    string getPath(){return path;}
    int getNumarIntrebari(){return nr_intrebari;}

    void creazaTest(){}
};
