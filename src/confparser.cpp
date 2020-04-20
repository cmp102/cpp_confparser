#include <fstream>
#include <sstream>
#include <algorithm>
#include <confparser.hpp>

namespace confparser{

ptr_wrapper& Config::findParam(std::string_view param){
	auto it = params.find(param.data());
	if(it == params.end()){
		throw std::runtime_error("Error, parameter not found");
	}
	return it->second;
}

void Config::loadFile(std::string_view filename){
	std::ifstream file(filename.data());
	std::string line;
	while(std::getline(file, line)){

		//Delete comments
		line.erase( std::find_if( line.begin(), line.end(),  [](int ch) {
			return ch == '#' || ch == ';';
		}), line.end());

		std::stringstream ss_line(line);
		std::string key;
		if( std::getline(ss_line, key, '=') ){
			std::string value;
			if( std::getline(ss_line, value) ){

				//Removes spaces in key and value
				Config::trim(key);
				Config::trim(value);

				//Sets de value
				auto& cont_ptr = findParam(key);
				cont_ptr.setData(value);
			}
		}
	}
}


/****************
 *              *
 * TRIM HELPERS *
 *              *
 ***************/

// trim from start (in place)
void Config::ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
	}));
}

// trim from end (in place)
void Config::rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

// trim from both ends (in place)
void Config::trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}

}
