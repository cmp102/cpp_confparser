#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <string_view>
#include <ptr_wrapper.hpp>

namespace confparser{

#define bindParam(param) bindNamedParam(param,#param)
#define bindRequiredParam(param) bindNamedParam(param,#param,true)

#define bindIndexedParam(param) bindIndexedNamedParam(param,#param)
#define bindIndexedRequiredParam(param) bindIndexedNamedParam(param,#param,true)


struct ConfParser{
	
	public:
	explicit ConfParser() = default;

	void loadFile(std::string_view filename);

	template<typename T>
	ConfParser& bindNamedParam(T& value, std::string_view param, bool required = false){
		ptr_wrapper pw{value, required};
		pw.setParseData<T>();
		params.emplace(param.data(), pw);
		return *this;
	}

	template<typename T>
	ConfParser& bindIndexedNamedParam(std::vector<T>& value, std::string_view param, bool required = false){
		ptr_wrapper pw{value, required};
		pw.setParseIndexedData<T>();
		params.emplace(param.data(), pw);
		return *this;
	}

	friend std::ostream& operator<< (std::ostream& stream, const ConfParser& cnf);

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
