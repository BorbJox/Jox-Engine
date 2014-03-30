#include "Window.h"
#include "Renderer.h"
#include "Game.h"
#include "Scene.h"

int main() {
	Window w = Window();
	Renderer r = Renderer(w);
	Game g = Game(&r);

	// For speed and time computation
	double time = 0.0;
	const double deltaTime = 0.01;
	double lastTimeChunk = glfwGetTime();
	double lastAccurateTime = lastTimeChunk;
	double accumulator = 0.0;
	int nbFrames = 0;

	// Main loop
	while (!glfwWindowShouldClose(w.getWindow()))
	{
		// Measure frame drawing speed for performance profiling
		double currentTime = glfwGetTime();
		double frameTime = currentTime - lastAccurateTime;
		nbFrames++;
		if (currentTime - lastTimeChunk >= 1.0){ // If last prinf() was more than 1sec ago
			// printf and reset
			//printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTimeChunk += 1.0;
		}
		//If framerate gets lower than 4 fps, limit physics speed.
		if (frameTime > 0.25)
			frameTime = 0.25;
		// Already have the frame time, so can step forward in time.
		lastAccurateTime = currentTime;
		accumulator += frameTime;

		// If the graphical frame took too long to render, catch up with time in physics frames at regular intervals
		while (accumulator >= deltaTime) {
			//One step in physics
			g.getPhysicsController()->doPhysicsStep(deltaTime);
			time += deltaTime;
			accumulator -= deltaTime;
		}
		
		g.update();

		glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);

		r.renderScene();

		glfwSwapBuffers(w.getWindow());
		glfwPollEvents();

		if (glfwGetKey(w.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(w.getWindow(), GL_TRUE);
	}
	
	return 0;
}