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

//Convert all of the chars to 1's and 0's.
void PhysicalLayer::Encode(unsigned char* frame, string outputFile, int charLength)
{
    //datafield contains: syn, ctrl, data (up to 64 data chars) and syn.
    ofstream ofs(outputFile, ios::out | ios::app);
    if (ofs.good()) //Returns true if none of the error flags are set to true.
    {
        int frameLength = charLength + 3;
        for (int loc = 0; loc < frameLength; loc++)
        {
            unsigned char theChar = frame[loc];
            //ASCII of 0 is 0110000
            //Stored in a byte: 00001100
            //Or with parity to store value.
            int parityCount = 0;
            int value;
            unsigned char character;
            for (int pos = 0; pos < 7; ++pos)//7 times
            {
                //if (theChar & '\x80') throw invalid byte exception.
                value = (int) (theChar >> pos) & 1;
                if (value == 1)
                    character = (unsigned char) '\x31';
                else character = (unsigned char) '\x30';

                ofs.put(character);

                if (value == 1)
                    parityCount++;
            }
            //Make this odd parity.
            if (parityCount % 2 == 0)
                character = '\x31';
            else
                character = '\x30';

            ofs.put(character);
        }
        ofs.flush();
        ofs.close();
    }
    else
        throw 3;

}

//Convert the 1's and 0's to chars.
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
        throw 3;

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
                throw 2;

            else
                characters[charLocation - 1] = charToCreate;
        }
        //We had an even number of 1's.
        else
        {
            if (onesModded == 0)
                characters[charLocation - 1] = charToCreate;
            else
                throw 2;

        }
    }
    return characters;
}