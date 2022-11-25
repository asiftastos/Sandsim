#include <stdlib.h>
#include <assert.h>
#include "glad.h"
#include "cglm/struct.h"
#include "assets.h"
#include "renderer.h"

#pragma region =====================================    PIPELINES   ========================================================

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

#pragma endregion


#pragma region ===============================    WORLD  RENDERER   ============================================

WorldRenderer * wRendererCreate(int width, int height, Shader* sh)
{
	WorldRenderer* wr = calloc(1, sizeof(WorldRenderer));
	assert(wr != NULL);

	wr->projection = glms_ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 1.0f);
	glCreateBuffers(1, &wr->vertexBuffer);
	glCreateBuffers(1, &wr->colorBuffer);

	glCreateVertexArrays(1, &wr->vertexArray);
	glBindVertexArray(wr->vertexArray);
	glVertexArrayVertexBuffer(wr->vertexArray, 0, wr->vertexBuffer, 0, sizeof(float) * 3);
	glVertexArrayVertexBuffer(wr->vertexArray, 1, wr->colorBuffer, 0, sizeof(float) * 3);

	glEnableVertexArrayAttrib(wr->vertexArray, 0);
	glVertexArrayAttribBinding(wr->vertexArray, 0, 0);
	glVertexArrayAttribFormat(wr->vertexArray, 0, 3, GL_FLOAT, false, 0);

	glEnableVertexArrayAttrib(wr->vertexArray, 1);
	glVertexArrayAttribBinding(wr->vertexArray, 1, 1);
	glVertexArrayAttribFormat(wr->vertexArray, 1, 3, GL_FLOAT, false, 0);

	wr->projUniformLocation = glGetProgramResourceLocation(sh->handle, GL_UNIFORM, "proj");

	return wr;
}

void wRendererDestroy(WorldRenderer* wr)
{
	if (wr)
	{
		glDeleteBuffers(1, &wr->colorBuffer);
		glDeleteBuffers(1, &wr->vertexBuffer);
		glDeleteVertexArrays(1, &wr->vertexArray);
		free(wr);
	}
}

void wRendererVertexData(WorldRenderer* wr, int count, float* verts)
{
	glNamedBufferStorage(wr->vertexBuffer, sizeof(float) * count, verts, 0);
}

void wRendererColorData(WorldRenderer* wr, int count, float* colors)
{
	glNamedBufferStorage(wr->colorBuffer, sizeof(float) * count, colors, 0);
}

void wRendererDraw(WorldRenderer* wr, uint32_t count)
{
	glBindVertexArray(wr->vertexArray);
	glDrawArrays(GL_TRIANGLES, 0, count);
}

#pragma endregion
