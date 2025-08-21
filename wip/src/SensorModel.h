// This is my custom vector implementation


// Includes
#include <cstdint>


// User includes
#include "Vector.h"


class SensorModel
{
public:
	SensorModel(Vector3D worldPointingVector);
	void detectedPixel(uint16_t x, uint16_t y);

private:
	static constexpr uint16_t Xres = 2560;		// in pixels
	static constexpr uint16_t Yres = 1440;		// in pixels

	static constexpr double Horz_fov = 85;		// in DEG
	static constexpr double Vert_fov = 54.6;	// in DEG

	static constexpr double principal_X = Xres / 2.0;
	static constexpr double principal_Y = Yres / 2.0;
	static constexpr double focal_length = principal_X / std::tan(toRads(Horz_fov) / 2.0);

	Point3D CameraLocation {};
	Vector3D CameraFrameX {};
	Vector3D CameraFrameY {};
	Vector3D CameraFrameZ {};
	Vector3D DetectedVector {};
	Vector3D WorldPointPixel {};

	inline double toRads(double angle) {return angle * M_PI / 180.0;}; 
};
