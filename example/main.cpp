/**
 * Cayetano Manchón Pernis
 * April 2020
**/

#include <confparser.hpp>

int main(){

	//Variables to bind
	int			myint		= 0;
	std::string	mystring	= "string";
	float			myfloat	= 10;

	confparser::Config conf;

	conf.bindParam("valueInt"		,myint);
	conf.bindParam("valueFloat"	,myfloat);
	conf.bindParam("ValueString"	,mystring);
	
	//Before load config file
	std::cout << "myint: " 		<< myint		<< '\n';
	std::cout << "mystring: "	<< mystring	<< '\n';
	std::cout << "myfloat: "	<< myfloat	<< "\n\n";
	
	conf.loadFile("config.ini");
	
	//After load config file
	std::cout << "myint: " 		<< myint		<< '\n';
	std::cout << "mystring: "	<< mystring	<< '\n';
	std::cout << "myfloat: "	<< myfloat	<< '\n';

	return 0;
}
