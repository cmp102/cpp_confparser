/**
 * Cayetano Manchón Pernis
 * April 2020
**/

#include <sstream>
#include <string>
#include <vector>
#include <confparser.hpp>




int main(){

	//Variables to bind
	int			myint		= 0;
	std::string	mystring	= "string";
	float			myfloat	= 10;
	bool			mybool = true;
	std::vector<std::vector<std::string>> vecString;

	confparser::ConfParser conf;

	conf	.bindParam				(myint		)
			.bindParam				(myfloat		)
			.bindRequiredParam	(mystring	)
			.bindIndexedParam		(vecString	)
			.bindParam				(mybool		);
	
	//Before load config file
	std::cout << "myint: " 		<< myint		<< '\n';
	std::cout << "mystring: "	<< mystring	<< '\n';
	std::cout << "myfloat: "	<< myfloat	<< "\n";
	std::cout << "mybool: "	<< mybool	<< "\n\n";
	for(auto& vec : vecString){
		std::cout << "vec: [";
		for(auto& val : vec){
			std::cout << "\"" << val << "\" ";
		}
		std::cout << "]\n";
	}


	conf.loadFile("config.ini");
	
	//After load config file
	std::cout << "myint: " 		<< myint		<< '\n';
	std::cout << "mystring: "	<< mystring	<< '\n';
	std::cout << "myfloat: "	<< myfloat	<< '\n';
	std::cout << "mybool: "	<< mybool	<< "\n";

	for(auto& vec : vecString){
		std::cout << "vec: [";
		for(auto& val : vec){
			std::cout << "\"" << val << "\" ";
		}
		std::cout << "]\n";
	}

	return 0;
}
