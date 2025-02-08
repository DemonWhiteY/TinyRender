#ifndef MAIN_H
#define MAIN_H

#include "rasterizer.h"
#include "Utils/objects_loader.h"
#include <conio.h>
#include "Utils/json_loader.h"
constexpr double MY_PI = 3.1415926;

inline double DEG2RAD(double deg) { return deg * MY_PI / 180; }

int main(int argc, char **argv)
{

	Camera Camera;

	Rasterizer ras(900, 600);
	ras.add_camera(Camera);

	ras.add_camera(Camera);

	json_loader json_loader("../test.JSON");
	std::vector<Model *> models = json_loader.get_models();

	for (auto model : models)
	{
		ras.add_model(*model);
	}

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
