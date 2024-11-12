# ZipXtract-project using C++
File zipper and unzipper tool which compresses multiple .txt files from a specified directory into a single packed file and then unpacks this file back to individual .txt files.
### Tech Involved: C++, Standard Libraries, File System Libraries, Git, Github, VScode.

#### 1. Directory Scanning and File Filtering:
  - Implemented functionality to scan a specified directory and identify .txt files for packing.
#### 2. File Packing (Packer.cpp):
  - Designed Packer.cpp to read and combine multiple .txt files into a single binary file.
  - For each .txt file, a header with file name and size information is added to the packed file.
  - Each file’s content is appended sequentially, creating a compact and organized archive.
#### 3. File Size Retrieval:
  - Used stat system calls to accurately determine file sizes and add this metadata to the packed file.
#### 4. Unpacking Files (Unpacker.cpp):
  - Implemented Unpacker.cpp to read the packed binary file, parse headers, and extract individual files.
  - For each extracted file, retrieved the file name and content size to reconstruct the original .txt files.

#### Error Handling and Validation:
  - Added error handling for scenarios such as file read/write failures, directory issues, and parsing errors.
#### User Interaction
  - Included console-based prompts to guide users through providing directory paths and naming packed files.
#### Summary Reporting
  - Displayed comprehensive summaries after packing and unpacking to inform users of the total files processed and extracted.
#### Code Structure and Modularity
  - Organized code with modular functions for tasks like file filtering, packing, and unpacking for clarity and reusability.
