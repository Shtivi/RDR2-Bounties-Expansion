#pragma once
//little one-line function called '$' to convert $TRING into a hash-key:
//Hash $(std::string str);
//Converts Radians to Degrees
float degToRad(float degs);
//quick function to get distance between 2 points:
float distanceBetween(Vector3 A, Vector3 B);
//quick "get random int in range 0-x" function:
int rndInt(int start, int end);
//VECTOR/FLOAT
Vector3 toVector3(float x, float y, float z);
Vector3 rot_to_direction(Vector3* rot);
Vector3 add(Vector3* vectorA, Vector3* vectorB);
Vector3 multiply(Vector3* vector, float x);
float get_distance(Vector3* pointA, Vector3* pointB);
float get_vector_length(Vector3* vector);

