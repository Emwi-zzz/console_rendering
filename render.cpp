#pragma once
#include <algorithm>
#include<vector>
#include<iostream>

using namespace std;

const int WIDTH = 168;
const int HEIGHT = 38;

const float SCALE = 0.5;

const float CAM_Z = -2;
const float CAM_F = 1;


class vec2{
  public:
  float x;
  float y;
  
  vec2(float a, float b){
    x = a;
    y = b;
  }
};

class vec3{
  public:
  float x;
  float y;
  float z;

  vec3() : x(0), y(0), z(0) {};

  vec3(float a, float b, float c){
    x = a;
    y = b;
    z = c;
  }
};

vec3 project(vec3 v){
  float scale = 1 / ((v.z - CAM_Z) * CAM_F);
  return vec3(((v.x * scale * SCALE) + 1) * WIDTH * 0.5, ((v.y * scale) + 1) * HEIGHT / 2, v.z);
}

class polygon{
  public:
  vec3 point_1;
  vec3 point_2;
  vec3 point_3;

  void render(vector<char> &screen, vector<float> zbuffer){
    vec3 p1 = project(point_1);
    vec3 p2 = project(point_2);
    vec3 p3 = project(point_3);
    
    cout << p1.x << ' ' << p1.y << ' ' << p1.z << '\n';
    cout << p2.x << ' ' << p2.y << ' ' << p2.z << '\n';
    cout << p3.x << ' ' << p3.y << ' ' << p3.z << '\n';

    cout << "render\n";

    for(int i = int(min({p1.y, p2.y, p3.y})); i < int(max({p1.y, p2.y, p3.y})); i++){
        for(int j = int(min({p1.x, p2.x, p3.x})); j < int(max({p1.x, p2.x, p3.x})); j++){
          cout << i << ' ' << j << ' ' << i * WIDTH + j << '\n'; 
          screen[i * WIDTH + j] = '#';
        }
    }
  }
};




