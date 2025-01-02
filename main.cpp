#include "render.cpp"
#include<iostream>

int main(){

  polygon tr;
  tr.point_1 = vec3(0, 1.1, 3);
  tr.point_2 = vec3(0, 0, 0);
  tr.point_3 = vec3(1.1, 0, 0);

  vector<char> s(WIDTH * HEIGHT, ' ');
  vector<float> z(WIDTH * HEIGHT);

  tr.render(s, z);

  for(int i = 0; i < s.size(); i++){
    cout << s[i];
  }
}
