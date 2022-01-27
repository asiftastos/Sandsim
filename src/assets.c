#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "glad.h"
#include "assets.h"

static char* loadTextFile(const char* path)
{
	FILE* f = fopen(path, "r");
	if (f == NULL)
	{
		printf("Cannot open file %s\n", path);
		return NULL;
	}

	char* text;
	long len;
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);
	text = calloc(1, len);
	assert(text != NULL);
	size_t r = fread(text, 1, len, f);
	if (r != len && !feof(f))
	{
		printf("Failed to read from %s\n", path);
	}

	fclose(f);

	return text;
}

Shader* shaderCreate()
{
	Shader* sh = calloc(1, sizeof(Shader));
	assert(sh != NULL);

	sh->handle = glCreateProgram();
	vec_init(&sh->shaders);

	return sh;
}

void shaderDestroy(Shader* sh)
{
	if (sh)
	{
		for (int i = 0; i < sh->shaders.length; i++)
		{
			unsigned int h = vec_pop(&sh->shaders);
			glDeleteShader(h);
		}
		vec_deinit(&sh->shaders);
		glDeleteProgram(sh->handle);
		free(sh);
		sh = NULL;
	}
}

void shaderLoad(Shader* sh, const char* path, unsigned int type)
{
	char* source = loadTextFile(path);

	GLuint s = glCreateShader(type);
	glShaderSource(s, 1, (const char**)&source, NULL);
	glCompileShader(s);
	free(source);

	int compile_error = 0;
	glGetShaderiv(s, GL_COMPILE_STATUS, &compile_error);
	if (compile_error == GL_FALSE)
	{
		int len;
		glGetShaderiv(s, GL_INFO_LOG_LENGTH, &len);
		char* log = calloc(len, sizeof(char));
		glGetShaderInfoLog(s, len, NULL, log);
		printf("Shader compile error for %s: %s\n", path, log);
		free(log);
		return;
	}

	vec_push(&sh->shaders, s);
}

Pipeline* pipelineCreate()
{
	Pipeline* pl = calloc(1, sizeof(Pipeline));
	assert(pl != NULL);

	glCreateProgramPipelines(1, &pl->handle);

	return pl;
}

void pipelineDestroy(Pipeline* pl)
{
	if (pl)
	{
		glDeleteProgramPipelines(1, &pl->handle);
		free(pl);
		pl = NULL;
	}
}

void pipelineStage(Pipeline* pl, GLbitfield stage, Shader* sh)
{
	int it;
	unsigned int s;
	vec_foreach(&sh->shaders, s, it)
	{
		glAttachShader(sh->handle, s);
	}
	glProgramParameteri(sh->handle, GL_PROGRAM_SEPARABLE, GL_TRUE);
	glLinkProgram(sh->handle);

	int link_error = 0;
	glGetProgramiv(sh->handle, GL_LINK_STATUS, &link_error);
	if (link_error == GL_FALSE)
	
	{
		int len;
		glGetProgramiv(sh->handle, GL_INFO_LOG_LENGTH, &len);
		char* log = calloc(len, sizeof(char));
		glGetProgramInfoLog(sh->handle, len, NULL, log);
		printf("Shader link error: %s\n", log);
		free(log);
		return;
	}

	glUseProgramStages(pl->handle, stage, sh->handle);
	pl->shader = sh;
}

void pipelineSet(Pipeline* pl)
{
	glUseProgram(0);
	glBindProgramPipeline(pl->handle);
}