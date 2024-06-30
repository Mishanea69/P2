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
             IntrebareGrila* grila = dynamic_cast<IntrebareGrila*>(test.intrebari[i]);
        if (grila != nullptr) {
            for (int j = 1; j <= 4; j++) {
                cout << "    " << char('A' + j - 1) << ". " << grila->getRaspuns(j) << std::endl;
            }
}
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
        logFile << "0" << endl;
        logFile.close();
    } else {
        cerr << "Nu s-a putut deschide fisierul pentru scriere." << endl;
    }

    cout << "Start test: " << nume_test << " pentru " << nume_persoana << endl;
    cout << 1 << ".)" << test.intrebari[0]->getQuestion() << endl;
    IntrebareGrila* grila = dynamic_cast<IntrebareGrila*>(test.intrebari[0]);
        if (grila != nullptr) {
            for (int j = 0; j <= 4; j++) {
                cout << "    " << char('A' + j - 1) << ". " << grila->getRaspuns(j) << endl;
            }
}
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
 inputFile.seekg(0, ios::end);
    if (inputFile.tellg() == 0) {
        cerr << "Nu exista niciun test inceput pentru a fi restartat." << endl;
        inputFile.close();
        return;
    }
    inputFile.seekg(0, ios::beg);
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
        logFile << 0 << endl;
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
        IntrebareGrila* grila = dynamic_cast<IntrebareGrila*>(test.intrebari[0]);
        if (grila != nullptr) {
            for (int j = 1; j <= 4; j++) {
                cout << "    " << char('A' + j - 1) << ". " << grila->getRaspuns(j) << endl;
            }
}
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
     inputFile.seekg(0, ios::end);
    if (inputFile.tellg() == 0) {
        cerr << "Nu exista niciun test inceput." << endl;
        inputFile.close();
        return;
    }
    inputFile.seekg(0, ios::beg);
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
         IntrebareGrila* grila = dynamic_cast<IntrebareGrila*>(test.intrebari[nr_intrebare]);
        if (grila != nullptr) {
            for (int j = 1; j <= 4; j++) {
                cout << "    " << char('A' + j - 1) << ". " << grila->getRaspuns(j) << std::endl;
            }
}
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

    inputFile.seekg(0, ios::end);
    if (inputFile.tellg() == 0) {
        cerr << "Nu exista niciun test inceput." << endl;
        inputFile.close();
        return;
    }
    inputFile.seekg(0, ios::beg);

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
    string nume_test = lines[1];
    string nume_persoana = lines[2];

    if (nr_intrebari_raspunse <= 0) {
        cerr << "Nu se poate reduce numărul întrebărilor răspunse sub 0." << endl;
        return;
    }

    lines[0] = to_string(nr_intrebari_raspunse - 1);
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

    Test test(nume_test);
    int n = test.getNumarIntrebari();

    int current_question_index = nr_intrebari_raspunse - 1;
    if (current_question_index < n) {
        cout << current_question_index + 1 << ".) " << test.intrebari[current_question_index]->getQuestion() << endl;
        IntrebareGrila* grila = dynamic_cast<IntrebareGrila*>(test.intrebari[current_question_index]);
        if (grila != nullptr) {
            for (int j = 1; j <= 4; j++) {
                cout << "    " << char('A' + j - 1) << ". " << grila->getRaspuns(j) << endl;
            }
        }
    } else {
        cout << "Testul a fost finalizat." << endl;
    }
}

void next_question() {
    ifstream inputFile("data/rulare.txt");
    if (!inputFile.is_open()) {
        cerr << "Eroare la deschiderea fișierului de rulare." << endl;
        return;
    }
         inputFile.seekg(0, ios::end);
    if (inputFile.tellg() == 0) {
        cerr << "Nu exista niciun test inceput." << endl;
        inputFile.close();
        return;
    }
    inputFile.seekg(0, ios::beg);
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
    Test test(nume_test);
    int n = test.getNumarIntrebari();
    IntrebareGrila* grila = dynamic_cast<IntrebareGrila*>(test.intrebari[nr_intrebari_raspunse]);
    IntrebareText* text = dynamic_cast<IntrebareText*>(test.intrebari[nr_intrebari_raspunse]);
             if (grila != nullptr) {
                tempFile << "G 0 0";
            } else {
                tempFile << "T 0 0";
            }
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
                IntrebareGrila* grila = dynamic_cast<IntrebareGrila*>(test.intrebari[nr_intrebari_raspunse]);
        if (grila != nullptr) {
            for (int j = 1; j <= 4; j++) {
                cout << "    " << char('A' + j - 1) << ". " << grila->getRaspuns(j) << std::endl;
            }
}
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
    ifstream inputFile("data/rulare.txt");
    if (!inputFile.is_open()) {
        cerr << "Eroare la deschiderea fișierului de rulare." << endl;
        return;
    }
     inputFile.seekg(0, ios::end);
    if (inputFile.tellg() == 0) {
        cerr << "Nu exista niciun test inceput." << endl;
        inputFile.close();
        return;
    }
    inputFile.seekg(0, ios::beg);
    string line;
    getline(inputFile, line);
    string nume_file;
    if (!getline(inputFile, nume_file)) {
        cerr << "Eroare la citirea numelui fișierului." << endl;
        inputFile.close();
        return;
    }
    string data;
    while (getline(inputFile, line)) {
        data += line + "\n";
    }
    inputFile.close();
    string statsFilePath = "data/teste/" + nume_test + "/stats.txt";
    ofstream statsFile(statsFilePath, ios::app);
    if (!statsFile.is_open()) {
        cerr << "Eroare la deschiderea fișierului de statistici." << endl;
        return;
    }
    statsFile << data;
    statsFile.close();
    ofstream logFile("data/rulare.txt", ios::trunc);
    if (logFile.is_open()) {
        logFile.close();
    }
    cout << "Salvare date test: " << nume_test << endl;
}


