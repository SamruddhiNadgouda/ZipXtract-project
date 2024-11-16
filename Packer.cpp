#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <dirent.h>  
#include <sys/stat.h> 
using namespace std;

bool hasTxtExtension(const string &fileName)
{
    return (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".txt");
}

size_t getFileSize(const string &filePath)
{
    struct stat statBuf;
    if (stat(filePath.c_str(), &statBuf) == 0)
    {
        return statBuf.st_size;
    }
    return 0;
}

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


    for (const auto &filePath : files)
    {
        ifstream inputFile(filePath, ios::binary);
        if (!inputFile)
        {
            continue;
        }

        size_t fileSize = getFileSize(filePath);
        string header = filePath.substr(filePath.find_last_of("/\\") + 1) + " " + to_string(fileSize);
        header.resize(100, ' '); // Padding with spaces

        packFile.write(header.c_str(), header.size());

        packFile << inputFile.rdbuf();
        cout << "File Successfully packed with name: " << filePath << endl;
        packCount++;
    }

    cout << "---------------------- Packing Summary ----------------------" << endl;
    cout << "Total number of files scanned: " << files.size() << endl;
    cout << "Total number of files packed: " << packCount << endl;
    cout << "Thank you for using the Packer-UnPacker..." << endl;

    packFile.close(); 

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
