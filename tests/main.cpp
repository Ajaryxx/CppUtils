#include <StringUtils.hpp>
#include <iostream>

int main()
{
	std::cout << StringUtils::ToLower("TE漢Ä, Ö, ÜsT") << std::endl;
	return EXIT_SUCCESS;
}