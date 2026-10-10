#include <StringUtils.hpp>
#include <iostream>

using namespace Utils;

struct MyStruct
{

};

int main()
{
	
	try
	{
		StringUtils::ValueToString(MyStruct());
		std::cout << StringUtils::Format("Name: {}, Age: {}, Size: {}, Hobby: {}", "Joel", 18, 1.84f, "Programming") << std::endl;
		
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