#include <cmath>
#include <iostream>
#include <fstream>
#include "Vectors/Vector3.h"
#include "Ray.h"
#include "PointLight.h"
#include <vector>

const int width = 1024;
const int height = 768;
float screenRatio = width / (float) height;
std::vector<Sphere> spheres;
dvec3 *framebuffer = new dvec3[width * height];
std::vector<PointLight> lights;

void saveFrameBuffer(dvec3 *frameBuffer, int width, int height) {
    std::ofstream ofs;
    ofs.open("./out.ppm");
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < height * width; ++i) {
        for (int j = 0; j < 3; j++) {
            ofs << (char) (255 * std::max(0.0, std::min(1.0, frameBuffer[i][j])));
        }
    }
    ofs.close();
}

//As discussed in: https://www.youtube.com/watch?v=naaeH1qbjdQ
dvec3 perfectReflectionVector(dvec3 normal, dvec3 i) {
    return i - (normal * normal.dot(i)) * 2.0;
}

//The lightning is currently based on Phong model
bool sceneIntersection(Ray ray, int x, int y) {
    dvec3 point;
    float distance = 10000;
    framebuffer[x + y * width] = dvec3(0.2, 0.7, 0.8);;
    for (int i = 0; i < spheres.size(); ++i) {
        bool intersect = ray.raySphereIntersection(spheres[i], point);
        if (intersect && std::abs(point.z) < distance) {
            distance = std::abs(point.z);
            dvec3 normal = (point - spheres[i].center).unit();
            float diffuseIntensity = 0;
            float specIntensity = 0;
            for (int j = 0; j < lights.size(); ++j) {
                dvec3 lightDir = (lights[j].position - point).unit();
                dvec3 reflection = perfectReflectionVector(normal, lightDir).unit();
                specIntensity +=
                        lights[j].intensity * std::pow(std::max(0.0, ray.direction.dot(reflection)), 50);
                diffuseIntensity += lights[j].intensity * std::max(0.0, normal.dot(lightDir));
            }
            framebuffer[x + y * width] = spheres[i].color * (diffuseIntensity + specIntensity);
        }
    }
}

void orthographicRender(float cameraWidth, float cameraHeight) {
    float pixelSizeX = cameraWidth / width;
    float pixelSizeY = cameraHeight / height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Ray r = Ray(
                    dvec3((x * pixelSizeX - cameraWidth / 2) * screenRatio, y * pixelSizeY - cameraHeight / 2,
                          0), dvec3(0, 0, -1));
            sceneIntersection(r, x, y);

        }
    }

    saveFrameBuffer(framebuffer, width, height);


    delete[] framebuffer;
}

void perspectiveRender(float fov, float cameraDistance) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            //In this case, since we are converting the image pixels to a normalized space, between [-1,1], we have to account for the aspect ratio
            //so the image wont get stretched

            float worldX = (2 * (x + 0.5) / (float) width - 1) * tan(fov / 2.0) * screenRatio;
            float worldY = -(2 * (y + 0.5) / (float) height - 1) * tan(fov / 2.0);

            Ray r = Ray(dvec3(0, 0, 0), dvec3(worldX, worldY, -1).unit());
            sceneIntersection(r, x, y);
        }
    }

    saveFrameBuffer(framebuffer, width, height);


    delete[] framebuffer;
}

int main() {


    spheres.push_back(Sphere(dvec3(-3, 0, -16), 2, dvec3(0.4, 0.4, 0.3)));
    spheres.push_back(Sphere(dvec3(-1.0, -1.5, -12), 2, dvec3(0.3, 0.1, 0.1)));
    spheres.push_back(Sphere(dvec3(1.5, -0.5, -18), 3, dvec3(0.3, 0.1, 0.1)));
    spheres.push_back(Sphere(dvec3(7, 5, -18), 4, dvec3(0.4, 0.4, 0.3)));

    lights.emplace_back(dvec3(-20, 20, 20), 1.5);
    lights.emplace_back(dvec3(30, 50, -25), 1.8);
    lights.emplace_back(dvec3(30, 20, 30), 1.7);

    perspectiveRender(M_PI / 2.0, 1);
    return 0;
}
