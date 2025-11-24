#include "MyMath.h"
#include <vector>

const unsigned int WINDOW_WIDTH = 1024;
const unsigned int WINDOW_HEIGHT = 768;

void rasterizeTriangle(GamesEngineeringBase::Window& canvas, const Triangle& t, std::vector<float> zBuffer);
void renderLesson1_2D(GamesEngineeringBase::Window& canvas, std::vector<float> zBuffer);
void renderLesson2_Projection(GamesEngineeringBase::Window& canvas, Matrix& projMatrix, Matrix& viewMatrix, std::vector<float> zBuffer);

int main(int argc, char** argv) {
	// Z-buffer
	std::vector<float> zBuffer(WINDOW_WIDTH * WINDOW_HEIGHT, 1.f);

	// Create a canvas
	GamesEngineeringBase::Window canvas;
	canvas.create(WINDOW_WIDTH, WINDOW_HEIGHT, "Rasterizer");

	// Initialize a projection Matrix
	Matrix proj = Matrix::projection(canvas, 100.0f, 0.1f, 45.f);

	// Camera at (0,0,5), looking at (0,0,0)
	Matrix view = Matrix::lookAt(Vec3(0.f, 0.f, 5.f), Vec3(0.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f));

	// Mode Selection for 2D or 3D Rendering
	int currentMode = 0;

	// Main Loop
	while (true) {
		// Clear the canvas
		canvas.clear();

		// Reset Z-Buffer to 1.0f (Infinity/Far)
		std::fill(zBuffer.begin(), zBuffer.end(), 1.0f);

		// Input Handling
		if (canvas.keyPressed(VK_ESCAPE)) break;
		
		if (canvas.keyPressed('1')) {
			std::cout << "Rasterizing 2D Triangle..." << std::endl;
			currentMode = 0;
		}

		if (canvas.keyPressed('2')) {
			std::cout << "Drawing 3D Triangle with Projection..." << std::endl;
			currentMode = 1;
		}

		// Render Logic
		if (currentMode == 0) renderLesson1_2D(canvas, zBuffer);
		else if (currentMode == 1) renderLesson2_Projection(canvas, proj, view, zBuffer);

		// Display the current frame on the canvas
		canvas.present();
	}
	
	// Terminate the program successfully
	return 0;
}

void rasterizeTriangle(GamesEngineeringBase::Window& canvas, const Triangle& t, std::vector<float> zBuffer) {
	Vec4 tr, bl;
	findBounds(canvas, t.v0, t.v1, t.v2, tr, bl);

	float projArea = edgeFunction(t.v0, t.v1, t.v2);
	float area = 1.f / projArea;

	for (int y = (int)bl.y; y < (int)tr.y + 1; y++) {
		for (int x = (int)bl.x; x < (int)tr.x + 1; x++) {
			Vec4 p(x + 0.5f, y + 0.5f, 0);

			float alpha = edgeFunction(t.v1, t.v2, p);
			float beta = edgeFunction(t.v2, t.v0, p);
			float gamma = edgeFunction(t.v0, t.v1, p);

			alpha *= area;
			beta *= area;
			gamma *= area;

			if ((alpha >= 0 && alpha <= 1) && (beta >= 0 && beta <= 1) && (gamma >= 0 && gamma <= 1)) {
				float currentZ = (alpha * t.v0.z) + (beta * t.v1.z) + (gamma * t.v2.z);
				int index = y * 1024 + x;

				if (currentZ < zBuffer[index]) {
					zBuffer[index] = currentZ;
					
					float w0 = t.v0.w;
					float w1 = t.v1.w;
					float w2 = t.v2.w;
					float frag_w = ((alpha * w0) + (beta * w1) + (gamma * w2));

					Colour frag = perspectiveCorrectInterpolateAttribute(
						Colour(0.f, 0.f, 1.f), Colour(0.f, 1.f, 0.f), Colour(1.f, 0.f, 0.f), // The attributes (Colors)
						w0, w1, w2,															 // The 1/w values
						alpha, beta, gamma,													 // The barycentric weights
						frag_w																 // (alpha * w0) + (beta * w1) + (gamma * w2)
					);
					canvas.draw(x, y, frag.r * 255, frag.g * 255, frag.b * 255);
				}
			}
		}
	}
}

// Draw 2D Rasterization
static void renderLesson1_2D(GamesEngineeringBase::Window& canvas, std::vector<float> zBuffer) {
	Vec4 v0(512.f, 184.f);
	Vec4 v1(685.f, 484.f);
	Vec4 v2(339.f, 484.f);
	Triangle t(v0, v1, v2);
	rasterizeTriangle(canvas, t, zBuffer);
}

// Draw 3D Projection
static void renderLesson2_Projection(GamesEngineeringBase::Window& canvas, Matrix& projMatrix, Matrix& viewMatrix, std::vector<float> zBuffer) {
	Vec4 v0(0.0f, 0.3f, 1.0f);
	Vec4 v1(0.3f, -0.3f, 1.0f);
	Vec4 v2(-0.3f, -0.3f, 1.0f);

	Matrix viewProj = projMatrix * viewMatrix;

	auto transform = [&](Vec4 v) -> Vec4 {
		// Matrix Multiply
		Vec4 vProj = viewProj.mul(v);

		// Perspective Divide (divide by w)
		Vec4 vClip = vProj.divideByW();

		// Viewport Transform (-1..1 -> 0..Width)
		float screenX = (vClip[0] + 1.0f) * 0.5f * canvas.getWidth();
		float screenY = (1.f - (vClip[1] + 1.0f) * 0.5f) * canvas.getHeight();

		// Return Transformed Vector
		return Vec4(screenX, screenY, vClip[2], vClip[3]);
	};

	Triangle t(transform(v0), transform(v1), transform(v2));
	rasterizeTriangle(canvas, t, zBuffer);
}