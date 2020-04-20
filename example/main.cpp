/**
 * Cayetano Manchón Pernis
 * April 2020
**/

#include <confparser.hpp>

int main(){
	confparser::Config conf;
	int myint = 0;
	std::string mystring = "string";
	conf.bindParam("valueInt", myint);
	conf.addParam("valueFloat", 10.0f);
	conf.bindParam("ValueString", mystring);
	std::cout << conf << '\n';
	conf.loadFile("config.ini");
	
	std::cout << conf << '\n';

	std::cout << myint << '\n';

	return 0;
}
