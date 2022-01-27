#pragma once

#include "vec.h"

typedef vec_t(unsigned int) vec_uint_t;

typedef struct Shader
{
	unsigned int handle;
	vec_uint_t shaders;
}Shader;

typedef struct Pipeline
{
	unsigned int handle;
	Shader* shader;
}Pipeline;

Shader* shaderCreate();
void shaderDestroy(Shader* sh);
void shaderLoad(Shader* sh, const char* path, unsigned int type);

Pipeline* pipelineCreate();
void pipelineDestroy(Pipeline* pl);
void pipelineStage(Pipeline* pl, GLbitfield stage, Shader* sh);
void pipelineSet(Pipeline* pl);
