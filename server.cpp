#include "include.hpp"

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Renderer *gRenderer = NULL;

int HORSE_G1 = 1;
int TOWER_G1 = 2;
int BISPE_G1 = 3;
int QUEEN_G1 = 4;
int KING_G1 = 5;
int PEON_G1 = 6;
// PIECES >>> GAMER 1

int HORSE_G2 = 7;
int TOWER_G2 = 8;
int BISPE_G2 = 9;
int QUEEN_G2 = 10;
int KING_G2 = 11;
int PEON_G2 = 12;
// PIECES >>> GAMER 2

int EMPTY = 13;

// EXISTS KING
int exists_king_gamer1 = 1;

// MESSAGE
char *message;

// BOARD
int board[8][8] =
	{
		{/*TOWER_G2*/ 8, /*HORSE_G2*/ 7, /*BISPE_G2*/ 9, /*KING_G2*/ 11, /*QUEEN_G2*/ 10, /*BISPE_G2*/ 9, /*HORSE_G2*/ 7, /*TOWER_G2*/ 8},
		{/*PEON_G2*/ 12, /*PEON_G2*/ 12, /*PEON_G2*/ 12, /*PEON_G2*/ 12, /*PEON_G2*/ 12, /*PEON_G2*/ 12, /*PEON_G2*/ 12, /*PEON_G2*/ 12},
		{/*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13},
		{/*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13},
		{/*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13},
		{/*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13},
		{/*PEON_G1*/ 6, /*PEON_G1*/ 6, /*PEON_G1*/ 6, /*PEON_G1*/ 6, /*PEON_G1*/ 6, /*PEON_G1*/ 6, /*PEON_G1*/ 6, /*PEON_G1*/ 6},
		{/*TOWER_G1*/ 2, /*HORSE_G1*/ 1, /*BISPE_G1*/ 3, /*KING_G1*/ 5, /*QUEEN_G1*/ 4, /*BISPE_G1*/ 3, /*HORSE_G1*/ 1, /*TOWER_G1*/ 2}};

int gamer = 2;

void movePiece(int column_ori, int line_ori, int column, int line, int gamer_)
{
	int l, c;

	if (board[line][column] < 0)
	{
		if (board[line][column] != -13) // ATE A PIECE OF THE OPPONENT
		{
			// PIECE IS KING?
			if (board[line][column] == -5)
				exists_king_gamer1 = 0;
		}

		board[line][column] = board[line_ori][column_ori];
		board[line_ori][column_ori] = 13; // EMPTY

		for (l = 0; l < 8; l++)
		{
			for (c = 0; c < 8; c++)
			{
				if (board[l][c] < 0)
					board[l][c] *= -1;
			}
		}
	}
}

int receivedVerifyMessage(char *message)
{
	char *token;
	char m[20];

	token = strtok(message, ",");
	int i = 0;
	while (token != NULL)
	{
		m[i] = atoi(token);
		token = strtok(NULL, ",");
		i++;
	}

	// chia messsage thanh 9 phan cach nhau dau phay
	if (i == 9)
	{
		if (m[0] == 1) // GAMER 1
		{
			// REFRESH BOARD
			int l_ori = m[1];
			int c_ori = m[2];
			int l_prox = m[3];
			int c_prox = m[4];
			int l_ori_s_l_prox = m[5];
			int c_ori_s_c_prox = m[6];
			int l_ori_s_c_prox = m[7];
			int l_prox_s_c_prox = m[8];

			if (l_ori_s_l_prox == (l_ori + l_prox) && c_ori_s_c_prox == (c_ori + c_prox) && l_ori_s_c_prox == (l_ori + c_prox) && l_prox_s_c_prox == (l_prox + c_prox))
			{
				testMovePiece(c_ori, l_ori, board[l_ori][c_ori], board, 1);
				movePiece(c_ori, l_ori, c_prox, l_prox, 1);

				return 1;
			}
		}
	}
	return 0;
}

const char *pathImage(int x)
{
	switch (x)
	{
	case -1:
		return "image/quancocopy/KnightW.png";
		break;
	case -2:
		return "image/quancocopy/RookW.png";
		break;
	case -3:
		return "image/quancocopy/BishopW.png";
		break;
	case -4:
		return "image/quancocopy/QueenW.png";
		break;
	case -5:
		return "image/quancocopy/KingW.png";
		break;
	case -6:
		return "image/quancocopy/PawnW.png";
		break;

	default:
		return nullptr;
		break;
	}
}

