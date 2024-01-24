#include "menu.hpp"

void inMenu()
{
	ImageInfo image1, image2, image3;

	// Load thông tin cho mỗi ảnh
	if (!loadMedia(&image1, "image/dangky.jpg", 380, 100) ||
		!loadMedia(&image2, "image/dangnhap.jpg", 380, 180) ||
		!loadMedia(&image3, "image/thoat.jpg", 380, 340))
	{
		printf("Failed to load media!\n");
	}
	else
	{
		SDL_BlitSurface(image1.surface, NULL, gScreenSurface, &image1.position);
		SDL_BlitSurface(image2.surface, NULL, gScreenSurface, &image2.position);
		SDL_BlitSurface(image3.surface, NULL, gScreenSurface, &image3.position);
	}
	closeImage(&image1);
	closeImage(&image2);
	closeImage(&image3);
}
