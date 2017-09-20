#include "Util.h"

std::string getCWD() {
    char buffer[FILENAME_MAX];
    char *answer = getcwd(buffer, sizeof(buffer));
    std::string s_cwd;
    if (answer)
    {
        s_cwd = answer;
    }
    
    return s_cwd;
}

std::string loadFile(std::string path) {
	std::ifstream inputFile;

	std::string result = "";

	char currLine[255];

	inputFile.open(path.c_str());

	if (!inputFile) {
		fprintf(stderr, "Failed  to open file: %s\n", path.c_str());
	}

	while (inputFile) {
		inputFile.getline(currLine, 255);

		result += currLine;
		result += "\n";
	}

	inputFile.close();

	return result;
}

std::vector<std::string> stringSplit(std::string& input, std::string& regex) {
	std::regex re(regex);
    std::sregex_token_iterator
        first{input.begin(), input.end(), re, -1},
        last;
    return {first, last};
}
