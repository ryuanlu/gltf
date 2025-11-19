#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <json.h>
#include "gltf.h"

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

	struct gltf_object* obj = gltf_object_new(data, st.st_size);

	free(data);

	gltf_object_destroy(obj);


	return EXIT_SUCCESS;
}