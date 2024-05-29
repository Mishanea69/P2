#include <iostream>
#include <sstream>
using namespace std;


 void Test_execute(string file_name){
        int nr_questions;
        int correct=0;
        string line,nume,answer,raspuns;
        system("cls");
        ifstream files(file_name);
        if (!files.is_open()) { 
        cerr << "Error opening the files!" << endl; 
        exit(1);
    }
        cin>>nr_questions;
        cout<<"Introduceti numele:";
        cin>>nume;
        for(int i=1;i<=nr_questions;++i){
             system("cls");
             getline(files, line);//intrebarea
             cout<<i<<"."<<line<<"\n";
             getline(files, line);//tipul
             if(line=="G"){
                getline(files, answer);//raspunsul
                for (int j=0;j<4;++j){//grila
                     getline(files, line);
                     switch (j) {
  case 1:
    cout <<"(A)"<<line;
    break;
  case 2:
    cout<<"(B)"<<line;
    break;
  case 3:
    cout<<"(C)"<<line;
    break;
  case 4:
    cout<<"(D)"<<line;
    break;
                }
cout<<"\n"
             }
        } else if(line=="T"){//Tip text
          getline(files, answer);//raspunsul
        }
        cin>>raspuns;
        if (raspuns == answer){
            correct++;
        }
    }
    file.close();
     fstream files_statistic("./data/teste/Test1/stats.txt");
    if (!files_statistic.is_open()) { 
        cerr << "Error opening the files!" << endl; 
        exit(1);
    }
    stringstream buffer;
    buffer << files_statistic.rdbuf();
    files_statistic.close();

    files_statistic.open("./data/teste/Test1/stats.txt");
    if (!files_statistic.is_open()) {
        cerr << "Error opening the file for rewriting!" << endl;
        exit(1);
    }
    string first_element;
    if (getline(buffer, first_element)) {

        first_element += " (modified)";
        files_statistic << first_element << endl;
    }
     string line;
    while (getline(buffer, line)) {
        files_statistic << line << endl;
    }
     files_statistic <<nume<<" "<<correct<<"/"<<nr_questions<< endl;
    files_statistic.close();
 }