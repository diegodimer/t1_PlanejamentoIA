#include <iostream>
#include <fstream>

using namespace std;
// uso: ./leitor arquivo algoritmo
int main(int argc, char const *argv[])
{
    char command[50];
    string str;
    ifstream file(argv[1]);
    if(file.is_open()){
        while(!file.eof()){
            if(getline(file,str)){
                sprintf(command, "./main -%s %s", argv[2], str.c_str());
                system(command);
            }
        }
        file.close();
    }
    return 0;
}
