#include <iostream>
using namespace std;

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

int main()
{
    //for(int i=0; i<=250; i++) cout << i << ".) " << char(i) << endl;
    string a = setColour("a", "red");
    if(a[0] == '\033') cout << a.length();
    return 0;
}

// 209.) ╤
// 207.) ╧
// 179.) │
// 196.) ─
// 197.) ┼