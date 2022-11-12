#include "jsmn.h"

#include <stdio.h>
#include <stdlib.h>

int usage()
{
	fprintf(stderr, "Usage: json11_test <json-file>");
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

	char* buffer = (char*)malloc(size + 1);
	fread(buffer, 1, size, file);
	buffer[size] = 0;
	fclose(file);

	jsmn_parser parser;
	jsmn_init(&parser);
	jsmntok_t tokens[1 << 15];
	int count = jsmn_parse(&parser, buffer, size, tokens, sizeof(tokens) / sizeof(tokens[0]));
	if (count < 0)
	{
		fprintf(stderr, "Failed to parse JSON: %d", count);
		free(buffer);
		return 1;
	}

	free(buffer);
	return 0;
}