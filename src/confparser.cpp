#include <fstream>
#include <sstream>
#include <algorithm>
#include <confparser.hpp>

namespace confparser{

const any_wrapper& Config::findParam(std::string_view param) const {
	auto it = params.find(param.data());
	if(it == params.end()){
		throw std::runtime_error("Error, parameter not found");
	}
	return it->second;
}

any_wrapper& Config::findParam(std::string_view param){
	auto& res = const_cast<const Config*>(this)->findParam(param);
	return const_cast<any_wrapper&>(res);
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
						Config::trim(key);
						Config::trim(value);
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

	std::ostream& operator<< (std::ostream& stream, const Config& cnf){
		for(const auto& [param, value] : cnf.params){
			stream << param << ": " << value << '\n';
		}
		return stream;
	}

}
