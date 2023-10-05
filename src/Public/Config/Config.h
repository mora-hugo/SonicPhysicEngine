#pragma once
#include <map>
#include <string>

class Config
{
public:
    

    static std::string & get(const std::string & Key);
    void static Parse();
    
    

private:

    static void InsertKeyValueFromString(const std::string& Line);
    static std::map<std::string, std::string> ConfigMap;
    static std::string trim(std::string& str);
};
