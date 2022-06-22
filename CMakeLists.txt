cmake_minimum_required(VERSION 3.22)
project(json_parser)

set(CMAKE_CXX_STANDARD 14)

add_executable(json_parser main.cpp source/JSONValidator.cpp headers/JSONValidator.h source/json-types/JSONBase.cpp headers/json-types/JSONBase.h source/json-types/JSONString.cpp headers/json-types/JSONString.h headers/JSONExceptions.h TypeUtilities.h source/JSON.cpp headers/JSON.h source/json-types/JSONNumber.cpp headers/json-types/JSONNumber.h source/json-types/JSONBool.cpp headers/json-types/JSONBool.h source/json-types/JSONNull.cpp headers/json-types/JSONNull.h source/json-types/JSONObject.cpp headers/json-types/JSONObject.h source/json-types/JSONArray.cpp headers/json-types/JSONArray.h source/JSONFactory.cpp headers/JSONFactory.h source/json-types/JSONPair.cpp headers/json-types/JSONPair.h source/JSONParser.cpp headers/JSONParser.h source/Utilities.cpp headers/Utilities.h source/JSONCommandsCLI.cpp headers/JSONCommandsCLI.h)
