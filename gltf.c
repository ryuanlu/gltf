#include <stdio.h>
#include <string.h>
#include <json.h>

struct gltf_asset
{
	char* copyright;
	char* generator;
	char* version;
	char* minVersion;

};

struct gltf_node
{
	int camera;
	int nr_children;
	int* children;
	int skin;
	float matrix[16];
	int mesh;
	float rotation[4];
	float scale[3];
	float translate[3];
	int nr_weights;
	float* weights;
	char* name;
};

struct gltf_scene
{
	int nr_nodes;
	int* nodes;
	char* name;
};

struct gltf_mesh_primitive
{
	int nr_attributes;
	void* attributes;
	int indices;
	int material;
	int mode;
	int nr_targets;
	void* targets;
};

struct gltf_mesh
{
	int nr_primitives;
	struct gltf_mesh_primitive* primitives;
	int nr_weights;
	float* weights;
	char* name;
};

struct gltf_animation_channel_target
{
	int node;
	char* path;

};

struct gltf_animation_channel
{
	int sampler;
	struct gltf_animation_channel_target target;
};


enum gltf_animation_sampler_interpolation
{
	GLTF_ANIMATION_SAMPLER_INTERPOLATION_LINEAR,
	GLTF_ANIMATION_SAMPLER_INTERPOLATION_STEP,
	GLTF_ANIMATION_SAMPLER_INTERPOLATION_CUBICSPLINE,
};

struct gltf_animation_sampler
{
	int input;
	enum gltf_animation_sampler_interpolation interpolation;
	int output;
};


struct gltf_animation
{
	int nr_channels;
	struct gltf_animation_channel* channels;
	int nr_samplers;
	struct gltf_animation_sampler* samplers;
	char* name;
};

struct gltf_skin
{
	int inverseBindMatrices;
	int skeleton;
	int nr_joints;
	int* joints;
	char* name;
};

struct gltf_accessor_sparse_indices
{
	int bufferView;
	int byteOffset;
	int componenetType;
};

struct gltf_accessor_sparse_values
{
	int bufferView;
	int byteOffset;
};

struct gltf_accessor_sparse
{
	int count;
	struct gltf_accessor_sparse_indices indices;
	struct gltf_accessor_sparse_values values;
};

struct gltf_accessor
{
	int bufferView;
	int bufferOffset;
	int componentType;
	int normalize;
	int count;
	int type;
	float* max;
	float* min;
	struct gltf_accessor_sparse* sparse;
	char* name;
};

struct gltf_textureinfo
{
	int index;
	int texCoord;
};

struct gltf_material_normaltextureinfo
{
	int index;
	int texCoord;
	float scale;
};

struct gltf_material_occlusiontextureinfo
{
	int index;
	int texCoord;
	float strength;
};

struct gltf_material_pbrmetallicroughness
{
	float baseColorFactor[4];
	struct gltf_textureinfo baseColorTexture;
	float metallicFactor;
	float roughnessFactor;
	struct gltf_textureinfo metallicRoughnessTexture;
};


enum gltf_material_alphamode
{
	GLTF_MATERIAL_ALPHAMODE_OPAQUE,
	GLTF_MATERIAL_ALPHAMODE_MASK,
	GLTF_MATERIAL_ALPHAMODE_BLEND,
};

struct gltf_material
{
	char* name;
	struct gltf_material_pbrmetallicroughness pbrMetallicRoughness;
	struct gltf_material_normaltextureinfo normalTexture;
	struct gltf_material_occlusiontextureinfo occlusionTexture;
	struct gltf_textureinfo emissiveTexture;
	float emissiveFactor[3];
	enum gltf_material_alphamode alphaMode;
	float alphaCutoff;
	int doubleSided;

};

struct gltf_texture
{
	int sampler;
	int source;
	char* name;
};

enum gltf_image_mimetype
{
	GLTF_IMAGE_MIMETYPE_IMAGE_JPEG,
	GLTF_IMAGE_MIMETYPE_IMAGE_PNG,
};

