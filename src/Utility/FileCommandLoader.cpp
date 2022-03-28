/*
 * FileCommandLoader.cpp
 *
 *  Created on: Jan 30, 2022
 *      Author: Jordan Hunt
 */
#include <FileCommandLoader.h>
FileCommandLoader::FileCommandLoader()
{
    // TODO Auto-generated constructor stub
}
FileCommandLoader::~FileCommandLoader()
{
    // TODO Auto-generated destructor stub
}
void FileCommandLoader::AddCommand(const Command &command)
{
    commands.push_back(command);
}
bool FileCommandLoader::LoadFile(const std::string &filePath)
{
    std::ifstream inputFile;
    inputFile.open(filePath);
    std::string line = "";
    if (inputFile.is_open() == false)
    {
        std::cout << "[FileCommandLoader.cpp] - [ERROR] - Could not open the file: " << filePath << std::endl;
    }
    while (!inputFile.eof())
    {
        std::getline(inputFile, line);
        size_t commandPosition = std::string::npos;
        // Find the next ":"
        if ((commandPosition = line.find(":")) != std::string::npos)
        {
            size_t delimiterPosition = line.find_first_of(" ", commandPosition);
            // If didn't find a space go to the end of the line
            if (delimiterPosition == std::string::npos)
            {
                delimiterPosition = line.length();
            }
            else
            {
                delimiterPosition -= 1;
            }
            std::string commandString = line.substr(commandPosition + 1, delimiterPosition);
            delimiterPosition += 1;
            for (size_t commandIndex = 0; commandIndex < commands.size(); commandIndex++)
            {
                if (commandString == commands[commandIndex].commandString)
                {
                    if (commands[commandIndex].commandType == COMMAND_ONE_LINE)
                    {
                        ParseFunctionParameters parameters;
                        parameters.delimiterPosition = delimiterPosition;
                        parameters.lineNumber = 0;
                        parameters.line = line;
                        commands[commandIndex].parseFunction(parameters);
                    }
                    else
                    {
                        std::string numbersOfLines = line.substr(delimiterPosition + 1);
                        int totalLines = std::stoi(numbersOfLines);
                        int lineNumber = 0;
                        while (lineNumber < totalLines)
                        {
                            std::getline(inputFile, line);
                            if (line.empty())
                            {
                                continue;
                            }
                            else
                            {
                                ParseFunctionParameters parameters;
                                parameters.delimiterPosition = delimiterPosition;
                                parameters.lineNumber = lineNumber;
                                parameters.line = line;
                                commands[commandIndex].parseFunction(parameters);
                                lineNumber++;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}
Color FileCommandLoader::ReadColor(const ParseFunctionParameters &parameters)
{
    // Find the first space position
    size_t nextSpacePosition = parameters.line.find_first_of(" ", parameters.delimiterPosition + 1);
    /*
     * :fillcolor 255 255 255 0
     * The first space will be after the command and the next value should be next color to read in
     */
    int red = std::stoi(parameters.line.substr(parameters.delimiterPosition, (nextSpacePosition - parameters.delimiterPosition)));
    size_t lastSpacePosition = nextSpacePosition;
    nextSpacePosition = parameters.line.find_first_of(" ", lastSpacePosition + 1);
    int green = std::stoi(parameters.line.substr(lastSpacePosition + 1, nextSpacePosition - lastSpacePosition));
    lastSpacePosition = nextSpacePosition;
    nextSpacePosition = parameters.line.find_first_of(" ", lastSpacePosition + 1);
    int blue = std::stoi(parameters.line.substr(lastSpacePosition + 1, nextSpacePosition - lastSpacePosition));
    int alpha = std::stoi(parameters.line.substr(nextSpacePosition + 1));
    return Color(red, green, blue, alpha);
}
Vector2D FileCommandLoader::ReadSize(const ParseFunctionParameters &parameters)
{
    // Find the first space position
    size_t nextSpacePosition = parameters.line.find_first_of(" ", parameters.delimiterPosition + 1);
    int width = std::stoi(parameters.line.substr(parameters.delimiterPosition, nextSpacePosition - parameters.delimiterPosition));
    size_t lastSpacePosition = nextSpacePosition;
    nextSpacePosition = parameters.line.find_first_of(" ", lastSpacePosition + 1);
    int height = std::stoi(parameters.line.substr(lastSpacePosition + 1, nextSpacePosition - lastSpacePosition));
    return Vector2D(width, height);
}
int FileCommandLoader::ReadInteger(const ParseFunctionParameters &parameters)
{
    std::string integerString = parameters.line.substr(parameters.delimiterPosition + 1);
    return (std::stoi(integerString));
}
std::string FileCommandLoader::ReadString(const ParseFunctionParameters &parameters)
{
    return (parameters.line.substr(parameters.delimiterPosition + 1));
}
char FileCommandLoader::ReadCharacter(const ParseFunctionParameters &parameters)
{
    return (parameters.line.substr(parameters.delimiterPosition + 1)[0]);
}
