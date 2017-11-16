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

    //Let port number be a parameter that you can pass in.
    if (command == "-th")
    {
        string hostname = argv[2];
        string fileToReadFrom = argv[3];
        try
        {
            ApplicationLayer al;
            al.CommandTHam(hostname, fileToReadFrom, true, true);
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
    else if (command == "-tcrc")
    {
        string hostname = argv[2];
        string fileToReadFrom = argv[3];
        try
        {
            ApplicationLayer al;    //              ham,  clientTrans
            al.CommandTCrc(hostname, fileToReadFrom, false, true);
        }
        catch (int exception)
        {
            string message;
            cerr << message;
            exit(exception);
        }
    }
    else if (command == "-rh")
    {
        string hostname = argv[2];
        string fileToWriteTo = argv[3];
        try
        {
            ApplicationLayer al;    //              ham, clientTrans
            al.CommandRHam(hostname, fileToWriteTo, true, false);
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
    else if (command == "-rcrc")
    {
        string hostname = argv[2];
        string fileToWriteTo = argv[3];
        try
        {
            ApplicationLayer al;    //              ham,  clientTrans
            al.CommandRCrc(hostname, fileToWriteTo, false, false);
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
            else if (exception == 99)
            {
                message = "Transmitter With Error: CRC did not return a 0 remainder.";
            }
            cerr << message;
            exit(exception);
        }
    }
    else
    {
        cerr << "Invalid command." << endl;
    }
    return 0;
}