/**
 * Cayetano Manchón Pernis
 * April 2020
**/

#include <confparser.hpp>

std::stringstream& operator>>(std::stringstream& ss, std::vector<std::string>& vec){
	std::string s;

	while(getline(ss, s, ','))
		vec.push_back(s);
	return ss;
}


int main(){

	//Variables to bind
	int			myint		= 0;
	std::string	mystring	= "string";
	float			myfloat	= 10;
	std::vector<std::vector<std::string>> vecString;

	confparser::ConfParser conf;

	conf	.bindParam				(myint		)
			.bindParam				(myfloat		)
			.bindRequiredParam	(mystring	)
			.bindIndexedParam		(vecString	);
	
	//Before load config file
	std::cout << "myint: " 		<< myint		<< '\n';
	std::cout << "mystring: "	<< mystring	<< '\n';
	std::cout << "myfloat: "	<< myfloat	<< "\n\n";
	
	conf.loadFile("config.ini");
	
	//After load config file
	std::cout << "myint: " 		<< myint		<< '\n';
	std::cout << "mystring: "	<< mystring	<< '\n';
	std::cout << "myfloat: "	<< myfloat	<< '\n';

	for(auto& vec : vecString){
		std::cout << "vec: [";
		for(auto& val : vec){
			std::cout << "\"" << val << "\" ";
		}
		std::cout << "]\n";
	}

	return 0;
}
