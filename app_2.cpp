#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include "data/classes/Intrebare.cpp"
#include "data/classes/Test.cpp"
using namespace std;

void logCommand(const string &command) {
    ofstream logFile("data/rulare.txt", ios::app);
    if (logFile.is_open()) {
        logFile << command << endl;
        logFile.close();
    } else {
        cerr << "Nu s-a putut deschide fisierul de log." << endl;
    }
}
void afisare_teste(){
    ifstream inputFile("data/config.txt");
    if (!inputFile.is_open()) {
        cerr << "Eroare la deschiderea fișierului de rulare." << endl;
        return;
    }
    int nr_teste = 0;
    string line;
    inputFile >> nr_teste;
    inputFile.ignore(); 
    for (int i=0;i<nr_teste;i++){
     getline(inputFile, line);
     cout << i+1 << ".)" << line << endl;
    }
    inputFile.close();
}
void afisare_test(const string &nume_test) {
    Test test(nume_test);

    cout << "Afisare test: " << nume_test << endl;
    int n = test.getNumarIntrebari();
    for (int i = 0; i < n; i++) {
        cout << i+1 << ".)" << test.intrebari[i]->getQuestion() << endl;
    }
}

void start_test(const string &nume_test, const string &nume_persoana) {
  Test test(nume_test);
    ifstream checkFile("data/rulare.txt");
    if (checkFile.is_open() && checkFile.peek() != ifstream::traits_type::eof()) {
        cerr << "Testul este deja în desfășurare. Nu poate fi început din nou." << endl;
        checkFile.close();
        return;
    }
    checkFile.close();

    ofstream logFile("data/rulare.txt", ios::trunc);
    if (logFile.is_open()) {
        logFile << "0" << endl;
        logFile << nume_test << endl; 
        logFile << nume_persoana << endl; 
        logFile.close();
    } else {
        cerr << "Nu s-a putut deschide fisierul pentru scriere." << endl;
    }

    cout << "Start test: " << nume_test << " pentru " << nume_persoana << endl;
    cout << 1 << ".)" << test.intrebari[0]->getQuestion() << endl;
}

void cancel_test() {
    ofstream logFile("data/rulare.txt", ios::trunc);
    if (logFile.is_open()) {
        logFile.close();
    }
    cout << "Test a fost anulat" << endl;
}

void restart_test() {
    ifstream inputFile("data/rulare.txt");
    if (!inputFile.is_open()) {
        cerr << "Eroare la deschiderea fișierului de rulare." << endl;
        return;
    }

    int index_intrebare_curenta;
    inputFile >> index_intrebare_curenta; 
    inputFile.ignore();
    string nume_test, nume_persoana;
    getline(inputFile, nume_test);
    getline(inputFile, nume_persoana);
    inputFile.close();

    ofstream logFile("data/rulare_temp.txt", ios::trunc);
    if (logFile.is_open()) {
        logFile << 0 << endl; 
        logFile << nume_test << endl; 
        logFile << nume_persoana << endl; 
        logFile.close();

        if (remove("data/rulare.txt") != 0) {
            cerr << "Eroare la ștergerea fișierului de rulare original." << endl;
            return;
        }
        if (rename("data/rulare_temp.txt", "data/rulare.txt") != 0) {
            cerr << "Eroare la redenumirea fișierului temporar." << endl;
            return;
        }
Test test(nume_test);
        cout << "Test a fost restartat" << endl;
        cout << 1 << ".)" << test.intrebari[0]->getQuestion() << endl;
    } else {
        cerr << "Nu s-a putut deschide fisierul pentru rescriere." << endl;
    }
}

void go_to_question(int nr_intrebare) {
    ifstream inputFile("data/rulare.txt");
    if (!inputFile.is_open()) {
        cerr << "Eroare la deschiderea fișierului de rulare." << endl;
        return;
    }
    nr_intrebare--;
    int index_intrebare_curenta;
    inputFile >> index_intrebare_curenta; 
    inputFile.ignore();
    string nume_test, nume_persoana;
    getline(inputFile, nume_test);
    getline(inputFile, nume_persoana);
    inputFile.close();
    
    Test test(nume_test);
    int n = test.getNumarIntrebari();
    
    if (nr_intrebare >= 0 && nr_intrebare < n) {
        cout << nr_intrebare+1  << ".) " << test.intrebari[nr_intrebare]->getQuestion() << endl;
    } else {
        cout << "Nu există întrebarea cu numărul " << nr_intrebare+1 << "." << endl;
    }
}

