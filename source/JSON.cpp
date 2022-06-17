//
// Created by vesko on 15.06.22.
//

#include "../headers/JSON.h"

JSON::JSON(std::string &fileName) : fileName(fileName)
{
//    1. OPEN file
//    2. Validate json
//    3. Move cursor to the beginning of file
//    4. Parse json
//    5. Close file
//    TODO IMPORTANT MOVE ONE CHAR BACK IN FACTORY
//    TODO CHECK FOR FILE STATE
}

void JSON::parseJSON(std::istream &in)
{
    char c;
    in >> c;

//    in.seekg(-1, std::ios_base::cur); // Move the cursor back because we need the data for further validating

//    if (c == '-' || (c >= '0' && c <= '9')) validateNumber(in);
//    else if (c == 't' || c == 'f') validateBool(in);
//    else if (c == 'n') validateNull(in);
//    else if (c == '"') validateString(in);
//    else if (c == '{') validateObject(in);
//    else if (c == '[') validateArray(in);
}
