//
// Created by kristopher on 9/30/17.
//

#include "PhysicalLayer.h"
#include <iostream>
#include <fstream>

PhysicalLayer::PhysicalLayer()
{

}
PhysicalLayer::~PhysicalLayer()
{

}
void PhysicalLayer::Encode(string dataField, string outputFile)
{
    //datafield contains: syn, ctrl, data and syn.
    //Works for extended ASCII table.
    string dataFieldInBinary;
    for (int i = 0; i < dataField.length(); i++)
    {
        char tempCharacter = dataField.at(i);
        //ASCII of 0 is 0110000
        //Stored in a byte: 00110000
        //Or with parity to store value.
        int parityCount = 0;
        int value;
        for (int pos = 0; pos < 7; ++pos)//7 times
        {
            value = (int) (tempCharacter >> pos) & 1;
            if (value == 1)
                dataFieldInBinary += "1";
            else dataFieldInBinary += "0";

            if (value == 1)
                parityCount++;
        }
        //Make this odd parity.
        if (parityCount % 2 == 0)
            dataFieldInBinary += "1";
        else
            dataFieldInBinary += "0";
    }

    Print(dataFieldInBinary, outputFile);
}

unsigned char* PhysicalLayer::Decode(string fileToRead, int fileLength)
{
    int charLength = fileLength / 8;
    unsigned char *bytes = new unsigned char[fileLength];
    int loc = 0;
    ifstream beginIfs(fileToRead, ios::in | ios::binary);
    if (beginIfs.good())
    {
        char character;
        while (beginIfs.get(character))
        {
            bytes[loc] = (unsigned char) character;
            loc++;
        }
    }
    else
    {
        //Cannot open the file, throw and exception.
    }
    //Now that we have read in all the 1's and 0's, do the parity check and construct the chars.
    int parityValue;
    int onesCount;
    unsigned char charToCreate;
    unsigned char *characters = new unsigned char[charLength];

    for (int count = 1; count <= charLength; count++)
    {
        //Reset our char that we are creating and the ones count.
        charToCreate = 0x0;
        onesCount = 0;
        charLocation++;//Keep track of the char we are at.
        parityValue = bytes[(count * 8) - 1];//This is the last bit of the char.
        for (int position = count * 8 - 2, forward = 6; position >= (count - 1) * 8; position--, forward--)
        {
            unsigned char tempCharacter = bytes[position];
            if (tempCharacter == 49)
            {
                onesCount++;
                charToCreate |= 1 << forward;
            }
        }

        int onesModded = onesCount % 2;
        string message;
        //We had an odd number of 1's.
        if (parityValue == 48)
        {
            //This is an error.
            if (onesModded == 0)
            {
                message = "Error at char: " + charLocation;
                cerr << message;
                return nullptr;
            }
            else
            {
                characters[charLocation - 1] = charToCreate;
            }
        }
        //We had an even number of 1's.
        else
        {
            if (onesModded == 0)
            {
                characters[charLocation - 1] = charToCreate;
            }
            else
            {
                message = "Error at char: " + charLocation;
                cerr << message;
                //We are done, this is a bad frame.
                return nullptr;
            }
        }
    }
    return characters;
}

void PhysicalLayer::Print(string value, string file)
{
    //Now that we have the entire binary number with parity bits included, write these values to a file.
    ofstream ofs(file, ios::out | ios::app);
    for (int loc = 0; loc < value.length(); loc++)
    {
        unsigned char character = (unsigned char) value.at(loc);
        ofs.put(character);
    }
    ofs.flush();
    ofs.close();
}