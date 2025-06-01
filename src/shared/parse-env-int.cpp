#include "shared/parse-env-int.hpp"

int parse_env_int(unordered_map<string, string> file, const string& arg) {
	return stoi(file[arg]);
}