#include "MyMath.h"
#include "GEMLoader.h"
#include <vector>

const unsigned int WINDOW_WIDTH = 1024;
const unsigned int WINDOW_HEIGHT = 768;

void rasterizeTriangle(GamesEngineeringBase::Window& canvas, const Triangle& t, std::vector<float> &zBuffer);
void rasterizeTriangle(GamesEngineeringBase::Window& canvas, const Triangle& t, const Vec4& n0, const Vec4& n1, const Vec4& n2, std::vector<float> &zBuffer);
void renderLesson1_2D(GamesEngineeringBase::Window& canvas, std::vector<float> &zBuffer);
void renderLesson2_Projection(GamesEngineeringBase::Window& canvas, Matrix& projMatrix, Matrix& viewMatrix, std::vector<float> &zBuffer);
void renderBunny(GamesEngineeringBase::Window& canvas, Matrix& viewProj, const std::vector<Vec3>& vertices, const std::vector<Vec3>& normals, std::vector<float>& zBuffer);

int main(int argc, char** argv) {
	// Initialization (load timer object and create a canvas)
	GamesEngineeringBase::Timer timer;
	GamesEngineeringBase::Window canvas;
	canvas.create(WINDOW_WIDTH, WINDOW_HEIGHT, "Rasterizer");

	// Load Bunny Model Meshes and Push Vertex to Vertex List
	std::vector<GEMLoader::GEMMesh> meshes;
	GEMLoader::GEMModelLoader loader;
	loader.load("Resources/bunny.gem", meshes);

	std::vector<Vec3> vertexList;
	std::vector<Vec3> normalList;

	for (int i = 0; i < meshes.size(); i++) {
		for (int j = 0; j < meshes[i].indices.size(); j++) {
			GEMLoader::GEMVec3 vec;
			GEMLoader::GEMVec3 norm;

			int index = meshes[i].indices[j];
			vec = meshes[i].verticesStatic[index].position;
			norm = meshes[i].verticesStatic[index].normal;

			vertexList.push_back(Vec3(vec.x, vec.y, vec.z));
			normalList.push_back(Vec3(norm.x, norm.y, norm.z));
		}
	}

	// z-Buffer and projection Matrix (zFar = 100, zNear = 0.1, theta = 45 degrees)
	std::vector<float> zBuffer(WINDOW_WIDTH * WINDOW_HEIGHT, 1.f);
	Matrix proj = Matrix::projection(canvas, 100.0f, 0.1f, 45.f);
	
	// Mode Selection for 2D, 3D or Bunny Rendering and total time variable
	float time = 0.f;
	int currentMode = 2;  // Render Bunny by default

	// Main Loop
	while (true) {
		time += timer.dt();								  // Calculate time
		canvas.clear();									  // Clear the canvas
		std::fill(zBuffer.begin(), zBuffer.end(), 1.0f);  // Reset z-Buffer

		// Input Handling
		if (canvas.keyPressed(VK_ESCAPE)) break;
		if (canvas.keyPressed('1')) currentMode = 0; // 2D Triangle
		if (canvas.keyPressed('2')) currentMode = 1; // 3D Projection
		if (canvas.keyPressed('3')) currentMode = 2; // Spinning Bunny

		Matrix view;
		if (currentMode == 2) {
			// Spinning Camera
			float radius = 0.5f;
			float camX = radius * cos(time);
			float camZ = radius * sin(time);
			view = Matrix::lookAt(Vec3(camX, 0.f, camZ), Vec3(0.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f));  // Look from (camX, 0, camZ) -> to Origin (0,0,0)
		}
		else view = Matrix::lookAt(Vec3(0.f, 0.f, 5.f), Vec3(0.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f));   // Static Camera

		// Render Logic
		if (currentMode == 0) renderLesson1_2D(canvas, zBuffer);
		else if (currentMode == 1) renderLesson2_Projection(canvas, proj, view, zBuffer);
		else if (currentMode == 2) {
			Matrix viewProj = proj * view;
			renderBunny(canvas, viewProj, vertexList, normalList, zBuffer);
		}
		// Display the current frame on the canvas
		canvas.present();
	}
	// Terminate the program successfully
	return 0;
}

void rasterizeTriangle(GamesEngineeringBase::Window& canvas, const Triangle& t, std::vector<float> &zBuffer) {
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
				int index = y * WINDOW_WIDTH + x;

				if (currentZ < zBuffer[index]) {
					zBuffer[index] = currentZ;
					float w0 = t.v0.w; float w1 = t.v1.w; float w2 = t.v2.w;
					float frag_w = ((alpha * w0) + (beta * w1) + (gamma * w2));

					Colour frag = perspectiveCorrectInterpolateAttribute(
						Colour(0.f, 0.f, 1.f), Colour(0.f, 1.f, 0.f), Colour(1.f, 0.f, 0.f), // The attributes (Colors)
						w0, w1, w2,															 // The 1/w values
						alpha, beta, gamma,													 // The barycentric coordinates
						frag_w																 // (alpha * w0) + (beta * w1) + (gamma * w2)
					);
					canvas.draw(x, y, frag.r * 255, frag.g * 255, frag.b * 255);
				}
			}
		}
	}
}

