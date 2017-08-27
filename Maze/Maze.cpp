//Maze.cpp
//Adam Kolodko
//04/30/2017

#include <fstream>
#include <vector>
#include <iostream>
#include "Maze.h"

Maze::Maze() {
   m_bad = true;
   m_imgData = nullptr;
   m_pixelArray = nullptr;
}

Maze::Maze(char * fName) {
   m_fName = fName;
   m_bad = false;

   setImgData();
   setHead();
   setPixelArrayLocation();
   setPixelArray();
   setDimensions();
   decodeBits();
}

Maze::~Maze() {
   delete[] m_imgData;
   delete[] m_pixelArray;
}

vector<vector<bool>> Maze::mazeArray() {
   return m_mazeArray;
}

int Maze::width() {
   return m_width;
}

int Maze::height() {
   return m_height;
}

bool Maze::isBad() {
   return m_bad;
}

void Maze::print()
{
   for (auto& row : m_mazeArray) {
      for (auto& col : row) {
         if (!col) cout << "X ";
         else cout << "  ";
      }
      cout << endl;
   }
}

void Maze::setImgData() {
   ifstream fs;
   fs.open(m_fName, ios_base::binary);
   //find file length
   fs.seekg(0, fs.end);
   m_fileSize = fs.tellg();
   fs.seekg(0, fs.beg);
   //set imgData to file size
   m_imgData = new unsigned char[m_fileSize];
   //read file into memory
   fs.read((char *)m_imgData, m_fileSize);

   fs.close();
}

void Maze::setHead() {
   // BMP header is 54 bytes
   memcpy(m_head, m_imgData, 54);
}

void Maze::setPixelArrayLocation() {
   //find location of pixelArray
   m_pixelArrayLocation =
      (int)m_head[10] +
      (((int)m_head[11]) << 8) +
      (((int)m_head[12]) << 16) +
      (((int)m_head[13]) << 24);
}

void Maze::setPixelArray() {
   //copy pixel array into seperate file
   m_pixelArraySize = m_fileSize - m_pixelArrayLocation;
   m_pixelArray = new unsigned char[m_pixelArraySize];
   memcpy(m_pixelArray, &m_imgData[m_pixelArrayLocation], m_pixelArraySize);
}

void Maze::setDimensions() {
   //TOFIX: Cast bytes as proper uint_8_t size
   //TOFIX: Check that m_width/m_height is uint_32_t
   //Dementions are 4bytes large, read first byte, add next bytes + 8bits + 16bits + 24bits
   m_width =
      m_head[18] +
      (m_head[19] << 8) +
      (m_head[20] << 16) +
      (m_head[21] << 24);
   m_height =
      m_head[22] +
      (m_head[23] << 8) +
      (m_head[24] << 16) +
      (m_head[25] << 24);

   //Size Check
   if (m_width > 32) {
      m_bad = true;
   }
}

void Maze::decodeBits() {
   int i, j, k;
   unsigned long long int lineBits;

   if (!isBad()) {
      //set 2d output array 'mazeArray'
      m_mazeArray.resize(m_height);
      for (auto& row : m_mazeArray) {
         row.resize(m_width);
      }

      //read backwards pixelArray
      k = m_pixelArraySize - 1;

      for (i = 0; i < m_height; i++) {

         //convert bytes into long row int
         lineBits =
            (int)m_pixelArray[k] +
            (((int)m_pixelArray[k - 1]) << 8) +
            (((int)m_pixelArray[k - 2]) << 16) +
            (((int)m_pixelArray[k - 3]) << 24);

         //skip used bytes
         k -= 4;

         //remove exess bits
         lineBits = lineBits >> (32 - m_width);

         //convert bits to bool
         for (j = m_width - 1; j >= 0; j--) {
            lineBits & 1 ? m_mazeArray[i][j] = true : m_mazeArray[i][j] = false;
            lineBits = lineBits >> 1;
         }
      }
   }
}
