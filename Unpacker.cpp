#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

void unpackFiles(const string &packFileName)
{
    ifstream packFile(packFileName, ios::binary);
    if (!packFile)
    {
        cerr << "Error opening packed file: " << packFileName << endl;
        return;
    }

    unsigned char header[100];
    int iCount = 0;

    cout << "Unpacking Activity of the application is started..." << endl;

    while (packFile.read(reinterpret_cast<char *>(header), sizeof(header)))
    {
        string headerStr(reinterpret_cast<char *>(header), sizeof(header));

        headerStr.erase(find_if(headerStr.rbegin(), headerStr.rend(), [](unsigned char ch)
                                { return !isspace(ch); })
                            .base(),
                        headerStr.end());

        cout << headerStr << endl;

        stringstream ss(headerStr);
        string fileName;
        size_t fileSize;

        ss >> fileName >> fileSize; 

        if (ss.fail())
        {
            cerr << "Error parsing header: " << headerStr << endl;
            continue; // Skip this header
        }

        ofstream newFile(fileName, ios::binary);
        if (!newFile)
        {
            cerr << "Error creating file: " << fileName << endl;
            continue; // Skip this file
        }

        vector<char> buffer(fileSize);
        packFile.read(buffer.data(), fileSize);
        newFile.write(buffer.data(), fileSize);

        cout << "File Successfully extracted with Name: " << fileName << endl;
        iCount++;
    }

    cout << "--------------- Unpacking Summary --------------" << endl;
    cout << "Total number of files extracted: " << iCount << endl;
    cout << "Thank you for using Packer-Unpacker..." << endl;
}

int main()
{
    // Ask the user for the name of the packed file
    cout << "----------- Packer Unpacker ----------- " << endl;
    cout << "Enter the file name which contains the packed data: ";
    string packFileName;
    cin >> packFileName;

    unpackFiles(packFileName);
    return 0;
}
