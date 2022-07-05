#pragma once

const int FILE_LINE_PARAMETERS = 6;
const int TRANSLATE_PARAMETERS = 3;

char* removeSpaces(const char*);

bool beginsWith(const char*, const char*);

char* copySubstring(const char*, const size_t, const size_t);

char** parseLine(char*);

char** parseTranslateParameters(const char*);