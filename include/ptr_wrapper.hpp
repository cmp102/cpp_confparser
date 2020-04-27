#pragma once
#include <iostream>
#include <sstream>
#include <any>
#include <vector>
#include <algorithm>

namespace confparser{

inline std::stringstream& operator>>(std::stringstream& ss, bool& b){
	auto s = ss.str();
	std::transform(s.begin(), s.end(), s.begin(), ::toupper);
	if(s == "TRUE"){
		b = true;
	}else if(s == "FALSE"){
		b = false;
	}else{
		std::string msg {"Error, " + s + " doesn't match with \"true\" or \"false\""};
		throw std::runtime_error(msg);
	}
	return ss;
}

template<typename T>
std::stringstream& operator>>(std::stringstream& ss, std::vector<T>& vec){
	std::string s;
	while(getline(ss, s, ',')){
		std::stringstream sss{s};
		sss >> vec.emplace_back();
	}
	return ss;
}

struct ptr_wrapper{
	public:
	bool required {false};
	//Constructor
	template<typename T>
	ptr_wrapper(T& value, bool req) : 
		required{req},
		dataptr{&value}
	{}

	//
	template<typename T>
	void setParseData(){
		parseDataPtr = parseData<T>;
	}
	template<typename T>
	void setParseIndexedData(){
		parseIndexedDataPtr = parseIndexedData<T>;
	}

	//Calls the apropiate function to parse string to corresponent type
	void parseData(const std::string& value){
		parseDataPtr(value, dataptr);
	}

	//Calls the apropiate function to parse string to corresponent type
	void parseIndexedData(const std::string& value, unsigned	int pos){
		parseIndexedDataPtr(value, dataptr, pos);
	}

	private:
	//Pointer to value
	void* dataptr {nullptr};
	

	//Parse function pointers
	void(*parseDataPtr)(const std::string&, void*) {nullptr};
	void(*parseIndexedDataPtr)(const std::string&, void*, unsigned int) {nullptr};


	//Template parse functions
	template<typename T>
	static void parseData(const std::string& value, void* valueptr){
		std::stringstream svalue {value};
		svalue >> *(static_cast<T*>(valueptr));
	}
	template<typename T>
	static void parseIndexedData(const std::string& value, void* valueptr, unsigned	int pos){
		std::stringstream svalue {value};
		auto& vec = *(static_cast<std::vector<T>*>(valueptr));
		if(!(vec.size()>pos)){
			vec.resize(pos+1);
		}
		parseData<T>(value, &vec[pos]);
	}
};

template<>
inline void ptr_wrapper::parseData<std::string>(const std::string& value, void* valueptr){
	*static_cast<std::string*>(valueptr) = value;
}

}

