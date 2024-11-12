#ifndef MAIN_H
#define MAIN_H
#include "Sence/camera.h"
#include "rasterizer.h"
#include "objects_loader.h"

constexpr double MY_PI = 3.1415926;

inline double DEG2RAD(double deg) { return deg * MY_PI / 180; }

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

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

Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
	Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
	return model;
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
	Rasterizer ras(1600, 900);
	ras.set_model(get_model_matrix(0));
	ras.set_view(get_view_matrix(Camera.get_position(), Camera.get_target(), Camera.get_up()));
	ras.set_projection(get_projection_matrix(Camera.get_eye_fov(), Camera.get_aspect_ratio(), Camera.get_zNear(), Camera.get_zFar()));

	// std::vector<Vector3f> position = {
	// 	{0.2, 0.4, 0.8},
	// 	{0.8, 0.4, 0.8},
	// 	{0.8, 0.6, 0.2},
	// 	{0.2, 0.4, 0.8},
	// 	{0.2, 0.6, 0.2},
	// 	{0.8, 0.6, 0.2},
	// 	{0.2, 0.3, 0.5},
	// 	{0.8, 0.3, 0.5},
	// 	{0.5, 0.8, 0.5},

	// };
	// std::vector<Vector3i> index = {
	// 	{0, 1, 2},
	// 	{3, 4, 5},
	// 	{6, 7, 8}};

	// std::vector<Vector3f> color = {
	// 	{0, 0, 0},
	// 	{225, 0, 0},
	// 	{0, 100, 5}};

	std::vector<Vector3f> position, color;
	std::vector<Vector3i> index;
	objects_loader loader;
	loader.load_obj("../objects/rock.obj", position, index);

	std::cout << "finish_load" << std::endl;
	ras.add_pos_buf(0, position);
	ras.add_ind_buf(0, index);
	ras.add_col_buf(0, color);

	ras.Handle();

	ras.output("../output/output.tga");
	return 0;
}

#endif
