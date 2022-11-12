#define CONFIGURU_IMPLEMENTATION 1
#include "configuru.hpp"

#include <cstdio>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: configuru_test <json-file>");
		return 1;
	}

	using namespace configuru;

	try
	{
		Config cfg = configuru::parse_file(argv[1], configuru::JSON);
	}
	catch (const configuru::ParseError& e)
	{
		return 1;
	}
	return 0;
}
