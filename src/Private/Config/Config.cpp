#include "../../Public/Config/Config.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>
namespace fs = std::filesystem;


std::map<std::string, std::string> Config::ConfigMap;

void Config::Parse()
{
    std::ifstream myfile ("data/Config.conf");
    if (myfile.is_open())
    {
        std::string line;
        while (std::getline(myfile, line))
        {
            if(line.length() > 2 && (line[0] != '#') && line != "\n" && line != "\r" && !line.empty()) 
                InsertKeyValueFromString(line);
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";
}

void Config::Save()
{
    std::ifstream infile("data/Config.conf");
    std::ofstream outfile("data/Config.conf.temp");

    if (infile.is_open() && outfile.is_open())
    {
        std::string line;
        while (std::getline(infile, line))
        {
            if (line.length() > 2 && (line[0] != '#') && line != "\n" && line != "\r" && !line.empty())
            {
                std::string segment(line);
                std::stringstream test(line);
                std::vector<std::string> seglist;

                while (std::getline(test, segment, ':'))
                {
                    seglist.push_back(segment);
                }

                if (seglist.size() != 2)
                {
                    outfile << line << "\n";
                    continue;
                }

                std::string Key = trim(seglist[0]);
                if (ConfigMap.find(Key) != ConfigMap.end())
                {
                    outfile << Key << " : " << ConfigMap[Key] << "\n";
                }
                else
                {
                    outfile << line << "\n";
                }
            }
            else
            {
                outfile << line << "\n";
            }
        }
        infile.close();
        outfile.close();

        std::filesystem::rename("data/Config.conf.temp", "data/Config.conf");
    }
    else
    {
        std::cout << "Unable to open file";
    }
}


void Config::InsertKeyValueFromString(const std::string& Line)
{
    std::string segment(Line);
    std::stringstream test(Line);
    std::vector<std::string> seglist;

    while(std::getline(test, segment, ':'))
    {
        seglist.push_back(segment);
    }
    if(seglist.size() != 2)
        return;
    
    ConfigMap[trim(seglist[0])] = trim(seglist[1]);
}

std::string Config::trim(std::string& str)
{
    str.erase(str.find_last_not_of(' ')+1);         //suffixing spaces
    str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
    return str;
}

std::string& Config::get(const std::string& Key)
{
    if(ConfigMap.find(Key) == ConfigMap.end())
        return std::string();
    return ConfigMap[Key];
}

void Config::set(const std::string& Key, const std::string& Value)
{
    if(ConfigMap.find(Key) == ConfigMap.end())
        ConfigMap.insert(std::pair(Key, Value));
    else
        ConfigMap[Key] = Value;
}

char Config::getChar(const std::string& Key)
{
    if(ConfigMap.find(Key) == ConfigMap.end() || ConfigMap[Key].length() < 1)
        return ' ';
    return ConfigMap[Key].at(0);
}


