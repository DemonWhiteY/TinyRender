#ifndef MAIN_H
#define MAIN_H

#include "Sence/camera.h"
#include "rasterizer.h"
#include "Utils/objects_loader.h"
#include <conio.h>

constexpr double MY_PI = 3.1415926;

inline double DEG2RAD(double deg) { return deg * MY_PI / 180; }

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

Eigen::Vector3f normal_fragment_shader(const fragment_shader_payload &payload)
{
	Eigen::Vector3f return_color = (payload.normal.head<3>().normalized() + Eigen::Vector3f(1.0f, 1.0f, 1.0f)) / 2.f;
	Eigen::Vector3f result;
	result << return_color.x() * 255, return_color.y() * 255, return_color.z() * 255;
	return result;
}

Eigen::Vector3f phong_fragment_shader(const fragment_shader_payload &payload)
{
	Eigen::Vector3f ka = Eigen::Vector3f(0.005, 0.005, 0.005);
	Eigen::Vector3f kd = payload.color;
	Eigen::Vector3f ks = Eigen::Vector3f(0.7937, 0.7937, 0.7937);

	auto l1 = light{{20, 20, 20}, {500, 500, 500}};
	auto l2 = light{{-20, 20, 0}, {500, 500, 500}};

	std::vector<light> lights = {l1, l2};
	Eigen::Vector3f amb_light_intensity{20, 20, 20};
	Eigen::Vector3f eye_pos{0, 0, 0};

	float p = 150;

	Eigen::Vector3f color = payload.color;
	Eigen::Vector3f point = payload.view_pos;
	Eigen::Vector3f normal = payload.normal.normalized();

	Eigen::Vector3f result_color = {0, 0, 0};
	Vector3f view_dir = (point).normalized();
	for (auto &light : lights)
	{
		// TODO: For each light source in the code, calculate what the *ambient*, *diffuse*, and *specular*
		// components are. Then, accumulate that result on the *result_color* object.
		float rr = (light.position - point).squaredNorm();
		Vector3f diffsue(0, 0, 0);
		Vector3f specular(0, 0, 0);
		Vector3f ambient(0, 0, 0);
		Vector3f light_dir = (light.position - point).normalized();

		for (size_t i = 0; i < 3; i++)
		{
			Vector3f h = (view_dir + light_dir).normalized(); // half
			float intensity = light.intensity[i] / rr;
			diffsue[i] = kd[i] * intensity * std::max(0.0f, normal.dot(light_dir));
			specular[i] = ks[i] * intensity * std::pow(std::max(0.0f, normal.dot(h)), p);
			ambient[i] = amb_light_intensity[i] * ka[i];
		}
		result_color += diffsue;
		result_color += specular;
		result_color += ambient;
	}

	return result_color * 255.f;
}

