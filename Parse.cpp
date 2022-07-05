#include <cstring>
#include "Parse.h"
#pragma warning(disable: 4996)

bool beginsWith(const char* line, const char* substr) {
	while (*line != '\0' && *substr != '\0') {
		if (*line != *substr) {
			return false;
		}
		line++;
		substr++;
	}
	if (*line == '\0') {
		return false;
	}
	return true;
}

char* copySubstring(const char* line, const size_t startIndex, const size_t length) {
	char* result = new char[length + 1];
	for (size_t i = 0; i < length; i++) {
		result[i] = line[i + startIndex];
	}
	result[length] = '\0';
	return result;
}

char* removeSpaces(char* line) {
	size_t length = strlen(line);
	char* temp = new char[length];
	int index = 0;
	for (size_t i = 0; i < length; i++) {
		if (line[i] != ' ') {
			temp[index++] = line[i];
		}
	}
	temp[index] = '\0';
	return temp;
}

char** parseLine(char* line) {
	char** result = new char* [FILE_LINE_PARAMETERS];
	line = removeSpaces(line);
	size_t length = strlen(line);
	if (beginsWith(line, "<rect")) {
		result[0] = new char[strlen("rect") + 1];
		strcpy(result[0], "rect");
		size_t indexResult = 1;
		bool inQuotes = false;
		size_t startIndex, endIndex;
		for (size_t i = strlen("rect") + 2; i < length &&
			indexResult < FILE_LINE_PARAMETERS; i++) {
			if (line[i] == '\"') {
				inQuotes = !inQuotes;
			}
			if (inQuotes) {
				startIndex = ++i;
				while (line[i] != '\"') {
					i++;
				}
				inQuotes = false;
				endIndex = i;
				result[indexResult++] = copySubstring(line, startIndex, endIndex - startIndex);
			}
		}
	}
	else if (beginsWith(line, "<circle")) {
		result[0] = new char[strlen("circle") + 1];
		strcpy(result[0], "circle");
		size_t indexResult = 1;
		bool inQuotes = false;
		size_t startIndex, endIndex;
		for (size_t i = strlen("circle") + 2; i < length &&
			indexResult < FILE_LINE_PARAMETERS; i++) {
			if (line[i] == '\"') {
				inQuotes = !inQuotes;
			}
			if (inQuotes) {
				startIndex = ++i;
				while (line[i] != '\"') {
					i++;
				}
				inQuotes = false;
				endIndex = i;
				result[indexResult++] = copySubstring(line, startIndex, endIndex - startIndex);
			}
		}
		result[FILE_LINE_PARAMETERS-1] = nullptr;
	}
	else if (beginsWith(line, "<line")) {
		result[0] = new char[strlen("line") + 1];
		strcpy(result[0], "line");
		size_t indexResult = 1;
		bool inQuotes = false;
		size_t startIndex, endIndex;
		for (size_t i = strlen("line") + 2; i < length &&
			indexResult < FILE_LINE_PARAMETERS; i++) {
			if (line[i] == '\"') {
				inQuotes = !inQuotes;
			}
			if (inQuotes) {
				startIndex = ++i;
				while (line[i] != '\"') {
					i++;
				}
				inQuotes = false;
				endIndex = i;
				result[indexResult++] = copySubstring(line, startIndex, endIndex - startIndex);
			}
		}
	}
	return result;
}

char** parseTranslateParameters(const char* line) {
	char** result = new char*[TRANSLATE_PARAMETERS];
	int resultIndex = 0, index = 0;
	bool inParameter = false;
	while (line[index]!='\0' && resultIndex<TRANSLATE_PARAMETERS) {
		if (line[index] != ' ') {
			inParameter = true;
			size_t startIndex = index;
			while (line[index] != ' ' && line[index]!='\0') {
				index++;
			}
			size_t endIndex = index;
			result[resultIndex++] = copySubstring(line, startIndex, endIndex - startIndex);
		}
		index++;
	}
	if (!beginsWith(result[0], "horizontal=") && !beginsWith(result[0], "vertical=")) {
		if (beginsWith(result[1], "horizontal=")) {
			result[1] = copySubstring(result[1], strlen("horizontal="),strlen(result[1])-strlen("horizontal="));
			result[2] = copySubstring(result[2], strlen("vertical="), strlen(result[2]) - strlen("vertical="));
		}
		else if (beginsWith(result[1], "vertical=")) {
			result[2] = copySubstring(result[2], strlen("horizontal="), strlen(result[2]) - strlen("horizontal="));
			result[1] = copySubstring(result[1], strlen("vertical="), strlen(result[1]) - strlen("vertical="));
			char* swap = result[2];
			result[2] = result[1];
			result[1] = swap;
		}
	}
	else {
		if (beginsWith(result[0], "horizontal=")) {
			result[0] = copySubstring(result[0], strlen("horizontal="), strlen(result[0]) - strlen("horizontal="));
			result[1] = copySubstring(result[1], strlen("vertical="), strlen(result[1]) - strlen("vertical="));
		}
		else if (beginsWith(result[0], "vertical=")) {
			result[1] = copySubstring(result[1], strlen("horizontal="), strlen(result[1]) - strlen("horizontal="));
			result[0] = copySubstring(result[0], strlen("vertical="), strlen(result[0]) - strlen("vertical="));
			char* swap = result[1];
			result[1] = result[0];
			result[0] = swap;
		}
		result[TRANSLATE_PARAMETERS-1] = nullptr;
	}
	return result;
}