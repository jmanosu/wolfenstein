#ifndef Map_cpp
#define Map_cpp

#include "map.hpp"

Map::Map()
{
  nfloors = 0;
  width = 0;
  height = 0;
  bsize = 0;
  floors = NULL;
}

Map::~Map()
{
  for(int i = 0; i < nfloors; i++){
    for(int j = 0; j < height; j++){
      delete[] floors[i][j];
    }
    delete[] floors[i];
  }
}

void Map::init(Wall *** floors, int width, int height, int bsize, int nfloors)
{
  this->floors = floors;
  this->width = width;
  this->height = height;
  this->bsize = bsize;
  this->nfloors = nfloors;
}

void Map::defaultMap(int width, int height){
  floors = new Wall**[1];
  floors[0] = new Wall*[height];
  Wall temp;
  for(int i = 0; i < height; i++){
    floors[0][i] = new Wall[width];
    for(int j = 0; j < width; j++){
      temp.init(j*i, j*i, j*i);
      floors[0][i][j] = temp;
    }
  }
  this->width = width;
  this->height = height;
  this->bsize = 20;
  this->nfloors = 1;
}

void Map::twoDRender(SDL_Renderer * renderer, int startx, int starty, int dsize){
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      Wall tempw = floors[0][i][j];
      SDL_Rect temp;
      temp.x = startx + j * dsize;
      temp.y = starty + i * dsize;
      temp.w = dsize;
      temp.h = dsize;
      SDL_SetRenderDrawColor(renderer, tempw.get_color().r, tempw.get_color().g, tempw.get_color().b, 0);
      SDL_RenderFillRect(renderer, &temp);
    }
  }
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
}

void Map::threeDRender(SDL_Renderer * renderer, Player * player, int startx, int starty, int rwidth, int rheight)
{
  int separation = 1;
  double dfov = player->get_fov();
  int sstep = ceil(rwidth / dfov * separation);
  double dstep = separation;
  double currentX = 0;
  double dcurrent = 0;
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  while(dfov > dcurrent){
    std::tuple<double, double, Wall> hit = calcWDistance(player->get_xpos(), player->get_ypos(), dcurrent,  renderer);
    double hitx = std::get<0>(hit);
    double hity = std::get<1>(hit);
    double distance = sqrt(pow(hitx, 2.0)+ pow(hity, 2.0)) * cos(((dfov / 2) - dcurrent) * M_PI / 180);
    double angle =  atan(3/distance);
    double heightw = tan(angle) / (M_PI/4) * rheight;
    //std::cout << " distance " << distance << std::endl;
    SDL_Rect temp;
    temp.x = currentX;
    temp.y = (rheight / 2) - heightw;
    temp.w = sstep;
    temp.h = heightw * 2;
    SDL_SetRenderDrawColor(renderer, 100, 0, 0, 100 * distance / 20);
    SDL_RenderFillRect(renderer, &temp);
    currentX += sstep;
    dcurrent += dstep;
  }
}

std::tuple<double, double, Wall> Map::calcWDistance(int x, int y, double degree, SDL_Renderer * renderer)
{
  degree = ceil(degree);
  bool end = false;
  double radian = (degree * M_PI) / 180.00;

  double c = cos(radian);
  double currentX = -(x % bsize);
  double xadjust = -1;
  if(c > 0){
    currentX = bsize - (x % bsize);
    xadjust = 0;
  }

  double s = sin(radian);
  double currentY = -(y % bsize);
  double yadjust = -1;
  if(s > 0){
    currentY = bsize - (y % bsize);
    yadjust = 0;
  }

  double closestX = -1;
  double closestY = -1;

  currentX = round(currentX);
  currentY = round(currentY);

  double foundY = bsize * height;
  double foundX = bsize * width;
  //while(!end){
    if((currentX + x) < (width * bsize) && (currentX + x) > 0 && ((int)(degree) % 90) != 0){
      foundY = currentX * tan(radian);
      if(foundY + y > 0 && foundY + y < height * bsize){
        //SDL_SetRenderDrawColor(renderer, 100, degree, degree, 0);
        //SDL_RenderDrawPoint(renderer, x + currentX, y + foundY);
        Wall temp = floors[0][(int)((y + foundY) / bsize)][(int)((x + currentX) / bsize + xadjust)];
        //SDL_SetRenderDrawColor(renderer, 250, 0, 200, 0);
        if(true){
          closestX = currentX;
          closestY = foundY;
        }
      }else{
        /*SDL_RenderDrawPoint(renderer, x + currentX, y + foundY);
        std::cout << "degree " << degree << std::endl;
        std::cout << "foundY " << foundY << std::endl;
        std::cout << "yadjust " << yadjust << std::endl;
        std::cout << (foundY + y > 0 - yadjust * bsize) << std::endl;
        std::cout << (foundY + y < height * bsize) << std::endl;*/
      }
    }

    if((currentY + y) < (height * bsize) && (currentY + y) > 0 && ((int)(degree) % 180) != 0){
      foundX = currentY / tan(radian);
      if(foundX + x > 0 && foundX + x < width * bsize){
        //SDL_SetRenderDrawColor(renderer, 0, 0, 200, 0);
        //SDL_RenderDrawPoint(renderer, x + foundX, y + currentY);
        Wall temp = floors[0][(int)((y + currentY) / bsize + yadjust)][(int)((x + foundX) / bsize)];
        if(sqrt(pow(closestX,2.0) + pow(closestY,2.0)) > sqrt(pow(foundX,2.0) + pow(currentY,2.0))){
          closestX = foundX;
          closestY = currentY;
        }
      }else{
        /*SDL_SetRenderDrawColor(renderer, 250, 0, 200, 0);
        SDL_RenderDrawPoint(renderer, x + foundX, y + currentY);*/
      }
    }
    currentX += bsize;
    currentY += bsize;
    Wall temp;
    std::tuple<double, double, Wall> foo (closestX, closestY, temp);
    return foo;
}

#endif