struct gltf_image
{
	char* uri;
	enum gltf_image_mimetype mimeType;
	int bufferView;
	char* name;
};

struct gltf_sampler
{
	int magFilter;
	int minFilter;
	int wrapS;
	int wrapT;
	char* name;
};

struct gltf_bufferview
{
	int buffer;
	int byteOffset;
	int byteLength;
	int byteStride;
	int target;
	char* name;

};

struct gltf_buffer
{
	char* uri;
	int byteLength;
	char* name;
};

struct gltf_camera_orthographic
{
	float xmag;
	float ymag;
	float zfar;
	float znear;

};

struct gltf_camera_perspective
{
	float aspectRatio;
	float yfov;
	float zfar;
	float znear;
};

enum gltf_camera_type
{
	GLTF_CAMERA_TYPE_PERSPECTIVE,
	GLTF_CAMERA_TYPE_ORTHOGRAPHIC,
};

struct gltf_camera
{
	struct gltf_camera_orthographic orthographic;
	struct gltf_camera_perspective perspective;
	enum gltf_camera_type type;
	char* name;

};

struct gltf_object
{
	struct gltf_asset asset;
	int nr_scenes;
	struct gltf_scene* scenes;
	int scene;
	int nr_nodes;
	struct gltf_node* nodes;
	int nr_meshes;
	struct gltf_mesh* meshes;
	int nr_animations;
	struct gltf_animation* animations;
	int nr_skins;
	struct gltf_skin* skins;
	int nr_accessors;
	struct gltf_accessor* accessors;
	int nr_materials;
	struct gltf_material* materials;
	int nr_textures;
	struct gltf_texture* textures;
	int nr_images;
	struct gltf_image* images;
	int nr_samplers;
	struct gltf_sampler* samplers;
	int nr_bufferviews;
	struct gltf_bufferview* bufferviews;
	int nr_buffers;
	struct gltf_buffer* buffers;
	int nr_cameras;
	struct gltf_camera* cameras;
};


static int read_integer(void* element, struct json_object* obj)
{
	int* data = (int*)element;
	*data = json_object_get_int(obj);
	return 0;
}

static int read_number(void* element, struct json_object* obj)
{
	float* data = (float*)element;
	*data = json_object_get_int(obj);
	return 0;
}

static char* get_string(const char* property, struct json_object* obj)
{
	struct json_object* value = NULL;
	json_object_object_get_ex(obj, property, &value);
	return value ? strdup(json_object_get_string(value)) : NULL;
}

static int get_integer(const char* property, struct json_object* obj)
{
	struct json_object* value = NULL;
	json_object_object_get_ex(obj, property, &value);
	return value ? json_object_get_int(value) : -1;
}


static int allocate_array(void** array, int* length, int sizeof_element, const char* property, struct json_object* obj)
{
	struct json_object* elements = NULL;
	
	json_object_object_get_ex(obj, property, &elements);
	
	if(!elements)
		return 1;

	*length = json_object_array_length(elements);
	*array = calloc(1, *length * sizeof_element);

	return 0;
}


static int read_array(void* array, int length, int sizeof_element, const char* property, int (*read_element)(void*, struct json_object*), struct json_object* obj)
{
	struct json_object* elements = NULL;
	
	json_object_object_get_ex(obj, property, &elements);
	
	if(!elements)
		return 1;

	for(int i = 0;i < length;++i)
	{
		read_element((void*)((char*)array + sizeof_element * i), json_object_array_get_idx(elements, i));
	}

	return 0;
}

static int free_array(void* array, int length, int sizeof_element, int (*free_element)(void*))
{
	for(int i = 0;i < length;++i)
	{
		free_element((void*)((char*)array + sizeof_element * i));
	}

	return 0;
}

static int read_asset(struct gltf_asset* gltf_asset, struct json_object* obj)
{
	struct json_object* asset = NULL;

	json_object_object_get_ex(obj, "asset", &asset);

	if(!asset)
		return 1;

	gltf_asset->version = get_string("version", asset);

	if(!gltf_asset->version)
		return 1;

	fprintf(stderr, "version = %s\n", gltf_asset->version);

	gltf_asset->copyright = get_string("copyright", asset);
	gltf_asset->generator = get_string("generator", asset);
	gltf_asset->minVersion = get_string("minVersion", asset);

	return 0;
}

