#include <vector>
#include "Maze.h"
//Main + Tester
//Node class and node control
using namespace std;
class node {
private:
   bool m_isWall;
   int m_xAxis;
   int m_yAxis;
public:
   node(){}
   ~node() {}
   node(bool isSpace, int x, int y) {
      
   }
};
class nodeContol {
private:
   vector<vector<node>> m_nodeArray;
public:
   nodeContol() {}
   ~nodeContol() {}
   nodeContol(Maze* mazeInput) {
      m_nodeArray.resize(mazeInput->height());
      for (int i = 0; i < mazeInput->height(); i++) {
         for (int j = 0; j < mazeInput->width(); j++) {
            m_nodeArray[i].push_back(node(mazeInput->mazeArray()[i][j], i, j));
         }
      }
   }
};
class path {

};
class intersection {

};



int main() {

   Maze mazeA("Maze.bmp");
   mazeA.print();
   nodeContol nc(&mazeA);
   return 0;
}