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

    if (argc != 4)
    {
        cerr << "The number of input parameters is not correct, please enter the command, hostname and file to read/write from/to.";
        exit(3);
    }

    //Let port number be a parameter that you can pass in.
    if (command == "-th")
    {
        try
        {
            string hostname = argv[2];
            string fileToReadFrom = argv[3];

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
        try
        {
            string hostname = argv[2];
            string fileToReadFrom = argv[3];

            ApplicationLayer al;    //              ham,  clientTrans
            al.CommandTCrc(hostname, fileToReadFrom, false, true);
        }
        catch (int exception)
        {
            string message;
            if (exception == 3)
            {
                message = "Transmitted With Error: Input file or output file is invalid.";
            }
            cerr << message;
            exit(exception);
        }
    }
    else if (command == "-rh")
    {
        try
        {
            string hostname = argv[2];
            string fileToWriteTo = argv[3];

            ApplicationLayer al;    //              ham, clientTrans
            al.CommandRHam(hostname, fileToWriteTo, true, false);
        }
        catch (int exception)
        {
            string message;
            if (exception == 1)
            {
                message = "Receiver With Error: First or last character is not a SYN.";
            }
            else if (exception == 2)
            {
                message = "Receiver With Error: Char parity was not correct.";
            }
            cerr << message;
            exit(exception);
        }
    }
    else if (command == "-rcrc")
    {
        try
        {
            string hostname = argv[2];
            string fileToWriteTo = argv[3];

            ApplicationLayer al;    //              ham,  clientTrans
            al.CommandRCrc(hostname, fileToWriteTo, false, false);
        }
        catch (int exception)
        {
            string message;
            if (exception == 1)
            {
                message = "Receiver With Error: First or last character is not a SYN.";
            }
            else if (exception == 2)
            {
                message = "Receiver With Error: Char parity was not correct.";
            }
            else if (exception == 99)
            {
                message = "Receiver With Error: CRC did not return a 0 remainder.";
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