static int free_asset(struct gltf_asset* gltf_asset)
{
	if(gltf_asset->copyright)
		free(gltf_asset->copyright);
	if(gltf_asset->generator)
		free(gltf_asset->generator);
	if(gltf_asset->version)
		free(gltf_asset->version);
	if(gltf_asset->minVersion)
		free(gltf_asset->minVersion);

	return 0;
}


static int read_scene(void* element, struct json_object* obj)
{
	struct gltf_scene* gltf_scene = (struct gltf_scene*)element;
	struct json_object* name = NULL;
	allocate_array((void**)&gltf_scene->nodes, &gltf_scene->nr_nodes, sizeof(int), "nodes", obj);
	read_array((void*)gltf_scene->nodes, gltf_scene->nr_nodes, sizeof(int), "nodes", read_integer, obj);

	json_object_object_get_ex(obj, "name", &name);
	gltf_scene->name = get_string("name", obj);

	return 0;
}

static int free_scene(void* element)
{
	struct gltf_scene* gltf_scene = (struct gltf_scene*)element;

	if(gltf_scene->nodes)
		free(gltf_scene->nodes);
	if(gltf_scene->name)
		free(gltf_scene->name);

	return 0;
}


static int read_node(void* element, struct json_object* obj)
{
	struct gltf_node* gltf_node = (struct gltf_node*)element;

	gltf_node->camera = get_integer("camera", obj);

	allocate_array((void**)&gltf_node->children, &gltf_node->nr_children, sizeof(int), "children", obj);
	read_array((void*)gltf_node->children, gltf_node->nr_children, sizeof(int), "children", read_integer, obj);

	gltf_node->skin = get_integer("skin", obj);
	read_array((void*)&gltf_node->matrix, 16, sizeof(float), "matrix", read_number, obj);
	gltf_node->mesh = get_integer("mesh", obj);
	read_array((void*)&gltf_node->rotation, 4, sizeof(float), "rotation", read_number, obj);
	read_array((void*)&gltf_node->scale, 3, sizeof(float), "scale", read_number, obj);
	read_array((void*)&gltf_node->translate, 3, sizeof(float), "translate", read_number, obj);

	allocate_array((void**)&gltf_node->weights, &gltf_node->nr_weights, sizeof(int), "weights", obj);
	read_array((void*)gltf_node->weights, gltf_node->nr_weights, sizeof(int), "weights", read_integer, obj);

	gltf_node->name = get_string("name", obj);

	return 0;
}

static int free_node(void* element)
{
	struct gltf_node* gltf_node = (struct gltf_node*)element;

	if(gltf_node->children)
		free(gltf_node->children);

	if(gltf_node->weights)
		free(gltf_node->weights);

	if(gltf_node->name)
		free(gltf_node->name);

	return 0;
}


static int read_mesh_primitive(void* element, struct json_object* obj)
{
	// struct gltf_mesh_primitive* gltf_mesh_primitive = (struct gltf_mesh_primitive*)element;

	return 0;
}

static int free_mesh_primitives(void* element)
{
	return 0;
}

static int read_mesh(void* element, struct json_object* obj)
{
	struct gltf_mesh* gltf_mesh = (struct gltf_mesh*)element;

	allocate_array((void*)&gltf_mesh->primitives, &gltf_mesh->nr_primitives, sizeof(struct gltf_mesh_primitive), "primitives", obj);
	read_array((void*)gltf_mesh->primitives, gltf_mesh->nr_primitives, sizeof(struct gltf_mesh_primitive), "primitives", read_mesh_primitive, obj);
	
	allocate_array((void*)&gltf_mesh->weights, &gltf_mesh->nr_weights, sizeof(int), "weights", obj);
	read_array((void*)gltf_mesh->weights, gltf_mesh->nr_weights, sizeof(int), "weights", read_integer, obj);
	
	gltf_mesh->name = get_string("name", obj);

	return 0;
}

