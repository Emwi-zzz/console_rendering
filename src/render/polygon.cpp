#pragma once
#include "vec.cpp"
#include<vector>
#include <algorithm>

using namespace std;


vec3 SunLight = vec3(1, 0, 0).normalize();

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