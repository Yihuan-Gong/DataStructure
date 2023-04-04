#include <iostream>
#include <string>

int main()
{
	char c = 'A';

	// using `std::string::operator+=`

	std::string s;
	s += c;
	std::cout << s << std::endl;

	return 0;
}