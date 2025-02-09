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

	Rasterizer ras(900, 900);

	json_loader json_loader("../test.JSON");
	std::vector<Model *> models = json_loader.get_models();
	std::vector<light> lights = json_loader.get_lights();
	for (auto model : models)
	{
		ras.add_model(*model);
	}

	for (auto light : lights)
	{
		ras.add_light(light);
	}
	ras.add_camera(json_loader.get_camera());
	ras.set_fragment_shader(texture_fragment_shader);
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
