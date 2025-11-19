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


enum gltf_mesh_primitive_mode
{
	GLTF_MESH_PRIMITIVE_MODE_POINTS,
	GLTF_MESH_PRIMITIVE_MODE_LINES,
	GLTF_MESH_PRIMITIVE_MODE_LINE_LOOP,
	GLTF_MESH_PRIMITIVE_MODE_LINE_STRIP,
	GLTF_MESH_PRIMITIVE_MODE_TRIANGLES,
	GLTF_MESH_PRIMITIVE_MODE_TRIANGLE_STRIP,
	GLTF_MESH_PRIMITIVE_MODE_TRIANGLE_FAN,

};


enum gltf_vertex_attribute
{
	GLTF_VERTEX_ATTRIBUTE_POSITION,
	GLTF_VERTEX_ATTRIBUTE_NORMAL,
	GLTF_VERTEX_ATTRIBUTE_TANGENT,
	GLTF_VERTEX_ATTRIBUTE_TEXCOORD_0,
	GLTF_VERTEX_ATTRIBUTE_COLOR_0,
	GLTF_VERTEX_ATTRIBUTE_JOINTS_0,
	GLTF_VERTEX_ATTRIBUTE_WEIGHTS_0,
};

struct gltf_mesh_attribute
{
	enum gltf_vertex_attribute attribute;
	int accessor;
};

struct gltf_mesh_attributes
{
	int nr_attributes;
	struct gltf_mesh_attribute* attributes;
};


