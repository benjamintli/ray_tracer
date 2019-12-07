#include <iostream>
#include <fstream>
#include "headers/scene.h"
#include "headers/object.h"
#include "headers/color.h"
#include "headers/vect.h"

using namespace std;

int main() {
    int height = 500;
    int width = 500;

    Color_t pix_col(0, 0, 0);

    Scene scene = Scene();

    Sphere sphere1(Vec3(200, 250, 220), 50, Color_t(10, 50, 0), SPECULAR);
    Lightsource light1 = Lightsource(Vec3(0, 500, 100), Color_t(255,255,255));
    Circle circle1(Vec3(250, 250, 250), Vec3(0, 0, 1), 275, Color_t(140, 140, 140), SPECULAR);
    Cylinder cylinder1(Vec3(350, 90, 230), Vec3(0,1,0), 50, 275, Color_t(140, 255, 200), REFLECTIVE);

    scene.add(&circle1);
    scene.add(&sphere1);
    scene.add(&cylinder1);
    scene.add(light1);


    ofstream my_Image ("image.ppm");

    if (my_Image.is_open ()) {
        my_Image << "P3\n" << width << " " << height << " 255\n";
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++)  {
                pix_col = scene.trace(i, j);
                my_Image << (int)pix_col.r << ' ' << (int)pix_col.g << ' ' << (int)pix_col.b << "\n";
            }
        }
        my_Image.close();
    }
    else
        cout << "Could not open the file";

    return 0;



}
