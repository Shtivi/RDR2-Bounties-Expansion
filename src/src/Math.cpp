#include "Main.h"

//Converts Radians to Degrees
float degToRad(float degs)
{
	return degs * 3.141592653589793f / 180.f;
}

//little one-line function called '$' to convert $TRING into a hash-key:
Hash $(std::string str) {
	return GAMEPLAY::GET_HASH_KEY(&str[0u]);
}


//quick function to get distance between 2 points: eg - if (distanceBetween(coordsOf(player), targetCoords) < 50)
float distanceBetween(Vector3 A, Vector3 B) {
	return GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(A.x, A.y, A.z, B.x, B.y, B.z, 1);
}

//quick "get random int in range 0-x" function:
int rndInt(int start, int end) {
	return GAMEPLAY::GET_RANDOM_INT_IN_RANGE(start, end);
}

//VECTOR AND FLOAT FUNCTIONS
Vector3 rot_to_direction(Vector3* rot) {
	float radiansZ = rot->z * 0.0174532924f;
	float radiansX = rot->x * 0.0174532924f;
	float num = abs((float)cos((double)radiansX));
	Vector3 dir;
	dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
	dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
	dir.z = (float)sin((double)radiansX);
	return dir;
}

Vector3 toVector3(float x, float y, float z)
{
	Vector3 output;
	output.x = x;
	output.y = y;
	output.z = z;

	return output;
}

Vector3 add(Vector3* vectorA, Vector3* vectorB) {
	Vector3 result;
	result.x = vectorA->x;
	result.y = vectorA->y;
	result.z = vectorA->z;
	result.x += vectorB->x;
	result.y += vectorB->y;
	result.z += vectorB->z;
	return result;
}

Vector3 multiply(Vector3* vector, float x) {
	Vector3 result;
	result.x = vector->x;
	result.y = vector->y;
	result.z = vector->z;
	result.x *= x;
	result.y *= x;
	result.z *= x;
	return result;
}

float get_distance(Vector3* pointA, Vector3* pointB) {
	float a_x = pointA->x;
	float a_y = pointA->y;
	float a_z = pointA->z;
	float b_x = pointB->x;
	float b_y = pointB->y;
	float b_z = pointB->z;
	double x_ba = (double)(b_x - a_x);
	double y_ba = (double)(b_y - a_y);
	double z_ba = (double)(b_z - a_z);
	double y_2 = y_ba * y_ba;
	double x_2 = x_ba * x_ba;
	double sum_2 = y_2 + x_2;
	return(float)sqrt(sum_2 + z_ba);
}

float get_vector_length(Vector3* vector) {
	double x = (double)vector->x;
	double y = (double)vector->y;
	double z = (double)vector->z;
	return(float)sqrt(x * x + y * y + z * z);
}

Vector3 cross(Vector3 left, Vector3 right)
{
	Vector3 result;
	result.x = left.y * right.z - left.z * right.y;
	result.y = left.z * right.x - left.x * right.z;
	result.z = left.x * right.y - left.y * right.x;
	return result;
}

Vector3 getUpVector(Entity entity)
{
	return cross(getRightVector(entity), ENTITY::GET_ENTITY_FORWARD_VECTOR(entity));
}

Vector3 getRightVector(Entity entity)
{
	const double D2R = 0.01745329251994329576923690768489;
	Vector3 rotation = ENTITY::GET_ENTITY_ROTATION(entity, 2);
	double num1 = cos(rotation.y * D2R);
	double x = num1 * cos(-rotation.z * D2R);
	double y = num1 * sin(rotation.z * D2R);
	double z = sin(-rotation.y * D2R);
	return toVector3((float)x, (float)y, (float)z);
}

Vector3 operator+(Vector3 const& v, Vector3 const& u)
{
	Vector3 result;
	result.x = u.x + v.x;
	result.y = u.y + v.y;
	result.z = u.z + v.z;
	return result;
}

Vector3 operator*(Vector3 const& u, float a)
{
	Vector3 result;
	result.x = u.x * a;
	result.y = u.y * a;
	result.z = u.z * a;
	return result;
}

Vector3 operator*(float a, Vector3 const& u)
{
	return u * a;
}

Vector3 operator-(Vector3 const& v, Vector3 const& u)
{
	return v + (u * (-1));
}

Vector3 operator* (Vector3 const& left, Vector3 const& right)
{
	Vector3 result;
	result.x = left.y * right.z - left.z * right.y;
	result.y = left.z * right.x - left.x * right.z;
	result.z = left.x * right.y - left.y * right.x;
	return result;
};