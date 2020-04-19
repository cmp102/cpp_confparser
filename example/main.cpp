/**
 * Cayetano Manchón Pernis
 * April 2020
**/

#include <confparser.hpp>



int main(){
	confparser::Config conf;
	conf.addParam("valueInt", 0);
	conf.addParam("valueFloat", 0.0f);
	conf.addParam("ValueString", std::string(""));
	std::cout << conf << '\n';
	conf.loadFile("config.ini");
	std::cout << conf << '\n';


	int valueInt {conf.getParam<int>("valueInt")};
	std::cout << valueInt << '\n';

	return 0;
}
