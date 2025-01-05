#include "render.cpp"
#include<iostream>

int main(){

  polygon tr;
  tr.point_1 = vec3(-1.1, 1.1, 0);
  tr.point_2 = vec3(0, 0, 0);
  tr.point_3 = vec3(1.1, 0, 0);

  vector<char> s(WIDTH * HEIGHT, ' ');
  vector<float> z(WIDTH * HEIGHT);
  
  for(int i = 0; i < 600; i++){
    fill(s.begin(), s.end(), ' ');
    tr.rotateOriginXZ(M_PI / 60);
    cout << tr.point_1.z << " " << tr.point_1.x << '\n';
    
    tr.render(s, z);

    for(int i = 0; i < s.size(); i++){
      cout << s[i];
    }
    this_thread::sleep_for(std::chrono::milliseconds(1000 / 60)); 

    
  }
}
