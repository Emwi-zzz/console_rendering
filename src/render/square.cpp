#pragma once
#include "polygon.cpp"

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