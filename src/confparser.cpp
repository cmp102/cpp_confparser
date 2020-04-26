#include <fstream>
#include <sstream>
#include <algorithm>
#include <confparser.hpp>
#include <cstdlib>

namespace confparser{

ptr_wrapper& ConfParser::findParam(std::string_view param){
	auto it = params.find(param.data());
	if(it == params.end()){
		throw std::runtime_error("Error, parameter not found");
	}
	return it->second;
}

void ConfParser::loadFile(std::string_view filename){
	std::ifstream file(filename.data());
	std::string line;
	unsigned int linecount = 1;
	while(std::getline(file, line)){
		try{
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
					ConfParser::trim(key);
					ConfParser::trim(value);

					if(key.find(':') != std::string::npos){
						unsigned int index;
						std::stringstream ss_key(key);
						std::getline(ss_key, key, ':');
						ss_key >> index;
						auto& cont_ptr = findParam(key);
						cont_ptr.parseIndexedData(value, index);
						cont_ptr.required = false;
					}else{
						//Sets de value
						auto& cont_ptr = findParam(key);
						cont_ptr.parseData(value);
						cont_ptr.required = false;
					}
				}
			}
		}catch(std::runtime_error& exception){
			std::string msg =	std::string("Error reading file " 
									+ std::string(filename) 
									+ " at line " 
									+ std::to_string(linecount) 
									+ "\n" 
									+ exception.what());
			throw std::runtime_error(msg);
		}
		++linecount;
	}

	//Checks if a required param was not found
	for(auto& [name,pw] : params){
		if(pw.required){
			std::string msg = std::string("Error reading file " 
									+ std::string(filename) 
									+ " param required \""
									+ name
									+ "\" not found\n");
			throw std::runtime_error{msg};
		}
	}

}


/****************
 *              *
 * TRIM HELPERS *
 *              *
 ***************/

// trim from start (in place)
void ConfParser::ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
	}));
}

// trim from end (in place)
void ConfParser::rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

// trim from both ends (in place)
void ConfParser::trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}

}
