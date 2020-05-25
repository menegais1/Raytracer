cmake_minimum_required(VERSION 3.16)
project(Raytracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(Raytracer Vectors/Vector2.h Vectors/Vector3.h Vectors/Vector4.h Vectors/Matrix.h main.cpp Ray.cpp Ray.h Sphere.cpp Sphere.h PointLight.cpp PointLight.h Material.cpp Material.h)