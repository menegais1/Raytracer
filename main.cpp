#include <cmath>
#include <iostream>
#include <fstream>
#include "Vectors/Vector3.h"
#include "Ray.h"
#include <vector>

const int width = 1024;
const int height = 768;
std::vector<Sphere> spheres;
dvec3 *framebuffer = new dvec3[width * height];

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
            framebuffer[x + y * width] = spheres[i].color;
        }
    }
}

void orthographicRender(float cameraWidth, float cameraHeight) {
    float pixelSizeX = cameraWidth / width;
    float pixelSizeY = cameraHeight / height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            framebuffer[x + y * width] = dvec3(0, 0, 0);
            Ray r = Ray(
                    dvec3(x * pixelSizeX - cameraWidth / 2 * width / (float) height, y * pixelSizeY - cameraHeight / 2,
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
            float screenX =
                    ((x + 0.5) / (float) (width) * 2 - 1) * tan(fov / 2.0) * -cameraDistance * width / (float) height;
            float screenY = ((y + 0.5) / (float) (height) * 2 - 1) * tan(fov / 2.0) * -cameraDistance;
            Ray r = Ray(dvec3(0, 0, 0), dvec3(screenX, screenY, -1).unit());
            sceneIntersection(r, x, y);
        }
    }

    saveFrameBuffer(framebuffer, width, height);


    delete[] framebuffer;
}

int main() {


    spheres.emplace_back(dvec3(0, 0, -3), 1, dvec3(1, 0, 0));
    spheres.emplace_back(dvec3(-1, 0, -5), 1, dvec3(0, 1, 0));
    spheres.emplace_back(dvec3(1, 1, -5), 1, dvec3(0, 0, 1));
    //orthographicRender(10, 10);
    perspectiveRender(3.145 / 2, 1);
    return 0;
}
