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
	struct gltf_nodes* nodes;
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

struct gltf_object* gltf_object_new(const char* data, int length)
{
	struct gltf_object* gltf_obj = NULL;

	struct json_tokener* tokener = NULL;
	struct json_object* obj = NULL;

	tokener = json_tokener_new();
	obj = json_tokener_parse_ex(tokener, data, length);
	gltf_obj = calloc(1, sizeof(struct gltf_object));



	json_object_put(obj);
	json_tokener_free(tokener);

	return gltf_obj;
}

int gltf_object_destroy(struct gltf_object* gltf_obj)
{

	free(gltf_obj);
	return 0;
}

