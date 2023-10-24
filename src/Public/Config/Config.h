#pragma once
#include "../../Public/Math/Vector3D.h"
#include <map>
#include <string>

class Config
{
public:
    

    static std::string & get(const std::string & Key);
    const inline static Vector3D GRAVITY = Vector3D(0, 1000, 0);
    static void set(const std::string & Key, const std::string & Value);
    static char getChar(const std::string & Key);
    void static Parse();
    void static Save();
    
    

private:

    static void InsertKeyValueFromString(const std::string& Line);
    static std::map<std::string, std::string> ConfigMap;
    static std::string trim(std::string& str);
};
