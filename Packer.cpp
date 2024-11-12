#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <dirent.h>   // For directory handling on POSIX systems
#include <sys/stat.h> // For getting file size

using namespace std;

// Function to check if a file has .txt extension
// => It compares the last four characters of the filename to the string .txt.
// If the filename length is less than 4, it returns false.
bool hasTxtExtension(const string &fileName)
{
    return (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".txt");
}

// Function to get file size using stat system call.
// => It calls stat to fill a stat structure with information about the file.
// If successful, it returns the size of the file; otherwise, it returns 0.
size_t getFileSize(const string &filePath)
{
    struct stat statBuf;
    if (stat(filePath.c_str(), &statBuf) == 0)
    {
        return statBuf.st_size;
    }
    return 0;
}

// Main function that handles the packing process.
// => Opens a binary output file for writing (packFileName).
// => Iterates through all files in the specified directory (folderName), checking for .txt files.
// => For each .txt file found, it reads its content, constructs a header containing the filename and its size, and writes both the header and the file contents to the packed file.
// => Keeps a count of successfully packed files and prints a summary at the end.
void packFiles(const string &folderName, const string &packFileName)
{
    ofstream packFile(packFileName, ios::binary);
    if (!packFile)
    {
        cout << "Unable to create packed file." << endl;
        return;
    }

    cout << "Packed File gets successfully created in your current directory." << endl;

    int packCount = 0;
    vector<string> files;

    // Iterate over all files in the directory
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(folderName.c_str())) != nullptr)
    {
        while ((ent = readdir(dir)) != nullptr)
        {
            string fileName(ent->d_name);
            if (hasTxtExtension(fileName))
            {
                files.push_back(folderName + "/" + fileName);
            }
        }
        closedir(dir);
    }
    else
    {
        cout << "Could not open directory." << endl;
        return;
    }

    cout << "Total number of files found in the directory are: " << files.size() << endl;

    // Packing files
    for (const auto &filePath : files)
    {
        ifstream inputFile(filePath, ios::binary);
        if (!inputFile)
        {
            continue;
        }

        // Create a header with the file name and length
        size_t fileSize = getFileSize(filePath);
        string header = filePath.substr(filePath.find_last_of("/\\") + 1) + " " + to_string(fileSize);
        header.resize(100, ' '); // Padding with spaces

        packFile.write(header.c_str(), header.size());

        // Write file data
        packFile << inputFile.rdbuf();
        cout << "File Successfully packed with name: " << filePath << endl;
        packCount++;
    }

    // Display packing summary
    cout << "---------------------- Packing Summary ----------------------" << endl;
    cout << "Total number of files scanned: " << files.size() << endl;
    cout << "Total number of files packed: " << packCount << endl;
    cout << "Thank you for using the Packer-UnPacker..." << endl;

    packFile.close(); // Close the pack file after finishing
}

int main()
{
    string folderName, packFileName;

    cout << "------------------------------- File Packer-UnPacker -------------------------------" << endl;
    cout << "Packing Activity of the Application has Started" << endl;

    cout << "Enter the name of folder which contains the files that you want to pack: ";
    getline(cin, folderName);

    cout << "Enter the name of packed file that you want to create: ";
    getline(cin, packFileName);

    packFiles(folderName, packFileName);

    return 0;
}
