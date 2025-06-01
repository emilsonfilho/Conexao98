#include <unordered_map>
#include <fstream>
#include <sstream>

#include "trim.hpp"

using namespace std;

unordered_map<string, string> load_env(const string& path);