void back_question() {
    ifstream inputFile("data/rulare.txt");
    if (!inputFile.is_open()) {
        cerr << "Eroare la deschiderea fișierului de rulare." << endl;
        return;
    }
    vector<string> lines;
    string line;
    while (getline(inputFile, line)) {
        lines.push_back(line);
    }
    inputFile.close();

    if (lines.size() < 3) {
        cerr << "Fișierul nu conține suficiente linii pentru a efectua operația." << endl;
        return;
    }
    int nr_intrebari_raspunse = stoi(lines[0]);
    if (nr_intrebari_raspunse <= 0) {
        cerr << "Nu se poate reduce numărul întrebărilor răspunse sub 0." << endl;
        return;
    }
    lines[0] = to_string(nr_intrebari_raspunse - 1);
    lines.pop_back();
    lines.pop_back();
    ofstream tempFile("data/rulare_temp.txt");
    if (!tempFile.is_open()) {
        cerr << "Eroare la deschiderea fișierului temporar pentru scriere." << endl;
        return;
    }

    for (const string& l : lines) {
        tempFile << l << endl;
    }
    tempFile.close();

    if (remove("data/rulare.txt") != 0) {
        cerr << "Eroare la ștergerea fișierului original." << endl;
        return;
    }
    if (rename("data/rulare_temp.txt", "data/rulare.txt") != 0) {
        cerr << "Eroare la redenumirea fișierului temporar." << endl;
        return;
    }

    cout << "Întoarcere la întrebarea anterioară." << endl;
}

void next_question() {
    ifstream inputFile("data/rulare.txt");
    if (!inputFile.is_open()) {
        cerr << "Eroare la deschiderea fișierului de rulare." << endl;
        return;
    }

    int nr_intrebari_raspunse = 0;
    inputFile >> nr_intrebari_raspunse;
    inputFile.ignore();
    string nume_test, nume_persoana;
    getline(inputFile, nume_test);
    getline(inputFile, nume_persoana);
    inputFile.close();

    Test test(nume_test);
    int n = test.getNumarIntrebari();

    if (nr_intrebari_raspunse < n) {
        int index_intrebare_curenta = nr_intrebari_raspunse;
        nr_intrebari_raspunse++;
        ofstream tempFile("data/rulare_temp.txt");
        if (tempFile.is_open()) {
            tempFile << nr_intrebari_raspunse << endl;
            tempFile << nume_test << endl;
            tempFile << nume_persoana << endl;
            ifstream inputFile("data/rulare.txt");
            string line;
            getline(inputFile, line);
            getline(inputFile, line);
            getline(inputFile, line);

            while (getline(inputFile, line)) {
                tempFile << line << endl;
            }
            tempFile << index_intrebare_curenta << endl;
            tempFile << 0 << endl;

            inputFile.close();
            tempFile.close();
            if (remove("data/rulare.txt") != 0) {
                cerr << "Eroare la ștergerea fișierului original." << endl;
                return;
            }
            if (rename("data/rulare_temp.txt", "data/rulare.txt") != 0) {
                cerr << "Eroare la redenumirea fișierului temporar." << endl;
                return;
            }
            if (nr_intrebari_raspunse < n) {
                cout << nr_intrebari_raspunse + 1 << ".) " << test.intrebari[nr_intrebari_raspunse]->getQuestion() << endl;
            } else {
                cout << "Testul a fost finalizat." << endl;
            }
        } else {
            cerr << "Nu s-a putut deschide fișierul temporar pentru scriere." << endl;
            return;
        }
    } else {
        cout << "Toate întrebările au fost deja răspunse." << endl;
    }
}

void end_test(const string &nume_test) {
    cout << "Salvare date test: " << nume_test << endl;
    logCommand("end_test " + nume_test);
}


