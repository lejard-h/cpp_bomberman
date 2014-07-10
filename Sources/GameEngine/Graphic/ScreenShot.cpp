//
// ScreenShot.cpp for  in /home/lelabo_m/rendu/cpp_bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sun Jun 15 13:51:43 2014 Marc Le Labourier
// Last update Sun Jun 15 14:06:00 2014 Marc Le Labourier
//

#include <cstdlib>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include "GraphicContext.hh"
#include "ScreenShot.hh"

Graphic::MyScreenShot::MyScreenShot(const std::string& n, int x, int y) : _name(n)
{
  _x = x;
  _y = y;
}

void	Graphic::MyScreenShot::SetWindow(int x, int y)
{
  _x = x;
  _y = y;
}

void	Graphic::MyScreenShot::TakeScreenShot()
{
  unsigned char *buffer;
  int buf_size = 18 + (_x * _y * 3);
  int i;
  unsigned char temp;
  FILE *out_file;

  // open file for output
  if (!(out_file = fopen(_name.c_str(), "wb")))
    {
      return;
    }

  // allocate mem to read from frame buf
  if (!(buffer = (unsigned char *) calloc(1, buf_size)))
    {
      return;
    }

  // set header info
  buffer[2] = 2;// uncompressed
  buffer[12] = _x & 255;
  buffer[13] = _x >> 8;
  buffer[14] = _y & 255;
  buffer[15] = _y >> 8;
  buffer[16] = 24;// 24 bits per pix

  // read frame buf
  glReadPixels(0, 0, _x, _y, GL_RGB, GL_UNSIGNED_BYTE, buffer + 18);

  // RGB to BGR
  for (i = 18; i < buf_size; i += 3)
    {
      temp = buffer[i];
      buffer[i] = buffer[i + 2];
      buffer[i + 2] = temp;
    }

  // write header + color buf to file
  fwrite(buffer, sizeof(unsigned char), buf_size, out_file);

  // cleanup
  fclose(out_file);
  free(buffer);
}
