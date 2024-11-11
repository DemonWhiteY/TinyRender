#include "Sence/camera.h"
#include "rasterizer.h"

constexpr double PI = 3.1415926;

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
	// 将角度转换为弧度
	float radian_fov = eye_fov * PI / 180.0f;

	// 计算透视矩阵的元素
	float tan_fov_2 = tan(radian_fov / 2.0f);

	Eigen::Matrix4f projection = Eigen::Matrix4f::Zero();

	// 填充透视投影矩阵
	projection(0, 0) = 1.0f / (tan_fov_2 * aspect_ratio); // 左右视野
	projection(1, 1) = 1.0f / tan_fov_2;				  // 上下视野
	projection(2, 2) = zFar / (zFar - zNear);			  // 深度映射
	projection(2, 3) = -zNear * zFar / (zFar - zNear);	  // 深度偏移
	projection(3, 2) = 1.0f;							  // 使透视矩阵正常化

	return projection;
}

int main(int argc, char **argv)
{

	Camera Camera;
	Rasterizer ras(40, 40);
	ras.set_model(get_model_matrix(0));
	ras.set_view(get_view_matrix(Camera.get_position(), Camera.get_target(), Camera.get_up()));
	ras.set_projection(get_projection_matrix(Camera.get_eye_fov(), Camera.get_aspect_ratio(), Camera.get_zNear(), Camera.get_zFar()));

	Triangle tri2;
	tri2.setVertex(0, {35, 20, 5});
	tri2.setVertex(1, {5, 5, 35});
	tri2.setVertex(2, {5, 35, 35});
	tri2.setColor(0, 0, 0, 225);
	ras.draw_triangle(tri2);
	Triangle tri;
	tri.setVertex(0, {5, 20, 5});
	tri.setVertex(1, {35, 5, 35});
	tri.setVertex(2, {35, 35, 35});
	tri.setColor(0, 0, 100, 22);
	ras.draw_triangle(tri);

	ras.output("../output/output.tga");
	return 0;
}
