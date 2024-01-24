#ifndef __dangnhap_H__
#define __dangnhap_H__

#include "include.hpp"

//void indangnhap();

//===================== text =======================
SDL_Texture *createTextTexture(const char *text);
SDL_Texture *loadImage(const char *filename);
void displayForm();
void handleInputEvent(SDL_Event *e);
void inlogin(SDL_Event *e);
void in(SDL_Event *e, int *show);

#endif 