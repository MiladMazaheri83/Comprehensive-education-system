#include "FileHandler.hpp"
#include <fstream>
#include <sstream>
#include "DataDefine.hpp"

FileHandler::FileHandler(const string &m_filename) : m_filename(m_filename)
{
    m_data = readData();
}

map<string, map<string, string>> FileHandler::readData()
{
    ifstream file(m_filename);
    string line;
    map<string, map<string, string>> m_data;
    vector<string> headers;

    if (getline(file, line))
    {
        stringstream s(line);
        string field;
        while (getline(s, field, COMMA_CHAR))
        {
            headers.push_back(field);
        }
    }

    while (getline(file, line))
    {
        vector<string> row;
        stringstream s(line);
        string field;
        while (getline(s, field, COMMA_CHAR))
        {
            row.push_back(field);
        }
        m_fileDataTable.push_back(row);
        for (size_t i = ONE_INDEX; i < row.size(); ++i)
        {
            m_data[row[FIRST_ELEMENT_INDEX]][headers[i]] = row[i];
        }
    }

    file.close();
    return m_data;
}

void FileHandler::writeData(const map<string, map<string, string>> &m_data)
{
    ofstream file(m_filename);

    for (const auto &row : m_data)
    {
        file << row.first;
        for (const auto &field : row.second)
        {
            file << COMMA << field.second;
        }
        file << NEW_LINE;
    }

    file.close();
}

string FileHandler::getData(const string &key, const string &subkey)
{
    auto it_outer = m_data.find(key);
    if (it_outer == m_data.end())
    {
        throw runtime_error(NOT_FOUND);
    }
    auto it_inner = it_outer->second.find(subkey);
    if (it_inner == it_outer->second.end())
    {
        throw runtime_error(NOT_FOUND);
    }
    return it_inner->second;
}

vector<vector<string>> FileHandler::getDataTable()
{
    return m_fileDataTable;
}

vector<string> splitString(string input, char delimiter)
{
    stringstream ss(input);
    string token;
    vector<string> output;
    while (getline(ss, token, delimiter))
    {
        output.push_back(token);
    }
    return output;
}

void removeCharacter(string &str, const char &characterToRemove)
{
    std::string result = EMPTY_STRING;

    for (char c : str)
    {
        if (c != characterToRemove)
        {
            result += c;
        }
    }
    str = result;
}

bool oneWordQout(const string &input, const char &border)
{
    size_t firstQuote = input.find(border);
    size_t secondQuote = input.find(border, firstQuote + ONE_INDEX);

    if (firstQuote != std::string::npos && secondQuote != std::string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
}