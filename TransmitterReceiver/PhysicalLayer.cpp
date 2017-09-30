//
// Created by kristopher on 9/30/17.
//

#include "PhysicalLayer.h"
#include <iostream>

PhysicalLayer::PhysicalLayer()
{

}
PhysicalLayer::~PhysicalLayer()
{

}
void PhysicalLayer::Encode(string dataField, string outputFile)
{
    string dataFieldInBinary;
    for (int i = 0; i < dataField.length(); i++)
    {
        char tempCharacter = dataField.at(i);
        //ASCII of 0 is 0110000
        //Stored in a byte: 00110000
        //Or with parity to store value.
        int parityCount = 0;
        int value;
        for (int pos = 0; pos < 8; ++pos)//7 times
        {
            value = (int) (tempCharacter >> pos) & 1;
            if (value == 1)
                dataFieldInBinary += "1";
            else dataFieldInBinary += "0";

            //dataFieldInBinary += value;
            if (value == 1)
                parityCount++;
        }
        //Make this odd parity.
        if (parityCount % 2 == 0)
            dataFieldInBinary += "1";
        else
            dataFieldInBinary += "0";
        cout << dataFieldInBinary << endl;
    }
}
void PhysicalLayer::Decode(char character)
{

}