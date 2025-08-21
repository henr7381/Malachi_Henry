// Vector implementation


// Includes
#include <stdio.h>
#include <cmath>


// User includes
#include "SensorModel.hpp"


SensorModel::SensorModel(Vector3D worldPointingVector):
	x {},
	y {},
	z {}
{
	Vector3D up {0, 0, 1};

	CameraFrameZ = worldPointingVector.normalize();
	CameraFrameX = up.cross(CameraFrameZ);
	CameraFrameY = CameraFrameZ.cross(CameraFrameX);	
}


void SensorModel::detectedPixel(uint16_t x, uint16_t y)
{
	DetectedVector.x = y - principal_X;
	DetectedVector.y = x - principal_y;
	DetectedVector.z = focal_length;

	DetectedVector.normalize();

	WorldPointPixel.x = CameraFrameX.x * DetectedVector.x + CameraFrameY.x * DetectedVector.y + CameraFrameZ.x * DetectedVector.z;
	WorldPointPixel.y = CameraFrameX.y * DetectedVector.x + CameraFrameY.y * DetectedVector.y + CameraFrameZ.y * DetectedVector.z;
	WorldPointPixel.z = CameraFrameX.z * DetectedVector.x + CameraFrameY.z * DetectedVector.y + CameraFrameZ.z * DetectedVector.z;

	WorldPointPixel.normalize();





	return;
}
