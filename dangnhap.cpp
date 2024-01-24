#include "dangnhap.hpp"
// #include "../Home/home.hpp"
// #include "../BanCo/banco.hpp"
// #include "../QuanCo/quanco.hpp"
// #include "../ClickChuot/clickChuot.hpp"

// void indangnhap()
// {
// 	ImageInfo image;

// 	// Load thông tin cho mỗi ảnh
// 	if (!loadMedia(&image, "image/login.jpg", 150, 150))
// 	{
// 		printf("Failed to load media!\n");
// 	}
// 	else
// 	{
// 		// Sao chép hình ảnh vào khu vực đích với kích thước và vị trí đã đặt
// 		SDL_BlitSurface(image.surface, NULL, gScreenSurface, &image.position);
// 	}
// 	close(&image);
// }

void in(SDL_Event *e, int *show)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        // return 1;
    }

    if (TTF_Init() < 0)
    {
        fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Quit();
        // return 1;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL)
    {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        // return 1;
    }

    gFont = TTF_OpenFont("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf", 15);
    if (gFont == NULL)
    {
        fprintf(stderr, "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        // return 1;
    }
    IMG_Init(IMG_INIT_JPG);
    SDL_RenderClear(gRenderer);

    // Load thông tin cho mỗi ảnh
    SDL_Texture *imageTexture = loadImage("image/login.jpg");
    SDL_Rect ButtonRect = {150, 150, 500, 250};
    SDL_RenderCopy(gRenderer, imageTexture, NULL, &ButtonRect);
    SDL_Texture *usernameText = createTextTexture(username);
    SDL_Texture *passwordText = createTextTexture(password);

    SDL_Rect usernameTextRect = {360, 175, 100, 30};
    SDL_Rect passwordTextRect = {360, 265, 100, 30};

    SDL_RenderCopy(gRenderer, usernameText, NULL, &usernameTextRect);
    SDL_RenderCopy(gRenderer, passwordText, NULL, &passwordTextRect);

    // SDL_DestroyTexture(imageTexture);
    //   int i=0;
    //   while(!i )
    //   {

    if (e->type == SDL_TEXTINPUT)
    {
        // Nếu sự kiện là nhập liệu từ bàn phím
        if (strlen(username) < sizeof(username) - 1 && activeInput == 0)
        {
            // Nếu chiều dài của username chưa vượt quá giới hạn và đang nhập vào ô username
            strcat(username, e->text.text);
        }
        else if (strlen(password) < sizeof(password) - 1 && activeInput == 1)
        {
            // Nếu chiều dài của password chưa vượt quá giới hạn và đang nhập vào ô password
            strcat(password, e->text.text);
        }
    }
    else if (e->type == SDL_KEYDOWN)
    {
        // Nếu người dùng nhấn phím Enter
        if (e->key.keysym.sym == SDLK_RETURN || e->key.keysym.sym == SDLK_KP_ENTER)
        {
            // Lưu dữ liệu khi nhấn Enter
            printf("Username: %s\n", username);
            printf("Password: %s\n", password);

            // *showInDangNhap = 0;
        }
        else if (e->key.keysym.sym == SDLK_BACKSPACE)
        {
            // Nếu người dùng nhấn phím Backspace
            if (activeInput == 0 && strlen(username) > 0)
            {
                // Xóa ký tự cuối cùng trong username
                username[strlen(username) - 1] = '\0';
            }
            else if (activeInput == 1 && strlen(password) > 0)
            {
                // Xóa ký tự cuối cùng trong password
                password[strlen(password) - 1] = '\0';
            }
        }
        else if (e->key.keysym.sym == SDLK_TAB)
        {
            // Nếu người dùng nhấn phím Tab, chuyển sang ô nhập liệu khác
            activeInput = (activeInput + 1) % 2;
        }
    }
    // }
    SDL_RenderPresent(gRenderer);
}
SDL_Texture *loadImage(const char *filename)
{
    SDL_Surface *surface = IMG_Load(filename);
    if (surface == NULL)
    {
        fprintf(stderr, "Unable to load image %s! SDL_Image Error: %s\n", filename, IMG_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

//===================== text =======================
// Tạo texture từ chuỗi ký tự
SDL_Texture *createTextTexture(const char *text)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, text, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_FreeSurface(textSurface);
    return textTexture;
}

// Hiển thị form nhập liệu
void displayForm()
{

    SDL_RenderClear(gRenderer);

    // Load thông tin cho mỗi ảnh

    // Hiển thị các trường nhập liệu và nút OK
    // SDL_Texture *usernameLabel = createTextTexture("Username:");
    // SDL_Texture *passwordLabel = createTextTexture("Password:");
    // SDL_Texture *okButton = createTextTexture("OK");
    SDL_Texture *imageTexture = loadImage("image/login.jpg");

    int inputBoxWidth = 400;
    int inputBoxHeight = 300;
    int inputBoxX = 150;
    int inputBoxY = 150;
    int spacing = 40;

    // SDL_Rect usernameRect = {inputBoxX, inputBoxY, inputBoxWidth, inputBoxHeight};
    // SDL_Rect passwordRect = {inputBoxX, inputBoxY + spacing, inputBoxWidth, inputBoxHeight};
    // SDL_Rect okButtonRect = {inputBoxX, inputBoxY + 2 * spacing, inputBoxWidth, inputBoxHeight};
    SDL_Rect ButtonRect = {150, 150, 500, 250};

    // Vẽ các trường nhập liệu và nút OK
    // SDL_RenderCopy(gRenderer, usernameLabel, NULL, &usernameRect);
    // SDL_RenderCopy(gRenderer, passwordLabel, NULL, &passwordRect);
    // SDL_RenderCopy(gRenderer, okButton, NULL, &okButtonRect);
    SDL_RenderCopy(gRenderer, imageTexture, NULL, &ButtonRect);

    // Hiển thị dữ liệu người dùng nhập vào
    SDL_Texture *usernameText = createTextTexture(username);
    SDL_Texture *passwordText = createTextTexture(password);

    SDL_Rect usernameTextRect = {360, 175, 100, 30};
    SDL_Rect passwordTextRect = {360, 265, 100, 30};

    SDL_RenderCopy(gRenderer, usernameText, NULL, &usernameTextRect);
    SDL_RenderCopy(gRenderer, passwordText, NULL, &passwordTextRect);

    // SDL_DestroyTexture(usernameLabel);
    // SDL_DestroyTexture(passwordLabel);
    // SDL_DestroyTexture(okButton);
    SDL_DestroyTexture(imageTexture);
    SDL_DestroyTexture(usernameText);
    SDL_DestroyTexture(passwordText);

    SDL_RenderPresent(gRenderer);
}

// Xử lý sự kiện nhập liệu từ bàn phím
void handleInputEvent(SDL_Event *e)
{
    if (e->type == SDL_TEXTINPUT)
    {

        // Nếu sự kiện là nhập liệu từ bàn phím
        if (strlen(username) < sizeof(username) - 1 && activeInput == 0)
        {
            // Nếu chiều dài của username chưa vượt quá giới hạn và đang nhập vào ô username
            strcat(username, e->text.text);
        }
        else if (strlen(password) < sizeof(password) - 1 && activeInput == 1)
        {
            // Nếu chiều dài của password chưa vượt quá giới hạn và đang nhập vào ô password
            strcat(password, e->text.text);
        }
    }
    else if (e->type == SDL_KEYDOWN)
    {
        // Nếu người dùng nhấn phím Enter
        if (e->key.keysym.sym == SDLK_RETURN || e->key.keysym.sym == SDLK_KP_ENTER)
        {
            // Lưu dữ liệu khi nhấn Enter
            printf("Username: %s\n", username);
            printf("Password: %s\n", password);
        }
        else if (e->key.keysym.sym == SDLK_BACKSPACE)
        {
            // Nếu người dùng nhấn phím Backspace
            if (activeInput == 0 && strlen(username) > 0)
            {
                // Xóa ký tự cuối cùng trong username
                username[strlen(username) - 1] = '\0';
            }
            else if (activeInput == 1 && strlen(password) > 0)
            {
                // Xóa ký tự cuối cùng trong password
                password[strlen(password) - 1] = '\0';
            }
        }
        else if (e->key.keysym.sym == SDLK_TAB)
        {
            // Nếu người dùng nhấn phím Tab, chuyển sang ô nhập liệu khác
            activeInput = (activeInput + 1) % 2;
        }
    }
}

void inlogin(SDL_Event *e)
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        // return 1;
    }

    if (TTF_Init() < 0)
    {
        fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Quit();
        // return 1;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL)
    {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        // return 1;
    }

    gFont = TTF_OpenFont("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf", 15);
    if (gFont == NULL)
    {
        fprintf(stderr, "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        // return 1;
    }
    IMG_Init(IMG_INIT_JPG);

    int quit = 0;
    // SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(e))
        {
            if (e->type == SDL_QUIT)
            {
                quit = 1;
            }
            else if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Kiểm tra xem người dùng có click vào nút OK không
                if (isMouseInsideRect(mouseX, mouseY, 100, 150, 530, 560))
                {
                    // Lưu dữ liệu khi nhấn nút OK
                    // TTF_CloseFont(gFont);
                    // TTF_Quit();
                    // SDL_DestroyRenderer(gRenderer);
                    // SDL_DestroyWindow(gWindow);
                    // SDL_DestroyWindow(gWindow);
                    // if(!TTF_CloseFont(gFont);)
                    // {
                    //     printf("kkk");
                    // }
                    // else{
                    //     printf("hihi");
                    //     // inBanCo();
                    //     // printBoard(board);
                    // }
                    // printf("tttttttttttt");

                    //    indangnhap();
                    exit(0);

                    // quit = 1;
                }
            }
            else
            {
                // Xử lý sự kiện nhập liệu từ bàn phím
                handleInputEvent(e);
            }
        }

        displayForm();
    }

    TTF_CloseFont(gFont);
    TTF_Quit();
    SDL_DestroyRenderer(gRenderer);
    // SDL_DestroyWindow(gWindow);
    SDL_Quit();
    // return 0;
}