void rasterizeTriangle(GamesEngineeringBase::Window& canvas, const Triangle& t, const Vec4& n0, const Vec4& n1, const Vec4& n2, std::vector<float>& zBuffer) {
	Vec4 tr, bl;
	findBounds(canvas, t.v0, t.v1, t.v2, tr, bl);

	float projArea = edgeFunction(t.v0, t.v1, t.v2);
	float area = 1.f / projArea;

	Vec4 omega_i = Vec4(1.0f, 1.0f, 0.f, 1.f).normalize();  // Light Direction (e.g., Sun from top-right)
	Colour rho(0.0f, 1.0f, 0.0f);							// Surface Color (Green Bunny)
	Colour L(1.0f, 1.0f, 1.0f);								// Light Intensity (White)
	Colour ambient(0.2f, 0.2f, 0.2f);						// Ambient Light (Grey)

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
				int index = y * WINDOW_WIDTH + x;

				if (currentZ < zBuffer[index]) {
					zBuffer[index] = currentZ;
					float w0 = t.v0.w; float w1 = t.v1.w; float w2 = t.v2.w;
					float frag_w = ((alpha * w0) + (beta * w1) + (gamma * w2));

					// Surface Normal
					Vec4 N = perspectiveCorrectInterpolateAttribute<Vec4>(n0, n1, n2, w0, w1, w2, alpha, beta, gamma, frag_w).normalize();

					// Lighting = (rho / PI) * (L * max(Dot(omega_i, N), 0) + ambient)
					Colour finalColor = (rho / M_PI) * (L * std::max(Dot(omega_i, N), 0.f) + ambient);

					// Draw Pixel
					canvas.draw(x, y, finalColor.r * 255.0f, finalColor.g * 255.0f, finalColor.b * 255.0f);
				}
			}
		}
	}
}

// Draw 2D Rasterization
static void renderLesson1_2D(GamesEngineeringBase::Window& canvas, std::vector<float> &zBuffer) {
	Vec4 v0(512.f, 184.f);
	Vec4 v1(685.f, 484.f);
	Vec4 v2(339.f, 484.f);
	Triangle t(v0, v1, v2);
	rasterizeTriangle(canvas, t, zBuffer);
}

// Draw 3D Projection
static void renderLesson2_Projection(GamesEngineeringBase::Window& canvas, Matrix& projMatrix, Matrix& viewMatrix, std::vector<float> &zBuffer) {
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

// Render Bunny
void renderBunny(GamesEngineeringBase::Window& canvas, Matrix& viewProj, const std::vector<Vec3> &vertices, const std::vector<Vec3>& normals, std::vector<float> &zBuffer) {
	auto transformPos = [&](Vec3 v) -> Vec4 {
		Vec4 v4(v.x, v.y, v.z, 1.f);
		return viewProj.mul(v4); // Return Clip Space (Before Divide)
	};

	auto toScreen = [&](Vec4 vClip) -> Vec4 {
		Vec4 v = vClip.divideByW();
		float screenX = (v[0] + 1.0f) * 0.5f * canvas.getWidth();
		float screenY = (1.f - (v[1] + 1.0f) * 0.5f) * canvas.getHeight();
		return Vec4(screenX, screenY, v[2], v[3]);
	};

	for (size_t i = 0; i < vertices.size(); i+=3) {
		if (i + 2 >= vertices.size()) break;
		Vec4 v0_clip = transformPos(vertices[i]);
		Vec4 v1_clip = transformPos(vertices[i + 1]);
		Vec4 v2_clip = transformPos(vertices[i + 2]);

		if (v0_clip.w < 0.1f || v1_clip.w < 0.1f || v2_clip.w < 0.1f) continue;
		Vec4 v0 = toScreen(v0_clip);
		Vec4 v1 = toScreen(v1_clip);
		Vec4 v2 = toScreen(v2_clip);

		Vec4 n0(normals[i].x, normals[i].y, normals[i].z, 0.0f);
		Vec4 n1(normals[i + 1].x, normals[i + 1].y, normals[i + 1].z, 0.0f);
		Vec4 n2(normals[i + 2].x, normals[i + 2].y, normals[i + 2].z, 0.0f);

		Triangle t(v0, v1, v2);
		rasterizeTriangle(canvas, t, n0, n1, n2, zBuffer);
	}
}