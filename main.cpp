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
bool sceneIntersection(Ray ray, dvec3 &point, dvec3 &normal, dvec3 &color) {
    float distance = 10000;
    bool intersect = false;
    dvec3 tmpPoint;
    for (int i = 0; i < spheres.size(); ++i) {
        if (ray.raySphereIntersection(spheres[i], tmpPoint) && std::abs(tmpPoint.z) < distance) {
            point = tmpPoint;
            distance = std::abs(point.z);
            normal = (point - spheres[i].center).unit();
            color = spheres[i].color;
            intersect = true;
        }
    }
    return intersect;
}

void orthographicRender(float cameraWidth, float cameraHeight) {
    float pixelSizeX = cameraWidth / width;
    float pixelSizeY = cameraHeight / height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            framebuffer[x + y * width] = dvec3(0.2, 0.7, 0.8);;
            Ray ray = Ray(
                    dvec3((x * pixelSizeX - cameraWidth / 2) * screenRatio, y * pixelSizeY - cameraHeight / 2,
                          0), dvec3(0, 0, -1));
            dvec3 point, normal, color;
            bool intersect = sceneIntersection(ray, point, normal, color);
            if (intersect) {
                float diffuseIntensity = 0;
                float specIntensity = 0;
                for (int j = 0; j < lights.size(); ++j) {
                    dvec3 lightDir = (lights[j].position - point).unit();
                    dvec3 reflection = perfectReflectionVector(normal, lightDir).unit();
                    specIntensity +=
                            lights[j].intensity * std::pow(std::max(0.0, ray.direction.dot(reflection)), 50);
                    diffuseIntensity += lights[j].intensity * std::max(0.0, normal.dot(lightDir));
                }
                framebuffer[x + y * width] = color * (diffuseIntensity + specIntensity);
            }
        }
    }

    saveFrameBuffer(framebuffer, width, height);


    delete[] framebuffer;
}

void perspectiveRender(float fov, float cameraDistance) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            framebuffer[x + y * width] = dvec3(0.2, 0.7, 0.8);;
            //In this case, since we are converting the image pixels to a normalized space, between [-1,1], we have to account for the aspect ratio
            //so the image wont get stretched

            float worldX = (2 * (x + 0.5) / (float) width - 1) * tan(fov / 2.0) * screenRatio;
            float worldY = -(2 * (y + 0.5) / (float) height - 1) * tan(fov / 2.0);

            Ray ray = Ray(dvec3(0, 0, 0), dvec3(worldX, worldY, -1).unit());
            dvec3 point, normal, color;
            bool intersect = sceneIntersection(ray, point, normal, color);
            if (intersect) {
                float diffuseIntensity = 0;
                float specIntensity = 0;
                for (int j = 0; j < lights.size(); ++j) {
                    dvec3 lightDir = (lights[j].position - point).unit();
                    Ray shadowRay = Ray(point,lightDir);
                    dvec3 shadowPoint,shadowNormal, shadowColor;
                    intersect = sceneIntersection(shadowRay, shadowPoint, shadowNormal, shadowColor);
                    if(!intersect){
                        dvec3 reflection = perfectReflectionVector(normal, lightDir).unit();
                        specIntensity +=
                                lights[j].intensity * std::pow(std::max(0.0, ray.direction.dot(reflection)), 50);
                        diffuseIntensity += lights[j].intensity * std::max(0.0, normal.dot(lightDir));
                    }
                }
                framebuffer[x + y * width] = color * (diffuseIntensity + specIntensity);
            }
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

    lights.emplace_back(dvec3(-20, 20, 20), 1.2);
    lights.emplace_back(dvec3(30, 50, -25), 1.0);
    lights.emplace_back(dvec3(30, 20, 30), 1.0);

    perspectiveRender(M_PI / 2.0, 1);
    return 0;
}
