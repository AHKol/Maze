//Maze.h
//Adam Kolodko

//Class that holds and creates 2d bool array from monochrome bitmap image
//Max Width 32px

//UPGRADE: check if monochrome
//TODO: Copy Constructor
//TODO: Assignment Opperator
//TODO: Default Constructor
//TODO: Return Maze Struct with h + w + array

#include <vector>

using namespace std;

class Maze {

private:
   vector<vector<bool>> m_mazeArray;
   unsigned char* m_pixelArray;
   unsigned char* m_imgData;
   unsigned char m_head[54];
   char* m_fName;
   int m_width;
   int m_height;
   int m_fileSize;
   int m_pixelArrayLocation;
   int m_pixelArraySize;
   bool m_bad;

   void setImgData();//read file data and put it in array
   void setHead();//req imgData
   void setPixelArrayLocation();//req head
   void setPixelArray();//req location
   void setDimensions();//req head
   void decodeBits();//req pixelArray, demensions

public:
   Maze();
   Maze(char* fName);
   ~Maze();
   vector<vector<bool>> mazeArray();
   int width();
   int height();
   bool isBad();
   void print();
};