void answer(const string &raspuns) {
    ifstream inputFile("data/rulare.txt");
    if (!inputFile.is_open()) {
        cerr << "Eroare la deschiderea fișierului de rulare." << endl;
        return;
    }
         inputFile.seekg(0, ios::end);
    if (inputFile.tellg() == 0) {
        cerr << "Nu exista niciun test inceput." << endl;
        inputFile.close();
        return;
    }
    inputFile.seekg(0, ios::beg);
    int nr_intrebari_raspunse = 0, raspunsuri_corecte = 0;
    inputFile >> nr_intrebari_raspunse;
    inputFile.ignore();
    string nume_test, nume_persoana;
    getline(inputFile, nume_test);
    getline(inputFile, nume_persoana);
    inputFile >> raspunsuri_corecte;
    inputFile.close();

    Test test(nume_test);
    int n = test.getNumarIntrebari();
    IntrebareGrila* grila = dynamic_cast<IntrebareGrila*>(test.intrebari[nr_intrebari_raspunse]);
    IntrebareText* text = dynamic_cast<IntrebareText*>(test.intrebari[nr_intrebari_raspunse]);
    stringstream ss(raspuns);
    
    if (nr_intrebari_raspunse < n) {
        int index_intrebare_curenta = nr_intrebari_raspunse;
        nr_intrebari_raspunse++;

        if (grila != nullptr) {
            int num = 0;
            if (!(ss >> num)) {
                raspunsuri_corecte = raspunsuri_corecte;
            } else {
                if (grila->checkAnswer(stoi(raspuns)) == 1) {
                    raspunsuri_corecte++;
                }
            }
        }

        if (text != nullptr) {
            if (text->checkAnswer(raspuns) == 1) {
                raspunsuri_corecte++;
            }
        }

        ofstream tempFile("data/rulare_temp.txt");
        if (tempFile.is_open()) {
            tempFile << nr_intrebari_raspunse << endl;
            tempFile << nume_test << endl;
            tempFile << nume_persoana << endl;
            tempFile << raspunsuri_corecte << endl;

            ifstream inputFile("data/rulare.txt");
            string line;
            getline(inputFile, line);
            getline(inputFile, line);
            getline(inputFile, line);
            getline(inputFile, line);
            while (getline(inputFile, line)) {
                tempFile << line << endl;
            }
            
            if (grila != nullptr) {
                tempFile << "G" << " ";
            } else {
                tempFile << "T" << " ";
            }

            if (grila != nullptr) {
                if (raspuns=="1"||raspuns=="2"||raspuns=="3"||raspuns=="4") {
                    tempFile << grila->checkAnswer(stoi(raspuns)) << " ";
                } else {
                     tempFile << 0 << " ";
                }
            }

            if (text != nullptr) {
                tempFile << text->checkAnswer(raspuns) << " ";
            }

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
                if (grila != nullptr) {
                    for (int j = 0; j < 4; j++) {
                        cout << "    " << char('A' + j) << ". " << grila->getRaspuns(j) << endl;
                    }
                }
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
inputFile.seekg(0, ios::end);
    if (inputFile.tellg() == 0) {
        cerr << "Nu exista niciun test inceput." << endl;
        inputFile.close();
        return;
    }
    inputFile.seekg(0, ios::beg);
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
    inputFile.seekg(0, ios::end);
    if (inputFile.tellg() == 0) {
        cerr << "Nu exista niciun test inceput." << endl;
        inputFile.close();
        return;
    }
    inputFile.seekg(0, ios::beg);
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