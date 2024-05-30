#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;



class Test{
    string nume;
    string path;
    int nr_intrebari;

public:
    vector<Intrebare*> intrebari;
    Test(const string& nume): nume(nume) {
        path = "data/teste/"+nume;
        ifstream f(path+"/test.txt");
        if(!f.is_open()){
            cout << "Acest test nu exista!";
            return;
        }

        char tip;
        string variante[5];
        int varianta_corecta;
        string raspuns_corect, intrebarea;

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

    string getName(){return nume;}
    string getPath(){return path;}
    int getNumarIntrebari(){return nr_intrebari;}
};
