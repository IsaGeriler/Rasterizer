#include "math.h"

const unsigned int WINDOW_WIDTH = 1024;
const unsigned int WINDOW_HEIGHT = 768;

int main(int argc, char** argv) {
	// Create a canvas
	GamesEngineeringBase::Window canvas;
	canvas.create(WINDOW_WIDTH, WINDOW_HEIGHT, "Rasterizer");

	// Define Vectors for Triangle Points (z = 0.f, w = 1.f)
	Vec4 v0(512.f, 184.f);
	Vec4 v1(685.f, 484.f);
	Vec4 v2(339.f, 484.f);
	Triangle t(v0, v1, v2);

	// Main Loop
	while (true) {
		canvas.clear();
		if (canvas.keyPressed('Q')) break;

		Vec4 tr, bl;
		findBounds(canvas, t.v0, t.v1, t.v2, tr, bl);

		for (int y = (int)bl.y; y < (int)tr.y + 1; y++) {
			for (int x = (int)bl.x; x < (int)tr.x + 1; x++) {
				Vec4 p(x + 0.5f, y + 0.5f, 0);
				
				float alpha = edgeFunction(t.v1, t.v2, p);
				float beta = edgeFunction(t.v2, t.v0, p);
				float gamma = edgeFunction(t.v0, t.v1, p);

				float projArea = edgeFunction(t.v1, t.v2, t.v0);
				float area = 1.f / projArea;

				alpha *= area;
				beta *= area;
				gamma *= area;

				if ((alpha >= 0 && alpha <= 1) && (beta >= 0 && beta <= 1) && (gamma >= 0 && gamma <= 1)) {
					Colour frag = simpleInterpolateAttribute(Colour(1.f, 0.f, 0.f), Colour(0.f, 1.f, 0.f), Colour(0.f, 0.f, 1.f), alpha, beta, gamma);
					canvas.draw(x, y, frag.r * 255, frag.g * 255, frag.b * 255);
				}
			}
		}
		canvas.present();
	}
	// Terminate the program successfully
	return 0;
}