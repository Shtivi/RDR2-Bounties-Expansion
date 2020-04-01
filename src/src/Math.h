#pragma once
//little one-line function called '$' to convert $TRING into a hash-key:
//Hash $(std::string str);

float degToRad(float degs);
float distanceBetween(Vector3 A, Vector3 B);
int rndInt(int start, int end);
Vector3 toVector3(float x, float y, float z);
Vector3 rot_to_direction(Vector3* rot);
Vector3 add(Vector3* vectorA, Vector3* vectorB);
Vector3 multiply(Vector3* vector, float x);
Vector3 cross(Vector3 left, Vector3 right);
Vector3 getUpVector(Entity entity);
Vector3 getRightVector(Entity entity);
float get_distance(Vector3* pointA, Vector3* pointB);
float get_vector_length(Vector3* vector);

Vector3 operator+(Vector3 const& v, Vector3 const& u);
Vector3 operator*(Vector3 const& u, float a);
Vector3 operator*(float a, Vector3 const& u);
Vector3 operator-(Vector3 const& v, Vector3 const& u);
Vector3 operator* (Vector3 const& left, Vector3 const& right);