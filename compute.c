#include "include/gmt.h"
// Radians to degrees
double rad2deg(double rad)
{
	return rad * 180.0 / M_PI;
}

struct compass_and_level compute_compass_and_level_data(double x, double y, double z, double w)
{
	struct compass_and_level ret;
	// Normalize quaternion and compute rotation matrix elements (input order: x y z w)
	double qnorm = sqrt(x * x + y * y + z * z + w * w);
	if (qnorm == 0.0) {
		fprintf(stderr, "Invalid quaternion\n");
		ret.angle = 0.0;
		ret.pitch = 0.0;
		ret.roll = 0.0;
		return ret;
	}
	x /= qnorm;
	y /= qnorm;
	z /= qnorm;
	w /= qnorm;

	double R00 = 1 - 2 * (y * y + z * z);
	double R01 = 2 * (x * y - z * w);
	double R02 = 2 * (x * z + y * w);

	double R10 = 2 * (x * y + z * w);
	double R11 = 1 - 2 * (x * x + z * z);
	double R12 = 2 * (y * z - x * w);

	double R20 = 2 * (x * z - y * w);
	double R21 = 2 * (y * z + x * w);
	double R22 = 1 - 2 * (x * x + y * y);

	// Compute Euler angles (roll=X, pitch=Y, yaw=Z heading) based on quaternion
	// (w,x,y,z) roll (about X)
	double roll = atan2(2 * (w * x + y * z), 1 - 2 * (x * x + y * y));
	// pitch (about Y) clamp to avoid asin domain errors
	double sinp = 2 * (w * y - z * x);
	if (sinp > 1.0)
		sinp = 1.0;
	if (sinp < -1.0)
		sinp = -1.0;
	double pitch = asin(sinp);
	// yaw (about Z / azimuth)
	double yaw = atan2(2 * (w * z + x * y), 1 - 2 * (y * y + z * z));

	// Normalize azimuth to [0,360)
	double azimuth_deg = rad2deg(yaw);
	double azimuth_final = fmod(azimuth_deg + 360.0, 360.0);

	double roll_deg = rad2deg(roll);
	double pitch_deg = rad2deg(pitch);

	// Normalize roll/pitch to [-180,180)
	double norm = 0.0;
	norm = fmod(roll_deg + 180.0, 360.0);
	if (norm < 0) {
		norm += 360.0;
	}
	roll_deg = norm - 180.0;
	norm = fmod(pitch_deg + 180.0, 360.0);
	if (norm < 0) {
		norm += 360.0;
	}
	pitch_deg = norm - 180.0;

	ret.angle = azimuth_final;
	ret.pitch = pitch_deg;
	ret.roll = roll_deg;

	return ret;
}
