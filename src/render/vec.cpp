#include <algorithm>
#include<cmath>

using namespace std;

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
          return sqrt(x * x + y * y + z * z);
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