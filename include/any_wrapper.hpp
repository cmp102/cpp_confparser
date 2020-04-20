#pragma once
#include <iostream>
#include <sstream>
#include <any>

namespace confparser{

struct any_wrapper : std::any{
	public:

	//Constructor
	template<typename T>
	explicit any_wrapper(T value) : 
		std::any{value}, 
		setDataPtr{&any_wrapper::setData<T>},
		printDataPtr{&any_wrapper::printData<T>} 
	{}

	void setData(const std::string& value){
		(this->*setDataPtr)(value);
	}

	std::ostream& printData(std::ostream& stream) const {
		return (this->*printDataPtr)(stream);
	};

	private: 	
	template<typename T>
	void setData(const std::string& value){
		std::stringstream svalue {value};
		if constexpr (std::is_pointer_v<T>){
			svalue >> **(std::any_cast<T>(this));
		}else{
			svalue >> *(std::any_cast<T>(this));
		}
	}


	template<typename T>
	std::ostream& printData(std::ostream& stream) const {
		if constexpr (std::is_pointer_v<T>){
			stream << **std::any_cast<T>(this);
		}else{
			stream << *std::any_cast<T>(this);
		}
		return stream;
	}

	void(any_wrapper::*setDataPtr)(const std::string&) {nullptr};
	std::ostream& (any_wrapper::*printDataPtr)(std::ostream& stream) const {nullptr};

	//Friends
	friend std::ostream& operator<< (std::ostream& stream, const any_wrapper& icont){return icont.printData(stream);}
};

template<>
inline void any_wrapper::setData<std::string>(const std::string& value){
	*std::any_cast<std::string>(this) = value;
}

template<>
inline void any_wrapper::setData<std::string*>(const std::string& value){
	**(std::any_cast<std::string*>(this)) = value;
}

}

