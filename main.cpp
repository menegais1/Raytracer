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

bool sceneIntersection(Ray ray, int x, int y) {
    dvec3 point;
    float distance = 10000;
    for (int i = 0; i < spheres.size(); ++i) {
        bool intersect = ray.raySphereIntersection(spheres[i], point);
        if (intersect && std::abs(point.z) < distance) {
            distance = point.z;
            dvec3 normal = (point - spheres[i].center).unit();
            float lightIntensity = 0;
            for (int j = 0; j < lights.size(); ++j) {
                dvec3 lightDir = (lights[j].position - point).unit();
                lightIntensity += lights[j].intensity * std::max(0.0, normal.dot(lightDir));
            }

            framebuffer[x + y * width] = spheres[i].color * lightIntensity;
        }
    }
}

void orthographicRender(float cameraWidth, float cameraHeight) {
    float pixelSizeX = cameraWidth / width;
    float pixelSizeY = cameraHeight / height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            framebuffer[x + y * width] = dvec3(0.4, 0.4, 0.4);
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
            framebuffer[x + y * width] = dvec3(0.4, 0.4, 0.4);
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


    spheres.emplace_back(dvec3(0, 0, -5), 1, dvec3(1, 0, 0));
    spheres.emplace_back(dvec3(-3, 0, -5), 1, dvec3(0, 1, 0));
    spheres.emplace_back(dvec3(1, 3, -4), 1, dvec3(0, 0, 1));

    lights.emplace_back(dvec3(1, 1, -2), 1);

    perspectiveRender(3.145 * 3 / 4.0, 1);
//    orthographicRender(20,20);
    return 0;
}
