#include "include.hpp"

int init()
{
    gWindow = SDL_CreateWindow("Nhóm 14", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 680, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);

    return 1;
}

int loadMedia(ImageInfo *imageInfo, const char *imagePath, int x, int y)
{
    imageInfo->surface = IMG_Load(imagePath);
    if (imageInfo->surface == NULL)
    {
        printf("Failed to load media! SDL_image Error: %s\n", IMG_GetError());
        return 0;
    }

    imageInfo->position.x = x;
    imageInfo->position.y = y;

    return 1;
}

void closeImage(ImageInfo *imageInfo)
{
    SDL_FreeSurface(imageInfo->surface);
}




