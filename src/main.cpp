#ifndef MAIN_H
#define MAIN_H

#include "rasterizer.h"
#include "Utils/objects_loader.h"
#include <conio.h>

constexpr double MY_PI = 3.1415926;

inline double DEG2RAD(double deg) { return deg * MY_PI / 180; }

int main(int argc, char **argv)
{

	Camera Camera;

	Rasterizer ras(1600, 900);
	ras.add_camera(Camera);
	Model model("../objects/spot_triangulated_good.obj", "牛牛");
	Texture *texture = new Texture("../objects/Texture/spot_texture.png");
	model.set_Texture(texture);
	model.set_Transform({1.0f, 1.0f, 1.0f}, {0, 140, 0}, {0, 0, 0});

	ras.add_model(model);

	ras.set_fragment_shader(texture_fragment_shader);
	std::cout << "finish_load" << std::endl;
	ras.Handle();

	int key = 0;
	int frame_count = 0;
	ras.output("../output/output.tga");
	// while (key != 'q')
	// {
	// 	ras.clear();
	// 	ras.set_model(get_model_matrix(angle));

	// 	ras.Handle();
	// 	ras.output("../output/output.tga");

	// 	angle += 30.0f;
	// }
	return 0;
}

#endif