void answer(const string &raspuns) {
    ifstream inputFile("data/rulare.txt");
    if (!inputFile.is_open()) {
        cerr << "Eroare la deschiderea fișierului de rulare." << endl;
        return;
    }

    int nr_intrebari_raspunse = 0;
    inputFile >> nr_intrebari_raspunse;
    inputFile.ignore();
    string nume_test, nume_persoana;
    getline(inputFile, nume_test);
    getline(inputFile, nume_persoana);
    inputFile.close();

    Test test(nume_test);
    int n = test.getNumarIntrebari();

    if (nr_intrebari_raspunse < n) {
        int index_intrebare_curenta = nr_intrebari_raspunse;
        nr_intrebari_raspunse++;
        ofstream tempFile("data/rulare_temp.txt");
        if (tempFile.is_open()) {
            tempFile << nr_intrebari_raspunse << endl;
            tempFile << nume_test << endl;
            tempFile << nume_persoana << endl;
            ifstream inputFile("data/rulare.txt");
            string line;
            getline(inputFile, line);
            getline(inputFile, line);
            getline(inputFile, line);

            while (getline(inputFile, line)) {
                tempFile << line << endl;
            }
            tempFile << index_intrebare_curenta << endl;
            tempFile << raspuns << endl;

            inputFile.close();
            tempFile.close();
            if (remove("data/rulare.txt") != 0) {
                cerr << "Eroare la ștergerea fișierului original." << endl;
                return;
            }
            if (rename("data/rulare_temp.txt", "data/rulare.txt") != 0) {
                cerr << "Eroare la redenumirea fișierului temporar." << endl;
                return;
            }
            if (nr_intrebari_raspunse < n) {
                cout << nr_intrebari_raspunse + 1 << ".) " << test.intrebari[nr_intrebari_raspunse]->getQuestion() << endl;
            } else {
                cout << "Testul a fost finalizat." << endl;
            }
        } else {
            cerr << "Nu s-a putut deschide fișierul temporar pentru scriere." << endl;
            return;
        }
    } else {
        cout << "Toate întrebările au fost deja răspunse." << endl;
    }
}

void correct_answer() {
    ifstream inputFile("data/rulare.txt");
    if (!inputFile.is_open()) {
        cerr << "Eroare la deschiderea fișierului de rulare." << endl;
        return;
    }

    int nr_intrebari_raspunse = 0;
    inputFile >> nr_intrebari_raspunse;
    inputFile.ignore(); 
    string nume_test;
    getline(inputFile, nume_test);
    inputFile.close();
    Test test(nume_test);
    cout << "Raspuns corect:\n" <<test.intrebari[nr_intrebari_raspunse]->getRaspuns()<< endl;
}

void progress() {
     ifstream inputFile("data/rulare.txt");
    if (!inputFile.is_open()) {
        cerr << "Eroare la deschiderea fișierului de rulare." << endl;
        return;
    }
    int nr_intrebari_raspunse = 0;
    inputFile >> nr_intrebari_raspunse;
    inputFile.ignore(); 
    string nume_test;
    getline(inputFile, nume_test);
    inputFile.close();
    Test test(nume_test);
    cout << "Progress:" <<nr_intrebari_raspunse<<" din "<<test.getNumarIntrebari()<< endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Utilizare: " << argv[0] << " <comanda> [argumente]" << endl;
        return 1;
    }
    string command(argv[1]);

    if (command == "afisare_test" && argc == 3) {
        afisare_test(argv[2]);
    } else if (command == "start_test" && argc == 4) {
        start_test(argv[2], argv[3]);
    } else if (command == "cancel_test") {
        cancel_test();
    }else if (command == "afisare_teste") {
        afisare_teste();
    } else if (command == "restart_test") {
        restart_test();
    } else if (command == "go_to_question" && argc == 3) {
        go_to_question(atoi(argv[2]));
    } else if (command == "back_question") {
        back_question();
    } else if (command == "next_question") {
        next_question();
    } else if (command == "end_test" && argc == 3) {
        end_test(argv[2]);
    } else if (command == "answer" && argc == 3) {
        answer(argv[2]);
    } else if (command == "correct_answer") {
        correct_answer();
    } else if (command == "progress") {
        progress();
    } else {
        cerr << "Comanda necunoscuta sau argumente incorecte." << endl;
        return 1;
    }

    return 0;
}