
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;

void readFile(string filename)
{
    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {

        cerr << "Error opening output file!"
            << endl;

        return;
    }
    string line;

    while (getline(inputFile, line))
    {

        cout << line << endl;

    }

}
int main()
{
   thread t1(readFile, "file1.txt");
   thread t2(readFile, "file2.txt");
    
   t1.join();
   t2.join();
   
    //readFile("file1.txt");
    //readFile("file2.txt");
    
    return 0;



}
