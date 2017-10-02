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

void ApplicationLayer::CommandT(string file1, string file2)
{
    DataLinkLayer dl;
    ifstream ifs(file1, ios::in | ios::binary);
    if (ifs.good())
    {
        char character;
        string dataField;
        int charCount = 0;
        while (ifs.get(character))
        {
            charCount++;
            dataField += character;
            //Works for extended ASCII.
            if (charCount == 8)
            {
                dl.Framing(dataField, file2);
                dataField = "";
            }
        }
        dl.Framing(dataField, file2);
    }
}

void ApplicationLayer::CommandR(string file1, string file2)
{

}

void ApplicationLayer::CommandTWithError(string file1, string file2)
{

}

void ApplicationLayer::CommandTAndR(string file1, string file2, string file3)
{

}

void ApplicationLayer::CommandTRAndError(string file1, string file2)
{

}

