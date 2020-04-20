#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <string_view>
#include <any_wrapper.hpp>

namespace confparser{

struct Config{
	
	public:
	explicit Config() = default;

	void loadFile(std::string_view filename);

	template<typename T>
	void bindParam(std::string_view param, T& value){
		params.emplace(param.data(),&value);
	}

	template<typename T>
	void addParam(std::string_view param, T&& value){
		params.emplace(param.data(),value);
	}

	template<typename T>
	T getParam(std::string_view param) const {
		auto& any_ref = findParam(param.data());
		return std::any_cast<T>(any_ref);
	}


	friend std::ostream& operator<< (std::ostream& stream, const Config& cnf);

	private:
	std::unordered_map<std::string, any_wrapper> params {};

	const any_wrapper& findParam(std::string_view param) const;
	any_wrapper& findParam(std::string_view param);

	// trim from start (in place)
	static inline void ltrim(std::string &s);

	// trim from end (in place)
	static inline void rtrim(std::string &s);

	// trim from both ends (in place)
	static inline void trim(std::string &s);
};

}
