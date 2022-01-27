#pragma once

#include "vec.h"

typedef vec_t(unsigned int) vec_uint_t;

typedef struct Shader
{
	unsigned int handle;
	vec_uint_t shaders;
}Shader;

Shader* shaderCreate();
void shaderDestroy(Shader* sh);
void shaderLoad(Shader* sh, const char* path, unsigned int type);
