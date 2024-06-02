#include "bsttJson.h"

#include <cstdio>

int usage()
{
	fprintf(stderr, "Usage: bsttJson_test <json-file>");
	return 1;
}

int main(int argc, char* argv[])
{
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

	Json json;
	std::string error;
	if (!Json::tryParse(buffer, json, error))
	{
		fprintf(stderr, "Error: %s", error.c_str());
		free(buffer);
		return 1;
	}

	free(buffer);
	return 0;
}