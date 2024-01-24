#ifndef __include_H__
#define __include_H__

#include <stdio.h>      // prextern intf
#include <stdlib.h>     // atoi
#include <string.h>     // strlen strcpy
#include <sys/socket.h> // socket
#include <arpa/inet.h>  // inet_addr
#include <unistd.h>     // for close

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "communication.hpp"
#include "chess.hpp"
#include "menu.hpp"

extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;
extern SDL_Renderer *gRenderer;
extern TTF_Font *gFont;
extern SDL_Color textColor;

// Định nghĩa cấu trúc để lưu trữ thông tin của mỗi ảnh
typedef struct
{
    SDL_Surface *surface;
    SDL_Rect position;
} ImageInfo;

int init();
int loadMedia(ImageInfo *imageInfo, const char *imagePath, int x, int y);
void closeImage(ImageInfo *imageInfo);

#endif