struct gltf_mesh_primitive
{
	struct gltf_mesh_attributes attributes;
	int indices;
	int material;
	enum gltf_mesh_primitive_mode mode;
	int nr_targets;
	struct gltf_mesh_attributes* targets;
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

enum gltf_accessor_type
{
	GLTF_ACCESSOR_TYPE_SCALAR,
	GLTF_ACCESSOR_TYPE_VEC2,
	GLTF_ACCESSOR_TYPE_VEC3,
	GLTF_ACCESSOR_TYPE_VEC4,
	GLTF_ACCESSOR_TYPE_MAT2,
	GLTF_ACCESSOR_TYPE_MAT3,
	GLTF_ACCESSOR_TYPE_MAT4
};

enum gltf_accessor_componenet_type
{
	GLTF_ACCESSOR_COMPONENT_TYPE_BYTE,
	GLTF_ACCESSOR_COMPONENT_TYPE_UNSIGNED_BYTE,
	GLTF_ACCESSOR_COMPONENT_TYPE_SHORT,
	GLTF_ACCESSOR_COMPONENT_TYPE_UNSIGNED_SHORT,
	GLTF_ACCESSOR_COMPONENT_TYPE_UNSIGNED_INT,
	GLTF_ACCESSOR_COMPONENT_TYPE_FLOAT
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
	struct gltf_accessor_sparse sparse;
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


enum gltf_sampler_filter
{
	GLTF_SAMPLER_FILTER_NEAREST,
	GLTF_SAMPLER_FILTER_LINEAR,
	GLTF_SAMPLER_FILTER_NEAREST_MIPMAP_NEAREST,
	GLTF_SAMPLER_FILTER_LINEAR_MIPMAP_NEAREST,
	GLTF_SAMPLER_FILTER_NEAREST_MIPMAP_LINEAR,
	GLTF_SAMPLER_FILTER_LINEAR_MIPMAP_LINEAR
};

enum gltf_sampler_wrap
{
	GLTF_SAMPLER_WRAP_CLAMP_TO_EDGE,
	GLTF_SAMPLER_WRAP_MIRRORED_REPEAT,
	GLTF_SAMPLER_WRAP_REPEAT
};

struct gltf_sampler
{
	enum gltf_sampler_filter magFilter;
	enum gltf_sampler_filter minFilter;
	enum gltf_sampler_wrap wrapS;
	enum gltf_sampler_wrap wrapT;
	char* name;
};


enum gltf_bufferview_target
{
	GLTF_BUFFERVIEW_TARGET_ARRAY_BUFFER,
	GLTF_BUFFERVIEW_TARGET_ELEMENT_ARRAY_BUFFER
};

struct gltf_bufferview
{
	int buffer;
	int byteOffset;
	int byteLength;
	int byteStride;
	enum gltf_bufferview_target target;
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

static double get_number(const char* property, struct json_object* obj)
{
	struct json_object* value = NULL;
	json_object_object_get_ex(obj, property, &value);
	return value ? json_object_get_double(value) : -1;
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
	if(!free_element)
		return 0;

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


static enum gltf_vertex_attribute str_to_attr(const char* attribue)
{
	if(!strcmp("POSITION", attribue))
		return GLTF_VERTEX_ATTRIBUTE_POSITION;
	if(!strcmp("NORMAL", attribue))
		return GLTF_VERTEX_ATTRIBUTE_NORMAL;
	if(!strcmp("TANGENT", attribue))
		return GLTF_VERTEX_ATTRIBUTE_TANGENT;
	if(!strcmp("TEXCOORD_0", attribue))
		return GLTF_VERTEX_ATTRIBUTE_TEXCOORD_0;
	if(!strcmp("COLOR_0", attribue))
		return GLTF_VERTEX_ATTRIBUTE_COLOR_0;
	if(!strcmp("JOINTS_0", attribue))
		return GLTF_VERTEX_ATTRIBUTE_JOINTS_0;
	if(!strcmp("WEIGHTS_0", attribue))
		return GLTF_VERTEX_ATTRIBUTE_WEIGHTS_0;

	return GLTF_VERTEX_ATTRIBUTE_POSITION;
}


static int read_mesh_attributes(void* element, struct json_object* obj)
{
	struct gltf_mesh_attributes* gltf_mesh_attributes = (struct gltf_mesh_attributes*)element;

	gltf_mesh_attributes->nr_attributes = json_object_object_length(obj);
	gltf_mesh_attributes->attributes = calloc(gltf_mesh_attributes->nr_attributes, sizeof(struct gltf_mesh_attribute));

	int i = 0;
	json_object_object_foreach(obj, key, val)
	{
		gltf_mesh_attributes->attributes[i].attribute = str_to_attr(key);
		gltf_mesh_attributes->attributes[i].accessor = json_object_get_int(val);
		++i;
	}

	return 0;
}

static int free_mesh_attributes(void* element)
{
	struct gltf_mesh_attributes* gltf_mesh_attributes = (struct gltf_mesh_attributes*)element;

	if(gltf_mesh_attributes->attributes)
		free(gltf_mesh_attributes->attributes);

	return 0;
}


static int read_mesh_primitive(void* element, struct json_object* obj)
{
	struct gltf_mesh_primitive* gltf_mesh_primitive = (struct gltf_mesh_primitive*)element;
	struct json_object* attributes = NULL;

	json_object_object_get_ex(obj, "attributes", &attributes);
	read_mesh_attributes(&gltf_mesh_primitive->attributes, attributes);

	gltf_mesh_primitive->indices = get_integer("indices", obj);
	gltf_mesh_primitive->material = get_integer("material", obj);
	gltf_mesh_primitive->mode = get_integer("mode", obj);

	allocate_array((void*)&gltf_mesh_primitive->targets, &gltf_mesh_primitive->nr_targets, sizeof(struct gltf_mesh_attributes), "targets", obj);
	read_array((void*)gltf_mesh_primitive->targets, gltf_mesh_primitive->nr_targets, sizeof(struct gltf_mesh_attributes), "targets", read_mesh_attributes, obj);

	return 0;
}

static int free_mesh_primitives(void* element)
{
	struct gltf_mesh_primitive* gltf_mesh_primitive = (struct gltf_mesh_primitive*)element;

	free_mesh_attributes(&gltf_mesh_primitive->attributes);
	free_array(gltf_mesh_primitive->targets, gltf_mesh_primitive->nr_targets, sizeof(struct gltf_mesh_attributes), free_mesh_attributes);

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


static int read_animation_channel_target(void* element, struct json_object* obj)
{
	struct gltf_animation_channel_target* gltf_animation_channel_target = (struct gltf_animation_channel_target*)element;

	gltf_animation_channel_target->node = get_integer("node", obj);
	gltf_animation_channel_target->path = get_string("path", obj);

	return 0;
}

static int free_animation_channel_target(void* element)
{
	struct gltf_animation_channel_target* gltf_animation_channel_target = (struct gltf_animation_channel_target*)element;

	if(gltf_animation_channel_target->path)
		free(gltf_animation_channel_target->path);

	return 0;
}

static int read_animation_channel(void* element, struct json_object* obj)
{
	struct gltf_animation_channel* gltf_animation_channel = (struct gltf_animation_channel*)element;
	struct json_object* target = NULL;

	gltf_animation_channel->sampler = get_integer("sampler", obj);
	json_object_object_get_ex(obj, "target", &target);
	read_animation_channel_target(&gltf_animation_channel->target, target);

	return 0;
}

static int free_animation_channel(void* element)
{
	struct gltf_animation_channel* gltf_animation_channel = (struct gltf_animation_channel*)element;

	free_animation_channel_target(&gltf_animation_channel->target);

	return 0;
}

static int read_animation_sampler(void* element, struct json_object* obj)
{
	struct gltf_animation_sampler* gltf_animation_sampler = (struct gltf_animation_sampler*)element;

	gltf_animation_sampler->input = get_integer("input", obj);
	gltf_animation_sampler->interpolation = get_integer("interpolation", obj);
	gltf_animation_sampler->output = get_integer("output", obj);

	return 0;
}

static int read_animation(void* element, struct json_object* obj)
{
	struct gltf_animation* gltf_animation = (struct gltf_animation*)element;

	allocate_array((void**)&gltf_animation->channels, &gltf_animation->nr_channels, sizeof(struct gltf_animation_channel), "channels", obj);
	read_array(gltf_animation->channels, gltf_animation->nr_channels, sizeof(struct gltf_animation_channel), "channels", read_animation_channel, obj);

	allocate_array((void**)&gltf_animation->samplers, &gltf_animation->nr_samplers, sizeof(struct gltf_animation_sampler), "samplers", obj);
	read_array(gltf_animation->samplers, gltf_animation->nr_samplers, sizeof(struct gltf_animation_sampler), "samplers", read_animation_sampler, obj);

	gltf_animation->name = get_string("name", obj);

	return 0;
}


static int free_animation(void* element)
{
	struct gltf_animation* gltf_animation = (struct gltf_animation*)element;

	free_array(gltf_animation->channels, gltf_animation->nr_channels, sizeof(struct gltf_animation_channel), free_animation_channel);
	free(gltf_animation->channels);
	free_array(gltf_animation->samplers, gltf_animation->nr_samplers, sizeof(struct gltf_animation_sampler), NULL);
	free(gltf_animation->samplers);

	return 0;
}

static int read_skin(void* element, struct json_object* obj)
{
	struct gltf_skin* gltf_skin = (struct gltf_skin*)element;

	gltf_skin->inverseBindMatrices = get_integer("inverseBindMatrices", obj);
	gltf_skin->skeleton = get_integer("skeleton", obj);

	allocate_array((void**)&gltf_skin->joints, &gltf_skin->nr_joints, sizeof(int), "joints", obj);
	read_array(gltf_skin->joints, gltf_skin->nr_joints, sizeof(int), "joints", read_integer, obj);

	gltf_skin->name = get_string("name", obj);
	return 0;
}

static int free_skin(void* element)
{
	struct gltf_skin* gltf_skin = (struct gltf_skin*)element;

	if(gltf_skin->name)
		free(gltf_skin->name);
	if(gltf_skin->joints)
		free(gltf_skin->joints);

	return 0;
}


static int sizeof_accessor_type(enum gltf_accessor_type type)
{
	switch(type)
	{
		case GLTF_ACCESSOR_TYPE_SCALAR:
		return 1;
		case GLTF_ACCESSOR_TYPE_VEC2:
		return 2;
		case GLTF_ACCESSOR_TYPE_VEC3:
		return 3;
		case GLTF_ACCESSOR_TYPE_VEC4:
		return 4;
		case GLTF_ACCESSOR_TYPE_MAT3:
		return 9;
		case GLTF_ACCESSOR_TYPE_MAT4:
		return 16;
		default:
		return 0;
	}

	return 0;
}


static int read_accessor_sparse_indices(void* element, struct json_object* obj)
{
	struct gltf_accessor_sparse_indices* gltf_accessor_sparse_indices = (struct gltf_accessor_sparse_indices*)element;

	gltf_accessor_sparse_indices->bufferView = get_integer("bufferView", obj);
	gltf_accessor_sparse_indices->byteOffset = get_integer("byteOffset", obj);
	gltf_accessor_sparse_indices->componenetType = get_integer("componentType", obj);

	return 0;
}

static int read_accessor_sparse_values(void* element, struct json_object* obj)
{
	struct gltf_accessor_sparse_values* gltf_accessor_sparse_values = (struct gltf_accessor_sparse_values*)element;

	gltf_accessor_sparse_values->bufferView = get_integer("bufferView", obj);
	gltf_accessor_sparse_values->byteOffset = get_integer("byteOffset", obj);

	return 0;
}

static int read_accessor_sparse(void* element, struct json_object* obj)
{
	struct gltf_accessor_sparse* gltf_accessor_sparse = (struct gltf_accessor_sparse*)element;

	gltf_accessor_sparse->count = get_integer("count", obj);
	read_accessor_sparse_indices(&gltf_accessor_sparse->indices, obj);
	read_accessor_sparse_values(&gltf_accessor_sparse->values, obj);

	return 0;
}


static int read_accessor(void* element, struct json_object* obj)
{
	struct gltf_accessor* gltf_accessor = (struct gltf_accessor*)element;

	gltf_accessor->bufferView = get_integer("bufferView", obj);
	gltf_accessor->bufferOffset = get_integer("bufferOffset", obj);
	gltf_accessor->componentType = get_integer("componentType", obj);
	gltf_accessor->normalize = get_integer("normalize", obj);
	gltf_accessor->count = get_integer("count", obj);
	gltf_accessor->type = get_integer("type", obj);
	gltf_accessor->max = calloc(sizeof_accessor_type(gltf_accessor->type), sizeof(float));
	gltf_accessor->min = calloc(sizeof_accessor_type(gltf_accessor->type), sizeof(float));
	read_accessor_sparse(&gltf_accessor->sparse, obj);
	gltf_accessor->name = get_string("name", obj);
	return 0;
}

static int free_accessor(void* element)
{
	struct gltf_accessor* gltf_accessor = (struct gltf_accessor*)element;

	if(gltf_accessor->max)
		free(gltf_accessor->max);
	if(gltf_accessor->min)
		free(gltf_accessor->min);
	if(gltf_accessor->name)
		free(gltf_accessor->name);

	return 0;
}


static int read_textureinfo(void* element, struct json_object* obj)
{
	struct gltf_textureinfo* gltf_textureinfo = (struct gltf_textureinfo*)element;

	gltf_textureinfo->index = get_integer("index", obj);
	gltf_textureinfo->texCoord = get_integer("texCoord", obj);

	return 0;
}


static int read_material_pbrmetallicroughness(void* element, struct json_object* obj)
{
	struct gltf_material_pbrmetallicroughness* gltf_material_pbrmetallicroughness = (struct gltf_material_pbrmetallicroughness*)element;
	struct json_object* value = NULL;

	read_array(gltf_material_pbrmetallicroughness->baseColorFactor, 4, sizeof(float), "baseColorFactor", read_number, obj);
	json_object_object_get_ex(obj, "baseColorTexture", &value);
	read_textureinfo(&gltf_material_pbrmetallicroughness->baseColorTexture, value);
	gltf_material_pbrmetallicroughness->metallicFactor = get_number("metallicFactor", obj);
	gltf_material_pbrmetallicroughness->roughnessFactor = get_number("roughnessFactor", obj);
	json_object_object_get_ex(obj, "metallicRoughnessTexture", &value);
	read_textureinfo(&gltf_material_pbrmetallicroughness->metallicRoughnessTexture, value);

	return 0;
}

static int read_material_normaltextureinfo(void* element, struct json_object* obj)
{
	struct gltf_material_normaltextureinfo* gltf_material_normaltextureinfo = (struct gltf_material_normaltextureinfo*)element;

	gltf_material_normaltextureinfo->index = get_integer("index", obj);
	gltf_material_normaltextureinfo->texCoord = get_integer("texCoord", obj);
	gltf_material_normaltextureinfo->scale = get_number("scale", obj);

	return 0;
}

static int read_material_occlusiontextureinfo(void* element, struct json_object* obj)
{
	struct gltf_material_occlusiontextureinfo* gltf_material_occlusiontextureinfo = (struct gltf_material_occlusiontextureinfo*)element;

	gltf_material_occlusiontextureinfo->index = get_integer("index", obj);
	gltf_material_occlusiontextureinfo->texCoord = get_integer("texCoord", obj);
	gltf_material_occlusiontextureinfo->strength = get_number("scale", obj);

	return 0;
}

static int read_material(void* element, struct json_object* obj)
{
	struct gltf_material* gltf_material = (struct gltf_material*)element;
	struct json_object* value = NULL;
	gltf_material->name = get_string("name", obj);

	json_object_object_get_ex(obj, "pbrMetallicRoughness", &value);
	read_material_pbrmetallicroughness(&gltf_material->pbrMetallicRoughness, value);
	json_object_object_get_ex(obj, "normalTexture", &value);
	read_material_normaltextureinfo(&gltf_material->normalTexture, value);
	json_object_object_get_ex(obj, "occlusionTexture", &value);
	read_material_occlusiontextureinfo(&gltf_material->occlusionTexture, value);
	json_object_object_get_ex(obj, "emissiveTexture", &value);
	read_textureinfo(&gltf_material->emissiveTexture, value);
	read_array(gltf_material->emissiveFactor, 3, sizeof(float), "emissiveFactor", read_number, obj);
	gltf_material->alphaMode = get_integer("alphaMode", obj);
	gltf_material->alphaCutoff = get_number("alphaCutoff", obj);
	gltf_material->doubleSided = get_integer("doubleSided", obj);

	return 0;
}

static int free_material(void* element)
{
	struct gltf_material* gltf_material = (struct gltf_material*)element;

	if(gltf_material->name)
		free(gltf_material->name);

	return 0;
}

static int read_texture(void* element, struct json_object* obj)
{
	struct gltf_texture* gltf_texture = (struct gltf_texture*)element;

	gltf_texture->sampler = get_integer("sampler", obj);
	gltf_texture->source = get_integer("source", obj);
	gltf_texture->name = get_string("name", obj);

	return 0;
}

static int free_texture(void* element)
{
	struct gltf_texture* gltf_texture = (struct gltf_texture*)element;

	if(gltf_texture->name)
		free(gltf_texture->name);

	return 0;
}


static int read_image(void* element, struct json_object* obj)
{
	struct gltf_image* gltf_image = (struct gltf_image*)element;

	gltf_image->uri = get_string("uri", obj);
	gltf_image->mimeType = get_integer("mimeType", obj);
	gltf_image->bufferView = get_integer("bufferView", obj);
	gltf_image->name = get_string("name", obj);

	return 0;
}

static int free_image(void* element)
{
	struct gltf_image* gltf_image = (struct gltf_image*)element;

	if(gltf_image->uri)
		free(gltf_image->uri);
	if(gltf_image->name)
		free(gltf_image->name);

	return 0;
}


static enum gltf_sampler_filter int_to_filter(int filter)
{
	switch(filter)
	{
		case 9728:
		return GLTF_SAMPLER_FILTER_NEAREST;
		case 9729:
		return GLTF_SAMPLER_FILTER_LINEAR;
		case 9984:
		return GLTF_SAMPLER_FILTER_NEAREST_MIPMAP_NEAREST;
		case 9985:
		return GLTF_SAMPLER_FILTER_LINEAR_MIPMAP_NEAREST;
		case 9986:
		return GLTF_SAMPLER_FILTER_NEAREST_MIPMAP_LINEAR;
		case 9987:
		return GLTF_SAMPLER_FILTER_LINEAR_MIPMAP_LINEAR;
	}
	return 0;
}

static enum gltf_sampler_wrap int_to_wrap(int wrap)
{
	switch(wrap)
	{
		case 33071:
		return GLTF_SAMPLER_WRAP_CLAMP_TO_EDGE;
		case 33648:
		return GLTF_SAMPLER_WRAP_MIRRORED_REPEAT;
		case 10497:
		return GLTF_SAMPLER_WRAP_REPEAT;
	}

	return 0;
}

static int read_sampler(void* element, struct json_object* obj)
{
	struct gltf_sampler* gltf_sampler = (struct gltf_sampler*)element;

	gltf_sampler->magFilter = int_to_filter(get_integer("magFilter", obj));
	gltf_sampler->minFilter = int_to_filter(get_integer("minFilter", obj));
	gltf_sampler->wrapS = int_to_wrap(get_integer("wrapS", obj));
	gltf_sampler->wrapT = int_to_wrap(get_integer("wrapT", obj));
	gltf_sampler->name = get_string("name", obj);

	return 0;
}

static int free_sampler(void* element)
{
	struct gltf_sampler* gltf_sampler = (struct gltf_sampler*)element;

	if(gltf_sampler->name)
		free(gltf_sampler->name);

	return 0;
}

static enum gltf_bufferview_target int_to_target(int target)
{
	switch(target)
	{
		case 34962:
		return GLTF_BUFFERVIEW_TARGET_ARRAY_BUFFER;
		case 34963:
		return GLTF_BUFFERVIEW_TARGET_ELEMENT_ARRAY_BUFFER;
	}

	return 0;
}

static int read_bufferview(void* element, struct json_object* obj)
{
	struct gltf_bufferview* gltf_bufferview = (struct gltf_bufferview*)element;

	gltf_bufferview->buffer = get_integer("buffer", obj);
	gltf_bufferview->byteOffset = get_integer("byteOffset", obj);
	gltf_bufferview->byteLength = get_integer("byteLength", obj);
	gltf_bufferview->byteStride = get_integer("byteStride", obj);
	gltf_bufferview->target = int_to_target(get_integer("target", obj));
	gltf_bufferview->name = get_string("name", obj);

	return 0;
}

static int free_bufferview(void* element)
{
	struct gltf_bufferview* gltf_bufferview = (struct gltf_bufferview*)element;

	if(gltf_bufferview->name)
		free(gltf_bufferview->name);

	return 0;
}


static int read_buffer(void* element, struct json_object* obj)
{
	struct gltf_buffer* gltf_buffer = (struct gltf_buffer*)element;

	gltf_buffer->uri = get_string("uri", obj);
	gltf_buffer->byteLength = get_integer("byteLength", obj);
	gltf_buffer->name = get_string("name", obj);

	return 0;
}

static int free_buffer(void* element)
{
	struct gltf_buffer* gltf_buffer = (struct gltf_buffer*)element;

	if(gltf_buffer->uri)
		free(gltf_buffer->uri);
	if(gltf_buffer->name)
		free(gltf_buffer->name);

	return 0;
}


static int read_camera_orthographic(void* element, struct json_object* obj)
{
	struct gltf_camera_orthographic* gltf_camera_orthographic = (struct gltf_camera_orthographic*)element;

	gltf_camera_orthographic->xmag = get_number("xmag", obj);
	gltf_camera_orthographic->ymag = get_number("ymag", obj);
	gltf_camera_orthographic->zfar = get_number("zfar", obj);
	gltf_camera_orthographic->znear = get_number("znear", obj);

	return 0;
}

static int read_camera_perspective(void* element, struct json_object* obj)
{
	struct gltf_camera_perspective* gltf_camera_perspective = (struct gltf_camera_perspective*)element;

	gltf_camera_perspective->aspectRatio = get_number("aspectRatio", obj);
	gltf_camera_perspective->yfov = get_number("yfov", obj);
	gltf_camera_perspective->zfar = get_number("zfar", obj);
	gltf_camera_perspective->znear = get_number("znear", obj);

	return 0;
}

static enum gltf_camera_type string_to_type(const char* type)
{
	if(!strcmp("perspective", type))
		return GLTF_CAMERA_TYPE_PERSPECTIVE;
	if(!strcmp("orthographic", type))
		return GLTF_CAMERA_TYPE_ORTHOGRAPHIC;
	return 0;
}

static int read_camera(void* element, struct json_object* obj)
{
	struct gltf_camera* gltf_camera = (struct gltf_camera*)element;
	struct json_object* value = NULL;

	json_object_object_get_ex(obj, "orthographic", &value);
	read_camera_orthographic(&gltf_camera->orthographic, value);
	json_object_object_get_ex(obj, "perspective", &value);
	read_camera_perspective(&gltf_camera->perspective, value);
	json_object_object_get_ex(obj, "type", &value);
	gltf_camera->type = string_to_type(json_object_get_string(value));
	gltf_camera->name = get_string("name", obj);

	return 0;
}

static int free_camera(void* element)
{
	struct gltf_camera* gltf_camera = (struct gltf_camera*)element;

	if(gltf_camera->name)
		free(gltf_camera->name);

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

	allocate_array((void**)&gltf_obj->accessors, &gltf_obj->nr_accessors, sizeof(struct gltf_accessor), "accessors", obj);
	read_array(gltf_obj->accessors, gltf_obj->nr_accessors, sizeof(struct gltf_accessor), "accessors", read_accessor, obj);

	allocate_array((void**)&gltf_obj->materials, &gltf_obj->nr_materials, sizeof(struct gltf_material), "materials", obj);
	read_array(gltf_obj->materials, gltf_obj->nr_materials, sizeof(struct gltf_material), "materials", read_material, obj);

	allocate_array((void**)&gltf_obj->textures, &gltf_obj->nr_textures, sizeof(struct gltf_texture), "textures", obj);
	read_array(gltf_obj->textures, gltf_obj->nr_textures, sizeof(struct gltf_texture), "textures", read_texture, obj);

	allocate_array((void**)&gltf_obj->images, &gltf_obj->nr_images, sizeof(struct gltf_image), "images", obj);
	read_array(gltf_obj->images, gltf_obj->nr_images, sizeof(struct gltf_image), "images", read_image, obj);

	allocate_array((void**)&gltf_obj->samplers, &gltf_obj->nr_samplers, sizeof(struct gltf_sampler), "samplers", obj);
	read_array(gltf_obj->samplers, gltf_obj->nr_samplers, sizeof(struct gltf_sampler), "samplers", read_sampler, obj);

	allocate_array((void**)&gltf_obj->bufferviews, &gltf_obj->nr_bufferviews, sizeof(struct gltf_bufferview), "bufferViews", obj);
	read_array(gltf_obj->bufferviews, gltf_obj->nr_bufferviews, sizeof(struct gltf_bufferview), "bufferViews", read_bufferview, obj);

	allocate_array((void**)&gltf_obj->buffers, &gltf_obj->nr_buffers, sizeof(struct gltf_buffer), "buffers", obj);
	read_array(gltf_obj->buffers, gltf_obj->nr_buffers, sizeof(struct gltf_buffer), "buffers", read_buffer, obj);

	allocate_array((void**)&gltf_obj->cameras, &gltf_obj->nr_cameras, sizeof(struct gltf_camera), "cameras", obj);
	read_array(gltf_obj->cameras, gltf_obj->nr_cameras, sizeof(struct gltf_camera), "cameras", read_camera, obj);


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
	free_array(gltf_obj->accessors, gltf_obj->nr_accessors, sizeof(struct gltf_accessor), free_accessor);
	free(gltf_obj->accessors);
	free_array(gltf_obj->materials, gltf_obj->nr_materials, sizeof(struct gltf_material), free_material);
	free(gltf_obj->materials);
	free_array(gltf_obj->textures, gltf_obj->nr_textures, sizeof(struct gltf_texture), free_texture);
	free(gltf_obj->textures);
	free_array(gltf_obj->images, gltf_obj->nr_images, sizeof(struct gltf_image), free_image);
	free(gltf_obj->images);
	free_array(gltf_obj->samplers, gltf_obj->nr_samplers, sizeof(struct gltf_sampler), free_sampler);
	free(gltf_obj->samplers);
	free_array(gltf_obj->bufferviews, gltf_obj->nr_bufferviews, sizeof(struct gltf_bufferview), free_bufferview);
	free(gltf_obj->bufferviews);
	free_array(gltf_obj->buffers, gltf_obj->nr_buffers, sizeof(struct gltf_buffer), free_buffer);
	free(gltf_obj->buffers);
	free_array(gltf_obj->cameras, gltf_obj->nr_cameras, sizeof(struct gltf_camera), free_camera);
	free(gltf_obj->cameras);

	free(gltf_obj);
	return 0;
}

