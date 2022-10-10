#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <algorithm>

constexpr std::string_view oFextension{".txt"}; // desired format of output file
std::string operateDirStr,                      // name of selected directory
    oFname;                                     // name of output file
std::list<std::filesystem::path> filesBuffer{}; // countainer for temporary storing file names
std::vector<std::string> allowType{".webp",     // list of accepted file suffixes
                                   ".png",
                                   ".jpeg",
                                   ".jpg"};

int main(int argc, char const *argv[])
{
    // request user input
    std::cout << "Directory: "; // select directory
    std::getline(std::cin, operateDirStr);
    std::cout << "Output Filename: "; // specify name of new webpage file
    std::getline(std::cin, oFname);

    // instantiate std::filesystem::path object using selected directory
    std::filesystem::path operateDir(operateDirStr);

    // verify if the selected directory is valid
    if (!std::filesystem::exists(operateDir) && !std::filesystem::is_directory(operateDir))
        return 1; // if not valid, terminate programme

    // create and open new webpage file for writing
    auto oFpath = operateDir;
    std::ofstream fout(oFpath.append(oFname).replace_extension(oFextension));

    for (auto &&foundFile : std::filesystem::directory_iterator(operateDir))
    {
        // check if file type is accepted
        if (std::find(allowType.begin(), allowType.end(), foundFile.path().extension()) == allowType.end())
            continue; // if not accepted, then skip this file/directory

        filesBuffer.emplace_back(foundFile.path().filename()); // if accepted, store name of file to vector
    }
    filesBuffer.sort();                   // sort vector of files lexicographically
    for (auto &&sortedFile : filesBuffer) // add stored filenames to output document
        fout << sortedFile << '\n';

    fout.close(); // close webpage file once the operation is finished
    return 0;
}
