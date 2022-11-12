#include "json11.hpp"
#include <cstdio>

int usage()
{
	fprintf(stderr, "Usage: json11_test <json-file>");
	return 1;
}

int main(int argc, char* argv[])
{
	using namespace json11;
	if (argc != 2) return usage();

	FILE* file;
	if (fopen_s(&file, argv[1], "rb") != 0) return usage();

	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buffer = new char[size + 1];
	fread(buffer, 1, size, file);
	buffer[size] = 0;
	fclose(file);

	std::string err;
	Json json = Json::parse(buffer, err, JsonParse::STANDARD);
	if (!err.empty())
	{
		fprintf(stderr, "Error: %s", err.c_str());
		free(buffer);
		return 1;
	}

	free(buffer);
	return 0;
}