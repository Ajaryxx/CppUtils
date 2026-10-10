#include <StringUtils.hpp>
#include <iostream>

using namespace Utils;


int main()
{
	
	try
	{
		std::cout << StringUtils::StringToValue<int>("3a33234") << std::endl;
		
	}
	catch (const std::invalid_argument& w)
	{
		std::cerr << w.what() << std::endl;
	}
	catch (const std::out_of_range& w)
	{
		std::cerr << w.what() << std::endl;
	}


	return EXIT_SUCCESS;
}