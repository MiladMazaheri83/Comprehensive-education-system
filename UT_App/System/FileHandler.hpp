#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <string>
#include <vector>
#include <map>
using namespace std;


class FileHandler
{
public:
    FileHandler(const string &m_filename);
    map<string, map<string, string>> readData();
    void writeData(const map<string, map<string, string>> &m_data);
    string getData(const string &key, const string &subkey);
    vector<vector<string>> getDataTable();
private:
    string m_filename;
    map<string, map<string, string>> m_data;
    vector<vector<string>> m_fileDataTable;
};

vector<string> splitString(string input, char delimiter);
bool oneWordQout(const string &input, const char &border);
void removeCharacter(string &str, const char &characterToRemove);

#endif // FILEHANDLER_HPP