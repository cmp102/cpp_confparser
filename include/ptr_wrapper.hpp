#pragma once
#include <iostream>
#include <sstream>
#include <any>

namespace confparser{

struct ptr_wrapper{
	public:
	//Constructor
	template<typename T>
	explicit ptr_wrapper(T& value) : 
		dataptr{&value}, 
		setDataPtr{&ptr_wrapper::setData<T>}
	{}

	//Calls the apropiate function to parse string to corresponent type
	void setData(const std::string& value){
		(this->*setDataPtr)(value);
	}

	private: 	
	void* dataptr {nullptr};
	void(ptr_wrapper::*setDataPtr)(const std::string&) {nullptr};

	template<typename T>
	void setData(const std::string& value){
		std::stringstream svalue {value};
		svalue >> *(static_cast<T*>(dataptr));
	}
};

template<>
inline void ptr_wrapper::setData<std::string>(const std::string& value){
	*static_cast<std::string*>(dataptr) = value;
}

}

