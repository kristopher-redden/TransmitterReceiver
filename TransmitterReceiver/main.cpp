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
            try
            {
                al.CommandT(file1, file2, -1);
            }
            catch(int exception)
            {
                string message;
                if (exception == 3)
                {
                    message = "Transmitter: Input file or output file is invalid.";
                    cerr << message;
                }
                exit(exception);
            }
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
            try
            {
                al.CommandR(file1, file2);
            }
            catch(int exception)
            {
                string message;
                if (exception == 1)
                {
                    message = "Receiver: Frame does not have a starting or ending SYN.";
                }
                else if (exception == 2)
                {
                    message = "Receiver: Error when checking parity.";
                }
                else if (exception == 3)
                {
                    message = "Receiver: Input file or output file is invalid.";
                }
                cerr << message;
                exit(exception);
            }
        }
        else
        {
            cerr << "No files \\ too many \\ too few files specified." << endl;
        }
    }
    else if (command == "-et")
    {
        if (argc == 4)
        {
            file1 = argv[2];
            file2 = argv[3];
            try
            {
                ApplicationLayer al;
                al.CommandTWithError(file1, file2);
            }
            catch (int exception)
            {
                string message;
                if (exception == 3)
                {
                    message = "Transmitter With Error: Input file or output file is invalid.";
                }
                else if (exception == 4)
                {
                    message = "Transmitter With Error: File that was written to has no length.";
                }
                cerr << message;
                exit(exception);
            }
        }
        else
        {
            cout << "No files \\ too many \\ too few files specified." << endl;
        }
    }
    else
    {
        cerr << "Invalid command." << endl;
    }
    return 0;
}