/*
File: map.cpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: The Map class contains a three dimensional array of Wall objects
  in a dynamically allocated array. This map can be rendered in a 2-d format
  where the walls are draw as a grid system. The other option is a 3-d render
  where the walls are draw using a technique called ray casting.

  Ray Casting Link: https://en.wikipedia.org/wiki/Ray_casting

*/

#ifndef Map_cpp
#define Map_cpp

#include "map.hpp"

// constructor for Map object
Map::Map()
{
  //nfloors repesents the number of levels the map has
  nfloors = 0;
  //width is the width of the map
  width = 0;
  //length is the length of the map
  length = 0;
  //bsize repesents a single side length of the square walls
  bsize = 0;
  //floors stores all the wall objects
  floors = NULL;
}

//simple destructor, delets all dynamically allocated variables
Map::~Map()
{
  for(int i = 0; i < nfloors; i++){
    for(int j = 0; j < length; j++){
      delete[] floors[i][j];
    }
    delete[] floors[i];
  }
}

//basic initalizer method with default parameters (see map.hpp)
void Map::init(Wall *** floors, int width, int length, int bsize, int nfloors)
{
  this->floors = floors;
  this->width = width;
  this->length = length;
  this->bsize = bsize;
  this->nfloors = nfloors;
}

//generates a default map with a single floor for tests
void Map::defaultMap(int width, int length){
  //construction of floors pointer so it points to an area in the heap
  floors = new Wall**[1];
  floors[0] = new Wall*[length];

  //temparary wall that will be loaded into wall location on each floor
  Wall temp;
  for(int i = 0; i < length; i++){
    floors[0][i] = new Wall[width];
    for(int j = 0; j < width; j++){
      //initalizes the wall object to have a cascading color
      temp.init(j*i, j*i, j*i);
      //sets floors pointer to wall temp
      floors[0][i][j] = temp;
    }
  }

  //changes other variables to refelct new floors compostion
  this->width = width;
  this->length = length;
  this->bsize = 20;
  this->nfloors = 1;
}


//twoDRender option for the map which displays it as a grid
void Map::twoDRender(SDL_Renderer * renderer, int startx, int starty, int dsize){
  //double for loop to access each elemenet of the floors array
  for(int i = 0; i < length; i++){
    for(int j = 0; j < width; j++){
      //sets a temp varable to the current index
      Wall tempw = floors[0][i][j];
      //creates a SDL rectangle used for the SDL display
      SDL_Rect temp;
      temp.x = startx + j * dsize;
      temp.y = starty + i * dsize;
      temp.w = dsize;
      temp.h = dsize;

      //sets render color to wall color
      SDL_SetRenderDrawColor(renderer, tempw.get_color().r, tempw.get_color().g, tempw.get_color().b, 0);
      //draws rectangle
      SDL_RenderFillRect(renderer, &temp);
    }
  }
  //resets rendercolor to white
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
}

//threeDRender option for map which displays map in 3D using raycasting
void Map::threeDRender(SDL_Renderer * renderer, Player * player, int startx, int starty, int rwidth, int rheight)
{
  //defines the amount we increase our current degree by
  int separation = 1;
  //gets players field of view in degrees
  double dfov = player->get_fov();
  //gets players line of sight in degrees
  double dlos = player->get_los();
  //caculates the amount of pixels the screen needs to move for every slice render
  int sstep = ceil(rwidth / dfov * separation);
  //current X and Y position on the screen that the renderer is drawing at
  double currentX = 0;
  //current degree which is set to the degree at the vary right of the feild of vision.
  double dcurrent = dlos - dfov / 2;
  //sets renderer to allow opacity to add depth to the map
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  while(dlos + dfov / 2 > dcurrent){
    //caculates the distance from the player to the nearest wall at a certain degree
    std::tuple<double, double, Wall> hit = calcWDistance(player->get_xpos(), player->get_ypos(), dcurrent,  renderer);
    //pulls data from the output of calcWDistance and formats it for later use
    double hitx = std::get<0>(hit);
    double hity = std::get<1>(hit);
    Wall wtemp  = std::get<2>(hit);
    double distance = sqrt(pow(hitx, 2.0)+ pow(hity, 2.0)) * cos((dlos - dcurrent) * M_PI / 180);
    double angle =  atan(3/distance);
    double heightw = tan(angle) / (M_PI/4) * rheight;
    //creates temp rectangle to draw
    SDL_Rect temp;
    temp.x = currentX;
    temp.y = (rheight / 2) - heightw;
    temp.w = sstep;
    temp.h = heightw * 2;
    //sets render color to the nearest wall
    SDL_SetRenderDrawColor(renderer, 100, 0, 0, 100 * distance / 20);
    //draws rectangle
    SDL_RenderFillRect(renderer, &temp);
    //increase currentX by the screen step and dcurrent by seperation
    currentX += sstep;
    dcurrent += separation;
  }
}


