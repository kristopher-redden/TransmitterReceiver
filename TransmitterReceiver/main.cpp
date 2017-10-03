#include <iostream>
#include <string>
#include "ApplicationLayer.h"

using namespace std;

int main(int argc, char* argv[]) {

    //F8 debugs.
    //argv[1];
    string command = argv[1];
    string file1 = "";
    string file2 = "";
    string file3 = "";

    if (command == "-t")
    {
        if (argc == 4)
        {
            file1 = argv[2];
            file2 = argv[3];
            ApplicationLayer al;
            al.CommandT(file1, file2);
        }
        else
        {
            cout << "No files \\ too many \\ too few files specified." << endl;
        }
    }
    else if (command == "-r")
    {
        if (argc == 4)
        {
            file1 = argv[2];
            file2 = argv[3];
            ApplicationLayer al;
            al.CommandR(file1, file2);
        }
        else
        {
            cout << "No files \\ too many \\ too few files specified." << endl;
        }
    }
    else if (command == "-tWithError")
    {
        if (argc == 4)
        {
            file1 = argv[2];
            file2 = argv[3];
        }
        else
        {
            cout << "No files \\ too many \\ too few files specified." << endl;
        }
    }
    else if (command == "-tAndR")
    {
        if (argc == 5)
        {
            file1 = argv[2];
            file2 = argv[3];
            file3 = argv[4];
        }
        else
        {
            cout << "No files \\ too many \\ too few files specified." << endl;
        }
    }
    else if (command == "trAndError")
    {
        if (argc == 4)
        {
            file1 = argv[2];
            file2 = argv[3];
        }
        else
        {
            cout << "No files \\ too many \\ too few files specified." << endl;
        }
    }
    //(command == "-help")
    else
    {
        cout << "-transmitter file1 [file2]" << endl;
        cout << "Encode a file and write it to a new file location." << endl;
        cout << "File1 is the file to encode." << endl;
        cout << "File2 is the file to write to." << endl;
    }

    //Help menu, call the application layer to read and write data.
    return 0;
}