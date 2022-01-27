#pragma once

#pragma region ==========================    PIPELINES    ================================================

typedef struct Pipeline
{
	unsigned int handle;
	Shader* shader;
}Pipeline;

Pipeline* pipelineCreate();
void pipelineDestroy(Pipeline* pl);
void pipelineStage(Pipeline* pl, GLbitfield stage, Shader* sh);
void pipelineSet(Pipeline* pl);

#pragma endregion


#pragma region ===================================    WORLD RENDERER    ============================================

typedef struct WorldRenderer
{
	unsigned int vertexArray;
	unsigned int vertexBuffer;
	unsigned int colorBuffer;
	mat4s projection;
	int projUniformLocation;
}WorldRenderer;

WorldRenderer* wRendererCreate(int width, int height, Shader* sh);
void wRendererDestroy(WorldRenderer* wr);
void wRendererVertexData(WorldRenderer* wr, int count, float* verts);
void wRendererColorData(WorldRenderer* wr, int count, float* colors);
void wRendererDraw(WorldRenderer* wr);

#pragma endregion
