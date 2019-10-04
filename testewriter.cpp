#include <iostream>
#include <fstream>
using namespace std;

int main( int argc, char* argv[] )
{
    ofstream myfile;
    myfile.open("testeFILE.csv",ios::app);
    myfile<<"first,line\n";
        
    myfile.close();
    
    return 0;

}