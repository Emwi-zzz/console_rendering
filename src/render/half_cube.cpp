#pragma once
#include "square.cpp"

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