#include <cmath>
#include <iostream>
#include <fstream>
#include "Vectors/Vector3.h"

const int width = 1024;
const int height = 768;

//Based on: http://www.lighthouse3d.com/tutorials/maths/ray-sphere-intersection/
bool raySphereIntersection(dvec3 origin, dvec3 ray, dvec3 center, float radius, dvec3 &point) {
    dvec3 oc = center - origin;
    if (oc.dot(ray) <= 0) {
        point = dvec3(0, 0, 0);
        return false;
    }
    float rayLength = ray.length();
    dvec3 projection = ray * (oc.dot(ray) / (rayLength * rayLength));
    dvec3 pointInsideSphere = origin + projection;
    float distance = (pointInsideSphere - center).length();
    if (distance < radius) {
        float c = radius;
        float a = distance;
        float b = std::sqrt(a * a + c * c);
        point = pointInsideSphere - ray.unit() * b;
        return true;
    } else if (distance == radius) {
        point = origin + projection;
        return true;
    }

    return false;
}

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

void orthographicRender(float cameraWidth, float cameraHeight) {
    dvec3 *framebuffer = new dvec3[width * height];
    float pixelSizeX = cameraWidth / width;
    float pixelSizeY = cameraHeight / height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            dvec3 point;
            bool intersect = raySphereIntersection(
                    dvec3(x * pixelSizeX - cameraWidth / 2, y * pixelSizeY - cameraHeight / 2, 0), dvec3(0, 0, -1),
                    dvec3(0, 0, -100), 1, point);
            if (intersect)
                framebuffer[x + y * width] = dvec3(1, 1, 1);
            else
                framebuffer[x + y * width] = dvec3(0, 0, 0);
        }
    }

    saveFrameBuffer(framebuffer, width, height);


    delete[] framebuffer;
}

void perspectiveRender(float fov, float cameraDistance) {
    dvec3 *framebuffer = new dvec3[width * height];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            dvec3 point;
            float screenX = ((x + 0.5) / (float) (width) * 2 - 1) * tan(fov / 2.0) * -cameraDistance;
            float screenY = ((y + 0.5) / (float) (height) * 2 - 1) * tan(fov / 2.0) * -cameraDistance;
            bool intersect = raySphereIntersection(
                    dvec3(0, 0, 0), dvec3(screenX, screenY, -1).unit(),
                    dvec3(0, 0, -5), 1, point);
            if (intersect)
                framebuffer[x + y * width] = dvec3(1, 1, 1);
            else
                framebuffer[x + y * width] = dvec3(0, 0, 0);
        }
    }

    saveFrameBuffer(framebuffer, width, height);


    delete[] framebuffer;
}

int main() {

    // orthographicRender(10, 10);
    perspectiveRender(3.145 / 2, 1);
    return 0;
}
