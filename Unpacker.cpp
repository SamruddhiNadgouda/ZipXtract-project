#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm> // For std::find_if

using namespace std;

// This function handles the unpacking process.
// => Opens the packed file for reading in binary mode. If it fails, an error message is printed, and the function exits.
// => Initializes a buffer (header) to hold the header data for each file.
// => Uses a loop to read the packed file in chunks corresponding to the size of the header (100 bytes).
// => Constructs a string from the header data and removes any trailing whitespace.
// => Parses the header to extract the file name and size using a stringstream. If parsing fails, an error message is printed, and it continues to the next iteration.
// => Opens a new file with the extracted name for writing. If this fails, it prints an error and skips to the next header.
// => Reads the actual file data into a buffer of the size specified in the header and writes this buffer to the newly created file.
// => Increments the count of successfully extracted files and prints a success message.
// => After finishing, it prints a summary of the unpacking activity, including the total number of files extracted.
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

        // Remove trailing spaces
        headerStr.erase(find_if(headerStr.rbegin(), headerStr.rend(), [](unsigned char ch)
                                { return !isspace(ch); })
                            .base(),
                        headerStr.end());

        cout << headerStr << endl;

        // Split the header to extract file name and size
        stringstream ss(headerStr);
        string fileName;
        size_t fileSize;

        ss >> fileName >> fileSize; // Use stringstream to parse file name and size

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

    cout << "---------------------- Unpacking Summary ----------------------" << endl;
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
