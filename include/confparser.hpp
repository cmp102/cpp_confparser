#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <string_view>
#include <ptr_wrapper.hpp>

namespace confparser{

struct Config{
	
	public:
	explicit Config() = default;

	void loadFile(std::string_view filename);

	template<typename T>
	void bindParam(std::string_view param, T& value){
		params.emplace(param.data(),value);
	}

	friend std::ostream& operator<< (std::ostream& stream, const Config& cnf);

	private:
	std::unordered_map<std::string, ptr_wrapper> params {};

	ptr_wrapper& findParam(std::string_view param);

	// trim from start (in place)
	static inline void ltrim(std::string &s);

	// trim from end (in place)
	static inline void rtrim(std::string &s);

	// trim from both ends (in place)
	static inline void trim(std::string &s);
};

}
