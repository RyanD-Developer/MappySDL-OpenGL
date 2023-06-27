#include "GLGraphics.h"
#include "AssetManager.h"
#include "MathHelper.h"

#include <glew.h>
#include <glm.hpp>
#include <gtx/transform.hpp>

namespace SDLFramework {
	void GLGraphics::DrawSprite(GLTexture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, float angle, SDL_RendererFlip flip) {
		float rad = angle * DEG_TO_RAD;
		Vector2 pos = texture->Position(GameEntity::Space::World);

		InitRenderData(texture, srcRect, texture->ID);

		shaderUtil.Use();
		glBindTexture(GL_TEXTURE_2D, texture->ID);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::mat4 scaleMatrix = glm::scale(glm::vec3(dstRect->w, dstRect->h, 1.0f));
		glm::mat4 rotateMatrix = glm::rotate(rad, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 translateMatrix = glm::translate(glm::vec3(pos.x, pos.y, 0.0f));

		GLint loc = shaderUtil.GetUniformLocation("tSampler");
		glUniform1i(loc, 0);

		loc = shaderUtil.GetUniformLocation("scaleMatrix");
		glUniformMatrix4fv(loc, 1, GL_FALSE, &(scaleMatrix[0][0]));
		loc = shaderUtil.GetUniformLocation("rotateMatrix");
		glUniformMatrix4fv(loc, 1, GL_FALSE, &(rotateMatrix[0][0]));
		loc = shaderUtil.GetUniformLocation("translateMatrix");
		glUniformMatrix4fv(loc, 1, GL_FALSE, &(translateMatrix[0][0]));

		loc = shaderUtil.GetUniformLocation("proj");
		glUniformMatrix4fv(loc, 1, GL_FALSE, &(orthoMatrix[0][0]));

		glBindBuffer(GL_ARRAY_BUFFER, texture->ID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GLGraphics::InitRenderData(Texture* texture, SDL_Rect* srcRect, GLuint quadVAO) {
		GLTexture* glTexture = dynamic_cast<GLTexture*>(texture);

		if (glTexture == nullptr) {
			std::cerr << "InitRenderData:: Unable to cast input texture to GLTexture pointer." << std::endl;
			return;
		}

		float height = (float)glTexture->Surface->h;
		float width = (float)glTexture->Surface->w;

		if (quadVAO == 0) {
			glGenBuffers(1, &quadVAO);
		}

		glm::vec2 topRight = glm::vec2(1, 1);
		glm::vec2 topLeft = glm::vec2(0, 1);
		glm::vec2 bottomLeft = glm::vec2(0, 0);
		glm::vec2 bottomRight = glm::vec2(1, 0);

		if (srcRect != nullptr) {
			topRight = glm::vec2((srcRect->x + srcRect->w) / width, (srcRect->y + srcRect->h) / height);
			topLeft = glm::vec2(srcRect->x / width, (srcRect->y + srcRect->h) / height);
			bottomLeft = glm::vec2(srcRect->x / width, srcRect->y / height);
			bottomRight = glm::vec2((srcRect->x + srcRect->w) / width, srcRect->y / height);
		}

		Vertex vertData[6];
		vertData[0].SetPosition(0.5f, 0.5f);
		vertData[0].SetUV(topRight.x, topRight.y);

		vertData[1].SetPosition(-0.5f, 0.5f);
		vertData[1].SetUV(topLeft.x, topLeft.y);

		vertData[2].SetPosition(-0.5f, -0.5f);
		vertData[2].SetUV(bottomLeft.x, bottomLeft.y);

		vertData[3].SetPosition(-0.5f, -0.5f);
		vertData[3].SetUV(bottomLeft.x, bottomLeft.y);

		vertData[4].SetPosition(0.5f, -0.5f);
		vertData[4].SetUV(bottomRight.x, bottomRight.y);

		vertData[5].SetPosition(0.5f, 0.5f);
		vertData[5].SetUV(topRight.x, topRight.y);

		for (int i = 0; i < 6; i++) {
			vertData[i].SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		glBindBuffer(GL_ARRAY_BUFFER, quadVAO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertData), vertData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void GLGraphics::InitLoadShaderData() {
		std::string basePath = SDL_GetBasePath();
		basePath.append("Assets/");

		std::string vShaderPath = basePath + "Shaders/vs.shader";
		std::string fShaderPath = basePath + "Shaders/fs.shader";

		AssetManager::Instance()->LoadShader(vShaderPath.c_str(), fShaderPath.c_str(), nullptr, "Sprite-Default");
		shaderUtil = AssetManager::Instance()->GetShaderUtil("Sprite-Default");
		orthoMatrix = glm::ortho(0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f, -1.0f, 1.0f);
		
		shaderUtil.Use();
		shaderUtil.SetVector2f("vertexPosition", glm::vec2(0, 0));
		shaderUtil.SetMatrix4f("proj", orthoMatrix);
	}

	void GLGraphics::ClearBackBuffer() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLGraphics::Render() {
		SDL_GL_SwapWindow(mWindow);
	}
	
	bool GLGraphics::Init() {
		if (!sInitialized) {
			return false;
		}

		InitLoadShaderData();

		return true;
	}

	GLGraphics::GLGraphics() {
		sInitialized = Init();
	}

	GLGraphics::~GLGraphics() {
	
	}
}