int main(int argc, char *argv[])
{
	struct sockaddr_in server, client;
	int socket_desc, client_sock, c, read_size, line_ori, column_ori, line_prox, column_prox, test_gamer = 0, test = 0, l, client_gamer;
	char client_message[2000], return_message[2000];
	strcpy(client_message, "1,0,0,0,0,0,0,0,0                    ");

	// Create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");

	// Prepare the sockaddr_in structure
	server.sin_family = AF_INET;			// IPv4
	server.sin_addr.s_addr = INADDR_ANY;	// Qualquer endereco
	server.sin_port = htons(atoi(argv[1])); // Porta a esperar por conexoes
	client_gamer = 2;						// cliente jogador

	// Bind
	if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("bind failed. Error"); // Print the error message
		return 1;
	}
	puts("bind done");

	listen(socket_desc, 3); // Listen

	// Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	// Accept connection from an incoming client
	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}
	puts("Connection accepted");

	strcpy(client_message, "");

	// Receive a message from client
	while ((read_size = recv(client_sock, client_message, 2000, 0)) > 0)
	{
		int mouseX = -1, mouseY = -1;
		int mouseX1 = -1, mouseY1 = -1;
		int tamdung = 0;
		int cauhoa = 0;
		int chiuthua = 0;
		int clienttamdung = 0;
		int clientcauhoa = 0;
		int clientchiuthua = 0;
		int checkcauhoa = 0;
		int checktamdung = 0;
		int checkchiuthua = 0;
		int chapnhancauhoa = 0;
		int icon = 0;
		int clienticon = 0;
		int quan = 0;
		int quananduoc[16] = {0};
		int a, b;

		// Verify message
		receivedVerifyMessage(client_message);

		strcpy(client_message, "");

		if (gamer == client_gamer)
		{
			if (!init())
			{
				printf("Failed to initialize!\n");
			}
			else
			{
				SDL_Event e;
				int quit = 0;
				while (!quit)
				{
					system("clear");
					while (SDL_PollEvent(&e))
					{
						if (e.type == SDL_QUIT)
						{
							quit = 1;
						}
						else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
						{
							SDL_GetMouseState(&a, &b);

							// tam dung
							if (a > 10 && a < 150 && b > 590 && b < 660)
							{
								send(client_sock, "tamdung", strlen("tamdung"), 0);
								tamdung = 1;
								if (cauhoa == 1)
									cauhoa = 0;
							}

							if (tamdung == 1)
							{
								if (a > 100 && a < 500 && b > 200 && b < 600)
								{
									send(client_sock, "tieptuc", strlen("tieptuc"), 0);
									tamdung = 0;
								}
							}

							// cau hoa
							if (a > 260 && a < 450 && b > 590 && b < 660)
							{
								send(client_sock, "cauhoa", strlen("cauhoa"), 0);
								cauhoa = 1;
								if (tamdung == 1)
									tamdung = 0;
							}

							// chiu thua
							if (a > 500 && a < 700 && b > 590 && b < 660)
							{
								send(client_sock, "chiuthua", strlen("chiuthua"), 0);
								chiuthua = 1;
							}

							// icon
							if (a > 530 && a < 600 && b > 430 && b < 480)
							{
								send(client_sock, "icon", strlen("icon"), 0);
							}

							if (clienticon == 1)
							{
								if (a > 100 && a < 500 && b > 200 && b < 600)
								{
									clienticon = 0;
								}
							}

							// ket thuc
							// if (chapnhancauhoa == 1 || chiuthua == 1 || clientchiuthua == 1)
							// {
							// 	if (a > 100 && a < 500 && b > 200 && b < 600)
							// 	{
							// 		return 1;
							// 	}
							// }

							if (clientcauhoa == 1)
							{
								SDL_GetMouseState(&a, &b);
								if (a > 20 && a < 150 && b > 100 && b < 600)
								{
									chapnhancauhoa = 1;
									send(client_sock, "chapnhancauhoa", strlen("chapnhancauhoa"), 0);
								}
								else if (a > 200 && a < 500 && b > 100 && b < 600)
								{
									clientcauhoa = 0;
									send(client_sock, "tuchoicauhoa", strlen("tuchoicauhoa"), 0);
								}
							}

							int click = 0;
							if (mouseX == -1 && mouseY == -1)
							{
								SDL_GetMouseState(&mouseX, &mouseY);

								line_ori = mouseY / 50;
								column_ori = mouseX / 50;
								line_ori--;
								column_ori--;
								if (board[line_ori][column_ori] <= 6)
									mouseX = -1, mouseY = -1;
								else
									test_gamer = testMovePiece(column_ori, line_ori, int(board[line_ori][column_ori]), board, gamer);
							}
							else if (mouseX1 == -1 && mouseY1 == -1)
							{
								click = 1;
								SDL_GetMouseState(&mouseX1, &mouseY1);

								line_prox = mouseY1 / 50;
								column_prox = mouseX1 / 50;
								line_prox--;
								column_prox--;
								mouseX = -1, mouseY = -1;
								mouseX1 = -1, mouseY1 = -1;
							}

							if (click == 1)
							{

								if (board[line_prox][column_prox] < 0)
								{
									if (board[line_prox][column_prox] != -13)
									{
										quananduoc[quan] = board[line_prox][column_prox];
										quan++;
									}
									movePiece(column_ori, line_ori, column_prox, line_prox, 2);
									test_gamer = 1;

									if (exists_king_gamer1 == 0)
									{
										clientchiuthua = 1;
										send(client_sock, "defeat", strlen("defeat"), 0);
										test_gamer = 0;

										// fflush(stdout);
										// close(client_sock);
										// return 1;
										// quit = 1;
									}
								}
								else
									test_gamer = 0;

								if (test_gamer != 0 && chiuthua == 0 && tamdung == 0 && cauhoa == 0)
								{
									// Create message
									snprintf(return_message, sizeof(return_message), "2,%d,%d,%d,%d,%d,%d,%d,%d", line_ori, column_ori, line_prox, column_prox,
											 line_ori + line_prox, column_ori + column_prox, line_ori + column_prox, line_prox + column_prox);

									int server_send = send(client_sock, return_message, strlen(return_message), 0);

									// Clear buffer
									memset(client_message, 0, sizeof(client_message));
								}
							}
						}
					}

					ImageInfo image1, image2, image3, image4, image5, image6, image7, image8;

					// Load thông tin cho mỗi ảnh
					if (
						!loadMedia(&image1, "image/dsonl.jpg", 0, 0) ||
						!loadMedia(&image2, "image/nguoichoi2.jpg", 530, 0) ||
						!loadMedia(&image4, "image/daulai.jpg", 530, 430) ||
						!loadMedia(&image8, "image/thoat.jpg", 660, 430) ||
						!loadMedia(&image5, "image/tamdung.jpg", 10, 590) ||
						!loadMedia(&image6, "image/cauhoa.jpg", 260, 590) ||
						!loadMedia(&image7, "image/chiuthua.jpg", 515, 590))
					{
						printf("Failed to load media!\n");
					}
					else
					{
						// Sao chép hình ảnh vào khu vực đích với kích thước và vị trí đã đặt
						SDL_BlitSurface(image1.surface, NULL, gScreenSurface, &image1.position);
						SDL_BlitSurface(image2.surface, NULL, gScreenSurface, &image2.position);
						SDL_BlitSurface(image4.surface, NULL, gScreenSurface, &image4.position);
						SDL_BlitSurface(image5.surface, NULL, gScreenSurface, &image5.position);
						SDL_BlitSurface(image6.surface, NULL, gScreenSurface, &image6.position);
						SDL_BlitSurface(image7.surface, NULL, gScreenSurface, &image7.position);
						SDL_BlitSurface(image8.surface, NULL, gScreenSurface, &image8.position);

						// SDL_UpdateWindowSurface(gWindow);
					}
					closeImage(&image1);
					closeImage(&image2);
					closeImage(&image4);
					closeImage(&image5);
					closeImage(&image6);
					closeImage(&image7);
					closeImage(&image8);

					ImageInfo quanco;
					if (loadMedia(&quanco, "image/banco.jpg", 0, 0))
					{
						SDL_BlitSurface(quanco.surface, NULL, gScreenSurface, &quanco.position);
					}
					closeImage(&quanco);
					printBoard(board);

					for (int i = 0; i < 16; i++)
					{
						if (quananduoc[i] < 0 && quananduoc[i] != -13)
						{
							ImageInfo quanan;
							if (i < 8)
							{
								if (loadMedia(&quanan, pathImage(quananduoc[i]), 515 + 32 * i, 10))
								{
									SDL_BlitSurface(quanan.surface, NULL, gScreenSurface, &quanan.position);
								}
							}
							else
							{
								if (loadMedia(&quanan, pathImage(quananduoc[i]), 515 + 32 * (i - 8), 70))
								{
									SDL_BlitSurface(quanan.surface, NULL, gScreenSurface, &quanan.position);
								}
							}
							closeImage(&quanan);
						}
					}
					if ((read_size = recv(client_sock, client_message, 2000, MSG_DONTWAIT)) > 0)
					{
						if (strcmp(client_message, "tamdung") == 0)
						{
							clienttamdung = 1;
							memset(client_message, 0, sizeof(client_message));
						}
						else if (strcmp(client_message, "tieptuc") == 0)
						{
							clienttamdung = 0;
							memset(client_message, 0, sizeof(client_message));
						}
						else if (strcmp(client_message, "cauhoa") == 0)
						{
							clientcauhoa = 1;
							memset(client_message, 0, sizeof(client_message));
						}
						else if (strcmp(client_message, "chiuthua") == 0)
						{
							clientchiuthua = 1;
							memset(client_message, 0, sizeof(client_message));
						}
						else if (strcmp(client_message, "defeat") == 0)
						{
							chiuthua = 1;
							memset(client_message, 0, sizeof(client_message));
						}
						else if (strcmp(client_message, "icon") == 0)
						{
							clienticon = 1;
							memset(client_message, 0, sizeof(client_message));
						}
						else if (strcmp(client_message, "chapnhancauhoa") == 0)
						{
							chapnhancauhoa = 1;
							memset(client_message, 0, sizeof(client_message));
							// close(sock);
							// return 1;
							// quit = 1;
						}
						else if (strcmp(client_message, "tuchoicauhoa") == 0)
						{
							cauhoa = 0;
							memset(client_message, 0, sizeof(client_message));
						}
						else
						{
							receivedVerifyMessage(client_message);
							strcpy(client_message, "");
						}
					}
					else if ((read_size = recv(client_sock, client_message, 2000, MSG_DONTWAIT)) == 0)
					{
						clientchiuthua = 1;
						// close(client_sock);
						// return 1;
						// quit = 1;
					}

					if (tamdung == 1)
					{
						ImageInfo image1;
						if (loadMedia(&image1, "image/donetamdung.jpg", 0, 80))
						{
							SDL_BlitSurface(image1.surface, NULL, gScreenSurface, &image1.position);
						}
						closeImage(&image1);
					}
					if (cauhoa == 1)
					{
						ImageInfo image1;
						if (loadMedia(&image1, "image/xincauhoa.jpg", 0, 80))
						{
							SDL_BlitSurface(image1.surface, NULL, gScreenSurface, &image1.position);
						}
						closeImage(&image1);
					}

					if (chiuthua == 1)
					{
						ImageInfo image1;
						if (loadMedia(&image1, "image/defeat.jpg", 0, 80))
						{
							SDL_BlitSurface(image1.surface, NULL, gScreenSurface, &image1.position);
						}
						closeImage(&image1);
					}

					if (clienttamdung == 1)
					{
						ImageInfo image1;
						if (loadMedia(&image1, "image/yctamdung.jpg", 0, 80))
						{
							SDL_BlitSurface(image1.surface, NULL, gScreenSurface, &image1.position);
						}
						closeImage(&image1);
					}
					if (clientcauhoa == 1)
					{
						ImageInfo image1;
						if (loadMedia(&image1, "image/yccauhoa.jpg", 0, 80))
						{
							SDL_BlitSurface(image1.surface, NULL, gScreenSurface, &image1.position);
						}
						closeImage(&image1);
					}
					if (chapnhancauhoa == 1)
					{
						ImageInfo image1;
						if (loadMedia(&image1, "image/hoa.jpg", 0, 80))
						{
							SDL_BlitSurface(image1.surface, NULL, gScreenSurface, &image1.position);
						}
						closeImage(&image1);
					}
					if (clientchiuthua == 1)
					{
						ImageInfo image1;
						if (loadMedia(&image1, "image/win.jpg", 0, 80))
						{
							SDL_BlitSurface(image1.surface, NULL, gScreenSurface, &image1.position);
						}
						closeImage(&image1);
					}
					if (clienticon == 1)
					{
						ImageInfo image1;
						if (loadMedia(&image1, "image/icon.png", 200, 200))
						{
							SDL_BlitSurface(image1.surface, NULL, gScreenSurface, &image1.position);
						}
						closeImage(&image1);
					}

					SDL_UpdateWindowSurface(gWindow);
				}
				SDL_DestroyWindow(gWindow);
				SDL_Quit();
			}
		}
	}

	return 0;
}