Eigen::Vector3f texture_fragment_shader(const fragment_shader_payload &payload)
{
	Eigen::Vector3f return_color = {0, 0, 0};
	if (payload.texture)
	{

		return_color = payload.texture->getColor(payload.tex_coords.x(), payload.tex_coords.y()) / 255.0f;
	}

	Eigen::Vector3f ka = Eigen::Vector3f(0.005, 0.005, 0.005);
	Eigen::Vector3f kd = return_color;
	Eigen::Vector3f ks = Eigen::Vector3f(0.7937, 0.7937, 0.7937);

	auto l1 = light{{20, 20, 20}, {500, 500, 500}};
	auto l2 = light{{-20, 20, 0}, {500, 500, 500}};

	std::vector<light> lights = {l1, l2};
	Eigen::Vector3f amb_light_intensity{20, 20, 20};
	Eigen::Vector3f eye_pos{0, 0, 0};

	float p = 150;

	Eigen::Vector3f color = payload.color;
	Eigen::Vector3f point = payload.view_pos;
	Eigen::Vector3f normal = payload.normal.normalized();

	Eigen::Vector3f result_color = {0, 0, 0};
	Vector3f view_dir = (point).normalized();
	for (auto &light : lights)
	{
		// TODO: For each light source in the code, calculate what the *ambient*, *diffuse*, and *specular*
		// components are. Then, accumulate that result on the *result_color* object.
		float rr = (light.position - point).squaredNorm();
		Vector3f diffsue(0, 0, 0);
		Vector3f specular(0, 0, 0);
		Vector3f ambient(0, 0, 0);
		Vector3f light_dir = (light.position - point).normalized();

		for (size_t i = 0; i < 3; i++)
		{
			Vector3f h = (view_dir + light_dir).normalized(); // half
			float intensity = light.intensity[i] / rr;
			diffsue[i] = kd[i] * intensity * std::max(0.0f, normal.dot(light_dir));
			specular[i] = ks[i] * intensity * std::pow(std::max(0.0f, normal.dot(h)), p);
			ambient[i] = amb_light_intensity[i] * ka[i];
		}
		result_color += diffsue;
		result_color += specular;
		result_color += ambient;
	}

	return result_color * 255.f;
}

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos, Eigen::Vector3f target, Eigen::Vector3f up)
{
	Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

	// 计算摄像机的三个坐标轴
	Eigen::Vector3f forward = (eye_pos - target).normalized();	// 计算前向
	Eigen::Vector3f right = up.cross(forward).normalized();		// 右向（上向与前向叉积）
	Eigen::Vector3f new_up = forward.cross(right).normalized(); // 重新计算上向

	// 旋转矩阵：将世界坐标系转换到摄像机坐标系
	Eigen::Matrix4f rotate;
	rotate << right[0], new_up[0], forward[0], 0,
		right[1], new_up[1], forward[1], 0,
		right[2], new_up[2], forward[2], 0,
		0, 0, 0, 1;

	// 计算平移矩阵
	Eigen::Matrix4f translate;
	translate << 1, 0, 0, -eye_pos[0],
		0, 1, 0, -eye_pos[1],
		0, 0, 1, -eye_pos[2],
		0, 0, 0, 1;

	// 视图矩阵 = 旋转矩阵 * 平移矩阵
	view = rotate * translate;

	return view;
}

Eigen::Matrix4f get_model_matrix(float angle)
{
	Eigen::Matrix4f rotation;
	angle = angle * MY_PI / 180.f;
	rotation << cos(angle), 0, sin(angle), 0,
		0, 1, 0, 0,
		-sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1;

	Eigen::Matrix4f scale;
	scale << 2, 0, 0, 0,
		0, 2, 0, 0,
		0, 0, 2, 0,
		0, 0, 0, 2;

	Eigen::Matrix4f translate;
	translate << 1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;

	return translate * rotation * scale;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio, float zNear, float zFar)
{
	// TODO: Copy-paste your implementation from the previous assignment.
	Eigen::Matrix4f projection;
	float top = -tan(DEG2RAD(eye_fov / 2.0f) * abs(zNear));
	float right = top * aspect_ratio;

	projection << zNear / right, 0, 0, 0,
		0, zNear / top, 0, 0,
		0, 0, (zNear + zFar) / (zNear - zFar), (2 * zNear * zFar) / (zFar - zNear),
		0, 0, 1, 0;
	return projection;
}

int main(int argc, char **argv)
{

	Camera Camera;
	float angle = -140.0f;
	Rasterizer ras(1600, 900);
	ras.set_model(get_model_matrix(angle));
	ras.set_view(get_view_matrix(Camera.get_position(), Camera.get_target(), Camera.get_up()));
	ras.set_projection(get_projection_matrix(Camera.get_eye_fov(), Camera.get_aspect_ratio(), Camera.get_zNear(), Camera.get_zFar()));

	std::vector<Vector3f> position, color, normal;
	std::vector<Vector3i> index;
	std::vector<Vector2f> uv;
	objects_loader loader;
	loader.load_obj("../objects/spot_triangulated_good.obj", position, index, normal, uv);

	ras.add_pos_buf(0, position);
	ras.add_ind_buf(0, index);
	ras.add_col_buf(0, color);
	ras.add_nor_buf(0, normal);
	ras.add_tex_buf(0, uv);
	Texture *texture = new Texture("../objects/Texture/spot_texture.png");

	ras.set_texture(texture);
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
