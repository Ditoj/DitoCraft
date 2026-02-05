#define GLFW_DLL
#define WIN32_LEAN_AND_MEAN

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include<memory>
#include<algorithm>
#include<chrono>

#include<minecraft/Block.hpp>
#include<minecraft/ColliderCube.hpp>
#include<minecraft/Player.hpp>
#include<minecraft/Camera.hpp>
#include<minecraft/Ray.hpp>
#include<minecraft/BlockManager.hpp>

#include<renderer/renderer.hpp>

#include<vendor/glm/gtc/matrix_transform.hpp>

void CalculateFrameRate(float* read);
int main() {
	srand(time(NULL));

	if(!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	auto monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "DitoCraft", NULL, NULL);

	if(window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glm::vec3 lightPos = glm::vec3(1.f, 2.f, -2.f);

	ditocraft::BlockManager blocks;
	blocks.addBlock({"images/minecraft/light.png"}, "shaders/lightBlock.glsl", lightPos, 0);

	int n = 20;
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < n; j ++) {
			if(j % 3 == 0) blocks.addBlock({"images/minecraft/grass_block.png", "images/minecraft/grass_block_specular.png"}, "shaders/generalBlock.glsl", glm::vec3((float) i, rand()%2, (float) j), 0);
			if(j % 3 == 1) blocks.addBlock({"images/minecraft/oak_log.png", "images/minecraft/oak_log_specular.png"}, "shaders/generalBlock.glsl", glm::vec3((float) i, rand()%2, (float) j), 1);
			if(j % 3 == 2) blocks.addBlock({"images/minecraft/oak_leaves.png", "images/minecraft/oak_leaves_specular.png"}, "shaders/generalBlock.glsl", glm::vec3((float) i, rand()%2, (float) j), 2);
		}
	}

	ditocraft::Player player(window, mode->width, mode->height, 90.f);

	float lastTime = glfwGetTime();
	float deltaTime;

	float yspd = -0.1f, ydec = 0.03f;

	float crosshairVertices[] = {
		-.0056250000,  .01, 0., 1., //top left
		 .0056250000,  .01, 1., 1., //top right
		 .0056250000, -.01, 1., 0., //bottom right
		 .0056250000, -.01, 1., 0., //bottom right
		-.0056250000, -.01, 0., 0., //bottom left
		-.0056250000,  .01, 0., 1., //top left
	};

	vertexBuffer crosshairVBO(crosshairVertices, sizeof(crosshairVertices));
	vertexBufferLayout crosshairLayout;
	crosshairLayout.push<GL_FLOAT>(2);
	crosshairLayout.push<GL_FLOAT>(2);
	vertexArray crosshairVAO;
	crosshairVAO.addBuffer(crosshairVBO, crosshairLayout);
	texture crosshairTexture("images/minecraft/crosshair.png");
	shaderProgram crosshairShader;
	crosshairShader.loadShader("shaders/crosshair.glsl");


	bool sprinting = false;

	ditocraft::Ray mouseRay;

	bool canPlace = true;

	ditocraft::Block* lastBlock = nullptr;

	while(!glfwWindowShouldClose(window)) {
		double currentTime = glfwGetTime();
		float fps;
		CalculateFrameRate(&fps);
		glfwSetWindowTitle(window, std::string("DitoCraft (" + std::to_string(fps) + "fps)").c_str());

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_ALPHA_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(.012, .12, .24, 1.);

		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && player.getCollider().isStandingOnGround()) {
			yspd = .14f;
			ydec = 0.f;
		}

		if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			sprinting = true;
			player.getCamera().setFOV(120.f);
		} else {
				sprinting = false;
				player.getCamera().setFOV(100.f);
			}

		float speedMultiplier = sprinting ? 2.f : 1.f;

		yspd -= ydec;
		ydec += .24f * deltaTime;
		if(yspd < -0.03f) yspd = -0.03f;
		if(ydec < -0.03f) ydec = -0.03f;

		glm::vec3 pos(0.f);
		glm::vec3 forwardMove = glm::normalize(glm::cross(player.getCamera().getWorldUp(), player.getCamera().getRight()));
		if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) pos += forwardMove;
		if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) pos -= forwardMove;
		if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) pos -= player.getCamera().getRight();
		if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) pos += player.getCamera().getRight();
		pos.x *= deltaTime * player.getCamera().getSpeed();
		pos.z *= deltaTime * player.getCamera().getSpeed();

		blocks.update();

		player.setSpeed(glm::vec3(pos.x * speedMultiplier, yspd, pos.z * speedMultiplier));
		player.update(blocks);

		blocks.sortFromCameraView(player.getCamera());

		blocks.setUniform3f("shaders/generalBlock.glsl", "u_lightPos", lightPos);
		blocks.setUniform3f("shaders/generalBlock.glsl", "u_cameraPos", player.getCamera().getPosition());
		blocks.setUniform3f("shaders/lightBlock.glsl", "u_cameraPos", player.getCamera().getPosition());
		blocks.setUniform3f("shaders/lightBlock.glsl", "u_lightColor", glm::vec3(1.f, 0.f, 0.f));
		blocks.draw(player.getCamera());

		mouseRay.castFromCamera(player.getCamera(), blocks.getBlocks(), 5.f);
		if(mouseRay.getRaycastInfo().other != lastBlock && lastBlock != nullptr ) {
			lastBlock->resetDestroyStage();
		}

		if(mouseRay.getRaycastInfo().hit) {
			mouseRay.getRaycastInfo().other->enableOutline();
			if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1)) {
				mouseRay.getRaycastInfo().other->destroy();
			}

			if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) && canPlace) {
				canPlace = false;

				glm::vec3 pos = mouseRay.getRaycastInfo().other->getPosition() + mouseRay.getRaycastInfo().normal;
				if(glm::distance(pos, player.getCollider().getPosition()) > 1.f) {
					if(!ditocraft::ColliderCube::containsPoint(pos + glm::vec3(0.f, .5f, 0.f), player.getCollider())) blocks.addBlock({"images/minecraft/sand_block.png", "images/minecraft/sand_block_specular.png"}, "shaders/generalBlock.glsl", pos, 4);
				}
			}

			if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE) {
				mouseRay.getRaycastInfo().other->resetDestroyStage();
			}
		}

		lastBlock = mouseRay.getRaycastInfo().other;

		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE) {
			canPlace = true;
		}

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		crosshairTexture.bind(0);
		crosshairShader.bind();
		crosshairShader.setUniform1i("u_crosshairTex", 0);
		crosshairVAO.bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}

int _fpsCount = 0;
int fps = 0; // this will store the final fps for the last second

std::chrono::time_point<std::chrono::steady_clock> lastTime = std::chrono::steady_clock::now();

void CalculateFrameRate(float* read) {
    auto currentTime = std::chrono::steady_clock::now();

    const auto elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
    ++_fpsCount;

    if (elapsedTime > 1000000000) {
        lastTime = currentTime;
        fps = _fpsCount;
        _fpsCount = 0;

        *read = fps;
    }
}