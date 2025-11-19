#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <json.h>

int main(int argc, char** argv)
{
	struct stat st;
	FILE* fp = NULL;
	char* data = NULL;
	
	stat(argv[1], &st);
	fp = fopen(argv[1], "r");
	data = calloc(1, st.st_size);
	fread(data, 1, st.st_size, fp);
	fclose(fp);

	struct json_tokener* tokener = NULL;
	struct json_object* obj = NULL;

	tokener = json_tokener_new();
	obj = json_tokener_parse_ex(tokener, data, st.st_size);

	json_object_object_foreach(obj, key, val)
	{
		printf("%s\n", key);
	}

	json_object_put(obj);
	json_tokener_free(tokener);

	free(data);

	return EXIT_SUCCESS;
}