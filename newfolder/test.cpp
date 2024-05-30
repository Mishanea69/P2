#include <iostream>
#include <fstream>
using namespace std;

ofstream& File(ofstream& f){
    f << "Hi" << endl << 0;
    return f;
}

int main()
{
    ofstream f("test.txt");
    File(f) << 1;

    f.close();
    
    return 0;
}