static int free_mesh(void* element)
{
	struct gltf_mesh* gltf_mesh = (struct gltf_mesh*)element;

	if(gltf_mesh->primitives)
	{
		free_array(gltf_mesh->primitives, gltf_mesh->nr_primitives, sizeof(struct gltf_mesh_primitive), free_mesh_primitives);
		free(gltf_mesh->primitives);
	}

	if(gltf_mesh->weights)
		free(gltf_mesh->weights);

	if(gltf_mesh->name)
		free(gltf_mesh->name);

	return 0;
}

static int read_animation(void* element, struct json_object* obj)
{
	return 0;
}

static int free_animation(void* element)
{
	return 0;
}

static int read_skin(void* element, struct json_object* obj)
{
	return 0;
}

static int free_skin(void* element)
{
	return 0;
}

struct gltf_object* gltf_object_new(const char* data, int length)
{
	struct gltf_object* gltf_obj = NULL;

	struct json_tokener* tokener = NULL;
	struct json_object* obj = NULL;

	tokener = json_tokener_new();
	obj = json_tokener_parse_ex(tokener, data, length);
	gltf_obj = calloc(1, sizeof(struct gltf_object));

	read_asset(&gltf_obj->asset, obj);

	allocate_array((void**)&gltf_obj->scenes, &gltf_obj->nr_scenes, sizeof(struct gltf_scene), "scenes", obj);
	read_array((void*)gltf_obj->scenes, gltf_obj->nr_scenes, sizeof(struct gltf_scene), "scenes", read_scene, obj);

	gltf_obj->scene = get_integer("scene", obj);

	allocate_array((void**)&gltf_obj->nodes, &gltf_obj->nr_nodes, sizeof(struct gltf_node), "nodes", obj);
	read_array((void*)gltf_obj->nodes, gltf_obj->nr_nodes, sizeof(struct gltf_node), "nodes", read_node, obj);

	allocate_array((void**)&gltf_obj->meshes, &gltf_obj->nr_meshes, sizeof(struct gltf_mesh), "meshes", obj);
	read_array((void*)gltf_obj->meshes, gltf_obj->nr_meshes, sizeof(struct gltf_mesh), "meshes", read_mesh, obj);

	allocate_array((void**)&gltf_obj->animations, &gltf_obj->nr_animations, sizeof(struct gltf_animation), "animations", obj);
	read_array((void*)gltf_obj->animations, gltf_obj->nr_animations, sizeof(struct gltf_animation), "animations", read_animation, obj);

	allocate_array((void**)&gltf_obj->skins, &gltf_obj->nr_skins, sizeof(struct gltf_skin), "skins", obj);
	read_array((void*)gltf_obj->skins, gltf_obj->nr_skins, sizeof(struct gltf_skin), "skins", read_skin, obj);

	json_object_put(obj);
	json_tokener_free(tokener);

	return gltf_obj;
}

int gltf_object_destroy(struct gltf_object* gltf_obj)
{
	free_asset(&gltf_obj->asset);
	free_array(gltf_obj->scenes, gltf_obj->nr_scenes, sizeof(struct gltf_scene), free_scene);
	free(gltf_obj->scenes);
	free_array(gltf_obj->nodes, gltf_obj->nr_nodes, sizeof(struct gltf_node), free_node);
	free(gltf_obj->nodes);
	free_array(gltf_obj->meshes, gltf_obj->nr_meshes, sizeof(struct gltf_mesh), free_mesh);
	free(gltf_obj->meshes);
	free_array(gltf_obj->animations, gltf_obj->nr_animations, sizeof(struct gltf_animation), free_animation);
	free(gltf_obj->animations);
	free_array(gltf_obj->skins, gltf_obj->nr_skins, sizeof(struct gltf_skin), free_skin);
	free(gltf_obj->skins);

	free(gltf_obj);
	return 0;
}