//caculates the distance between a point and the nearest wall at a certain degree
std::tuple<double, double, Wall> Map::calcWDistance(int x, int y, double degree, SDL_Renderer * renderer)
{
  bool end = false;
  //gets radian equivalent of degree
  double radian = (degree * M_PI) / 180.00;

  //caculates the cosine of the angle
  double c = cos(radian);
  //currentX is the distance from the point to the closest wall on the x axis
  double currentX = -(x % bsize);
  //xadjust tweks the x index of the wall array to the correct wall
  double xadjust = -1;
  //the angle changes which closestX i.e if degree < 90 then we want cloest wall
  //to the right but if degree > 90 we want closest wall to the left
  if(c > 0){
    currentX = bsize - (x % bsize);
    xadjust = 0;
  }

  //copy of 158 to 169 for y
  double s = sin(radian);
  double currentY = -(y % bsize);
  double yadjust = -1;
  if(s > 0){
    currentY = bsize - (y % bsize);
    yadjust = 0;
  }

  //setting closestX and closestY which will hold our closest wall hit
  double closestX = 1000000;
  double closestY = 1000000;

  //cacultes the Y and X values for currentX and currentY
  double foundY = bsize * length;
  double foundX = bsize * width;

  //sets continue bools to ture
  bool currentXcont = true;
  bool currentYcont = true;

  //closest wall to the point at the given degree
  Wall closestW;

  //as long as the shortest distance hasn't been found continue
  //will exit even if there doesn't exist a wall in the inputted direction
  while(currentXcont || currentYcont){

    //checks if the currentX exceeds the boundries of the map
    if((currentX + x) < (width * bsize) && (currentX + x) > 0  && currentXcont){
      //finds the Y position on the line created by the degree and current
      foundY = currentX * tan(radian);
      //checks if the foundY exceeds the boundries of the map
      if(foundY + y > 0 && foundY + y < length * bsize){
        //get's the wall at the current position
        Wall temp = floors[0][(int)((y + foundY) / bsize)][(int)((x + currentX) / bsize + xadjust)];
        //checks if the closestX and closestY are less then the new found X and Y
        if(sqrt(pow(closestX,2.0) + pow(closestY,2.0)) > sqrt(pow(currentX,2.0) + pow(foundY,2.0))){
          //sets closestX and closestY
          closestX = currentX;
          closestY = foundY;
          closestW = temp;
          currentXcont = false;
        }
      }else{ currentXcont = false; }
    }else{ currentXcont = false; }


    //duplicate of lines 197 to  216 execpt using foundY instead of foundX
    if((currentY + y) < (length * bsize) && (currentY + y) > 0 && currentYcont){
      foundX = currentY / tan(radian);
      if(foundX + x > 0 && foundX + x < width * bsize){
        Wall temp = floors[0][(int)((y + currentY) / bsize + yadjust)][(int)((x + foundX) / bsize)];
        if(sqrt(pow(closestX,2.0) + pow(closestY,2.0)) > sqrt(pow(foundX,2.0) + pow(currentY,2.0))){
          closestX = foundX;
          closestY = currentY;
          closestW = temp;
          currentYcont = false;
        }
      }else{ currentYcont = false; }
    }else{ currentYcont = false; }


    //adds a bsize to caculate the next shortest distance
    if(xadjust){
      currentX -= bsize;
    }else{
      currentX += bsize;
    }

    if(yadjust){
      currentY -= bsize;
    }else{
      currentY += bsize;
    }
  }

  //creates a tuple of final values that we will return
  std::tuple<double, double, Wall> foo (closestX, closestY, closestW);

  return foo;
}

#endif
