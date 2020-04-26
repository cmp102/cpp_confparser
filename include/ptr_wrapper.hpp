#pragma once
#include <iostream>
#include <sstream>
#include <any>
#include <vector>

namespace confparser{

struct ptr_wrapper{
	public:
	bool required {false};
	//Constructor
	template<typename T>
	ptr_wrapper(T& value, bool req) : 
		dataptr{&value},
		required{req}
	{}

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
	void* dataptr {nullptr};
	void(*parseDataPtr)(const std::string&, void*) {nullptr};
	void(*parseIndexedDataPtr)(const std::string&, void*, unsigned int) {nullptr};

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

