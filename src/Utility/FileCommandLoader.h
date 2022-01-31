/*
 * FileCommandLoader.h
 *
 *  Created on: Jan 30, 2022
 *      Author: Jordan Hunt
 */

#ifndef UTILITY_FILECOMMANDLOADER_H_
#define UTILITY_FILECOMMANDLOADER_H_
#include <functional>
#include <vector>
#include <string>
#include "Color.h"
#include "Vector2D.h"
#include <stdint.h>
#include <fstream>
#include <iostream>
enum CommandType
{
    COMMAND_ONE_LINE,
    COMMAND_MULTIPLE_LINE
};
struct ParseFunctionParameters
{
    std::string line;
    size_t delimiterPosition;
    uint32_t lineNumber;
};
// Type define
using ParseFunction = std::function<void(const ParseFunctionParameters &parameters)>;
struct Command
{
    CommandType commandType = COMMAND_ONE_LINE;
    std::string commandString = "";
    ParseFunction parseFunction = nullptr;
};

class FileCommandLoader
{
public:
    FileCommandLoader();
    virtual ~FileCommandLoader();
    void AddCommand(const Command &command);
    bool LoadFile(const std::string &filePath);
    // Helper function
    static Color ReadColor(const ParseFunctionParameters &parameters);
    static Vector2D ReadSize(const ParseFunctionParameters &parameters);
    static int ReadInteger(const ParseFunctionParameters &parameters);
    static std::string ReadString(const ParseFunctionParameters &parameters);
    static char ReadCharacter(const ParseFunctionParameters &parameters);

private:
    std::vector<Command> commands;
};

#endif /* UTILITY_FILECOMMANDLOADER_H_ */
