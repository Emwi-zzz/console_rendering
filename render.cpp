#pragma once
#include<chrono>
#include<thread>
#include<math.h>
#include <algorithm>
#include<vector>
#include<iostream>

using namespace std;

const int WIDTH = 168;
const int HEIGHT = 38;

const float SCALE = 0.5;

const float CAM_Z = -5;
const float CAM_F = 0.5;


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

  vec3(){
    x = 0;
    y = 0;
    z = 0;
  };

  vec3(float a, float b, float c){
    x = a;
    y = b;
    z = c;
  }

  vec3 operator+(const vec3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

  vec3 operator-(const vec3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    static vec3 cross(const vec3& a, const vec3& b) {
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    }

    static float dot(const vec3& a, const vec3& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    float norm() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    vec3 normalize() const {
        float magnitude = norm();
        return {x / magnitude, y / magnitude, z / magnitude};
    }

    void rotateOriginXY(float angle){
      float cosx = cos(angle);
      float sinx = sin(angle);

      float newX = x * cosx - y * sinx;
      y = x * sinx + y * cosx;
      x = newX;
    }

    void rotateOriginXZ(float angle){
      float cosx = cos(angle);
      float sinx = sin(angle);

      float newX = x * cosx - z * sinx;
      z = x * sinx + z * cosx;
      x = newX;
    }

    void rotateOriginYZ(float angle){
      float cosx = cos(angle);
      float sinx = sin(angle);

      float newY = y * cosx - z * sinx;
      z = y * sinx + z * cosx;
      y = newY;
    }

};

vec3 project(vec3 v){
  float scale = 1 / ((v.z - CAM_Z) * CAM_F);
  return vec3(((v.x * scale * SCALE) + 1) * WIDTH * 0.5, ((v.y * scale) + 1) * HEIGHT / 2, v.z);
}

vec3 SunLight = vec3(1, 1, 1).normalize();

class polygon{
  public:
  vec3 point_1;
  vec3 point_2;
  vec3 point_3;
  
  polygon(){
    ;
  }

  polygon(vec3 p1, vec3 p2, vec3 p3){
    point_1 = p1;
    point_2 = p2;
    point_3 = p3;
  }
  
  void rotateOriginXZ(float angle){
    point_1.rotateOriginXZ(angle);
    point_2.rotateOriginXZ(angle);
    point_3.rotateOriginXZ(angle);
  }
  
  void rotateOriginYZ(float angle){
    point_1.rotateOriginYZ(angle);
    point_2.rotateOriginYZ(angle);
    point_3.rotateOriginYZ(angle);
  }

  void render(vector<char> &screen, vector<float> &zbuffer){
    vec3 p1 = project(point_1);
    vec3 p2 = project(point_2);
    vec3 p3 = project(point_3);
    /*
    cout << p1.x << ' ' << p1.y << ' ' << p1.z << '\n';
    cout << p2.x << ' ' << p2.y << ' ' << p2.z << '\n';
    cout << p3.x << ' ' << p3.y << ' ' << p3.z << '\n';

    cout << "render\n";
    */
    /*
     *  D  =  (y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3)
     *
     *  L1 = ((y2 - y3) * (x  - x3) + (x3 - x2) * (y  - y3)) / D
     *
     *  L2 = ((y3 - y1) * (x  - x3) + (x1 - x3) * (y  - y3)) / D 
     *
    */

    float D = 1 / ((p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y));

    for(int i = int(min({p1.y, p2.y, p3.y}) - 1); i < int(max({p1.y, p2.y, p3.y}) + 1); i++){
        for(int j = int(min({p1.x, p2.x, p3.x}) - 1); j < int(max({p1.x, p2.x, p3.x}) + 1); j++){
          // cout << i << ' ' << j << ' ' << i * WIDTH + j << '\n';
          float L1 = ((p2.y - p3.y) * (j - p3.x) + (p3.x - p2.x) * (i - p3.y)) * D;
          float L2 = ((p3.y - p1.y) * (j - p3.x) + (p1.x - p3.x) * (i - p3.y)) * D;
          if((L1 + L2 <= 1) && L1 > 0  && L2 > 0){
            float z_d = p1.z + (p2.z - p1.z) * L1 + (p3.z - p1.z) * L2;
            
            //float z_d = (1.0 - L1 - L2) * point_1.z + L1 * point_2.z + point_3.z * L2;
            /*
            cout << z_d << '\n';
            cout << i << ' ' << j << '\n'; 
            cout << "L1: " << L1 << " L2: " << L2 << '\n';
            */
            if(zbuffer[i * WIDTH + j] < z_d){
              zbuffer[i * WIDTH + j] = z_d;
              vec3 AB = p2 - p1;
              vec3 AC = p3 - p1;
              vec3 normal = vec3::cross(AB, AC).normalize();

              float cosTheta = vec3::dot(normal, SunLight);
            
            
              int index = (float)(cosTheta * 13);
              index = max({0, index});
              screen[i * WIDTH + j] = ".,-~:;=!*#$@@@@@@@@@@@@@@@@@@@"[index];

            }
                      
          }
        }
    }
  }

  polygon operator+(const vec3& other){
    return{point_1 + other, point_2 + other, point_3 + other};
  }
};

class square{
  public:
  polygon first;

  polygon second;

  square(){
    ;
  } 

  square(polygon f, polygon s){
    first = f;
    second = s;
  }

  square(float half_size){
    vec3 p1(half_size, half_size, 0);
    vec3 p2(half_size, -half_size, 0);
    vec3 p3(-half_size, half_size, 0);
    vec3 p4(-half_size, -half_size, 0);
    first = polygon(p1, p2, p3);
    second = polygon(p4, p3, p2);
  }

  square operator+(const vec3& other){
    return {first + other, second + other};
  }

  void render(vector<char> &screen, vector<float> &zbuffer){
    first.render(screen, zbuffer);
    second.render(screen, zbuffer);
  }

  void rotateOriginXZ(float angle){
    first.rotateOriginXZ(angle);
    second.rotateOriginXZ(angle);
  }

  void rotateOriginYZ(float angle){
    first.rotateOriginYZ(angle);
    second.rotateOriginYZ(angle);
  }

};

class half_cube{
  vector<square> squares;
  public:
  half_cube(float half_size){
    squares.resize(3);
    fill(squares.begin(), squares.end(), (square(half_size) + vec3(0, 0, half_size)));
    squares[1].rotateOriginXZ(M_PI * 0.5);
    squares[2].rotateOriginYZ(M_PI * 0.5);
  }
 
  void rotateOriginXZ(float angle){
    for(int i = 0; i < 3; i++){
      squares[i].rotateOriginXZ(angle);
    }
  }

  void rotateOriginYZ(float angle){
    for(int i = 0; i < 3; i++){
      squares[i].rotateOriginYZ(angle);
    }
  }
  
  void operator+=(const vec3& other){
    for(int i = 0; i < 3; i++){
      squares[i] = squares[i] + other;
    }
    return;
  }
 

  void render(vector<char> &screen, vector<float> &zbuffer){
    for(int i = 0; i < 3; i++){
      //cout << "render " << i << '\n';
      squares[i].render(screen, zbuffer);
    }
  }

};

class cube{
  vector<square> squares;
  public:
  cube(float half_size){
    squares.resize(6);
    fill(squares.begin(), squares.end(), (square(half_size) + vec3(0, 0, half_size)));
    squares[1].rotateOriginXZ(M_PI * 0.5);
    squares[2].rotateOriginXZ(M_PI);
    squares[3].rotateOriginXZ(M_PI * 1.5);
    squares[4].rotateOriginYZ(M_PI * 0.5);
    squares[5].rotateOriginYZ(M_PI * -0.5);
  }
 
  void rotateOriginXZ(float angle){
    for(int i = 0; i < 6; i++){
      squares[i].rotateOriginXZ(angle);
    }
  }

  void rotateOriginYZ(float angle){
    for(int i = 0; i < 6; i++){
      squares[i].rotateOriginYZ(angle);
    }
  }
  
  void operator+=(const vec3& other){
    for(int i = 0; i < 6; i++){
      squares[i] = squares[i] + other;
    }
    return;
  }
 

  void render(vector<char> &screen, vector<float> &zbuffer){
    for(int i = 0; i < 6; i++){
      cout << "render " << i << '\n';
      squares[i].render(screen, zbuffer);
    }
  }

};

