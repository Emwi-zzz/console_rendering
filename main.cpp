#include "render.cpp"
#include<iostream>
#include<limits>

int main(){
  //cin.tie(0);
  //ios_base::sync_with_stdio(false);
  polygon tr;
  tr.point_1 = vec3(-1.1, 1.1, 1);
  tr.point_2 = vec3(0, 0, 1);
  tr.point_3 = vec3(1.1, 0, 1);

  vector<char> s(WIDTH * HEIGHT + 1, ' ');
  vector<float> z(WIDTH * HEIGHT);
  
  square q(0.5);
  half_cube c(0.7);  
  q = q + vec3(0, 0, 1);
  
  float vd = 0;

  c.rotateOriginXZ(M_PI / 2 - M_PI / 120);
  while(true){

  for(int i = 0; i < 60; i++){
    fill(s.begin(), s.end(), ' ');
    s[WIDTH * HEIGHT] = '\0';
    fill(z.begin(), z.end(), -10000);
    vd += 0.1;

    
    c.rotateOriginXZ(M_PI/ 120);
    c.rotateOriginYZ(M_PI / 8);
    c += vec3(0, sin(vd), 0);
    c.render(s, z);

    c += vec3(0, -sin(vd), 0);

    c.rotateOriginYZ(M_PI / -8);

    
    /*
    tr.rotateOriginXZ(M_PI / 60);
        
    tr.render(s, z);
    */
    //cout << tr.point_1.z << " " << tr.point_1.x << '\n';
/*
    for(int i = 0; i < s.size(); i++){
      cout << s[i];
    }
*/ 
    printf("%s\n", s.data());
    cout << "\n";
    this_thread::sleep_for(std::chrono::milliseconds(1000 / 30)); 

  }
  c.rotateOriginXZ(M_PI / -2);
  }
}
