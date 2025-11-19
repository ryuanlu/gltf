#ifndef __GLTF_H__
#define __GLTF_H__


struct gltf_object;

struct gltf_object* gltf_object_new(const char* data, int length);
int gltf_object_destroy(struct gltf_object* gltf_obj);



#endif /* __GLTF_H__ */
