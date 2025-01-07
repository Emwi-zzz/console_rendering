#include "render.cpp"
#include<iostream>

int main(){
  //cin.tie(0);
  //ios_base::sync_with_stdio(false);
  polygon tr;
  tr.point_1 = vec3(-1.1, 1.1, 1);
  tr.point_2 = vec3(0, 0, 1);
  tr.point_3 = vec3(1.1, 0, 1);

  vector<char> s(WIDTH * HEIGHT, ' ');
  vector<float> z(WIDTH * HEIGHT);
  
  square q(0.5);
  cube c(0.7);  
  q = q + vec3(0, 0, 1);

  for(int i = 0; i < 300; i++){
    fill(s.begin(), s.end(), ' ');
     
    c.rotateOriginXZ(M_PI/ 60);
    c.render(s, z);

    /*
    tr.rotateOriginXZ(M_PI / 60);
        
    tr.render(s, z);
    */
    cout << tr.point_1.z << " " << tr.point_1.x << '\n';

    for(int i = 0; i < s.size(); i++){
      cout << s[i];
    }
    this_thread::sleep_for(std::chrono::milliseconds(1000 / 30)); 

    
  }
}
