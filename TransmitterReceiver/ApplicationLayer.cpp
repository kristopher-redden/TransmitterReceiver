//
// Created by kristopher on 9/30/17.
//

#include "ApplicationLayer.h"
#include "PhysicalLayer.h"
#include "DataLinkLayer.h"

#include <iostream>
#include <string>
#include <fstream>

ApplicationLayer::ApplicationLayer()
{

}

ApplicationLayer::~ApplicationLayer()
{

}

//file1 is the file to read from, file2 is the file to write to.
void ApplicationLayer::CommandT(string file1, string file2)
{
    //Clear out the file in case it exists, this way we can simply append to it later on.
    ofstream ofs(file2, ios::out | ios::trunc);
    DataLinkLayer dl;
    ifstream ifsLeng(file1, ios::in | ios::ate);
    int fileLength = ifsLeng.tellg();
    ifsLeng.close();

    //Open the file and get the data length of the extra frame's.
    ifstream ifs (file1, ios::in | ios::binary);
    int extraFrameCharLength = fileLength % 64;
    if (ifs.good())
    {
        char character;
        //We will have 67 chars in the frame, get the data for 2 - 65.
        unsigned char *chars = new unsigned char[67];
        int charCount = 0;
        while (ifs.get(character))
        {
            //Location 0 and 1 is SYN and ctrl, location 66 is the other SYN Char.
            chars[charCount + 2] = character;
            charCount++;
            //We've got 64 chars, go to DataLink to place SYN's and ctrl in the correct location.
            if (charCount == 64)
            {
                dl.Framing(chars, file2, 64);
                charCount = 0;
            }
        }
        //Copy the left over chars to a new byte array, which will be the frame that is not full.
        unsigned char *smallChars = new unsigned char[extraFrameCharLength + 3];
        for (int smallCount = 0; smallCount < extraFrameCharLength; smallCount++)
        {
            smallChars[smallCount + 2] = chars[smallCount + 2];
        }
        dl.Framing(smallChars, file2, extraFrameCharLength);
        ifs.close();
    }
    else
        throw 3;
}

//file1 is the file to read from, file2 is the file to write to.
void ApplicationLayer::CommandR(string file1, string file2)
{
    ifstream ifs(file1, ios::in | ios::ate);
    int fileLength = ifs.tellg();
    ifs.close();

    DataLinkLayer dl;
    unsigned char *values;
    values = dl.Deframing(file1, fileLength);
    //Grab the number of chars that will make up the decoded file.

    int charLength = fileLength / 8;
    int printableChars = 0;
    int tempFileLength;
    while(charLength > 0)
    {
        tempFileLength = charLength;
        charLength -= 67;
        //In case we don't grab the last non full frame, we need to get the char count of that one.
        if (charLength < 0)
        {
            tempFileLength -= 3;
            printableChars += tempFileLength;
            break;
        }
        //We've accounted for the frame, but we will only print 64 chars from the frame.
        tempFileLength -= 67;
        printableChars += 64;
    }
    //We have all of the chars, write them to the file.
    ofstream ofs(file2, ios::out | ios::trunc);
    if (ofs.good())
    {
        unsigned char character;
        for (int charCount = 0; charCount < printableChars; charCount++)
        {
            character = values[charCount];
            ofs.put(character);
        }
        ofs.flush();
        ofs.close();
    }
    else
        throw 3;

}

//file1 is the file to read from, file2 is the file to write to.
void ApplicationLayer::CommandTWithError(string file1, string file2)
{
    //Generate the file of 1's and 0's.
    CommandT(file1, file2);
    //Grab the number of 1's and 0's in the file, and pick a random one to switch.
    ifstream ifs(file2, ios::in | ios::ate);

    int fileLength = ifs.tellg();
    if (fileLength == 0)
        throw 4;
    char character;
    srand(time(NULL));
    if (ifs.good())
    {
        int bit = rand() % fileLength;
        ifs.seekg(bit);
        ifs.get(character);
        ifs.close();
        //ofstream ofs(file2, ios::out);
        //ofs.seekp(bit);
        fstream ofs(file2, ios::out);
        ofs.seekp(bit);
        if (character == 48)
            ofs.put('\031');//If we have a 0, write a 1.
        else if (character == 49)
            ofs.put('\030');
        else
        {
            int weHaveAnError = 0;
        }
    }
    else
        throw 3;
}


