#include <iostream>
#include "shared/load-env.hpp"

unordered_map<string, string> load_env(const string& path) {
	ifstream file(path);
	unordered_map<string, string> env;
	string line;

	while (getline(file, line)) {
		if (line.empty() or line[0] == '#') continue;

		istringstream ss(line);
		string key, value;
		if (getline(ss, key, '=') and getline(ss, value))
			env[trim(key)] = trim(value);
	}

	return env;
}