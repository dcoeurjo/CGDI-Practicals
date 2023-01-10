#include <iostream>
#include <string>
#include <random>
#include <vector>
//Command-line parsing
#include "CLI11.hpp"

//Image filtering and I/O
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

//Global flag to silent verbose messages
bool silent;


int main(int argc, char **argv)
{
  CLI::App app{"rasterizer"};
  std::string outputImage= "output.png";
  app.add_option("-o,--output", outputImage, "Output image")->required();

  CLI11_PARSE(app, argc, argv);
  
  //Image loading
  int width=640,height=480, nbChannels=3;
  std::vector<unsigned char> output(width*height*nbChannels);


  for(auto i = 0 ; i < width ; ++i)
  {
    for(auto j = 0; j < height; ++j)
    {
      auto indexPixel = nbChannels*(width*j+i);
      unsigned char r = 0;
      unsigned char g = 0;
      unsigned char b = 0;
      //Swapping the channels
      output[ indexPixel ] = b;
      output[ indexPixel + 1 ] = g;
      output[ indexPixel + 2 ] = r;
    }
  }
  
  //Final export
  std::cout<<"Exporting.."<<std::endl;
  int errcode = stbi_write_png(outputImage.c_str(), width, height, nbChannels, output.data(), nbChannels*width);
  if (!errcode)
  {
    std::cout<<"Error while exporting the resulting image."<<std::endl;
    exit(errcode);
  }
  
  exit(0);
}
