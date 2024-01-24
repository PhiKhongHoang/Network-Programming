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
int exists_king_gamer2 = 1;

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

int gamer = 1;

void movePiece(int column_ori, int line_ori, int column, int line, int gamer_)
{
	int l, c;

	if (board[line][column] < 0)
	{
		if (board[line][column] != -13) // ATE A PIECE OF THE OPPONENT
		{
			// PIECE IS KING?
			if (board[line][column] == -11)
				exists_king_gamer2 = 0;
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
		// printf("%d\n", atoi(token));
		m[i] = atoi(token);
		token = strtok(NULL, ",");
		i++;
	}

	// chia messsage thanh 9 phan cach nhau dau phay
	if (i == 9)
	{
		if (m[0] == 2) // GAMER 2
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
				testMovePiece(c_ori, l_ori, board[l_ori][c_ori], board, 2);
				movePiece(c_ori, l_ori, c_prox, l_prox, 2);

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
	case -7:
		return "image/quancocopy/KnightB.png";
		break;
	case -8:
		return "image/quancocopy/RookB.png";
		break;
	case -9:
		return "image/quancocopy/BishopB.png";
		break;
	case -10:
		return "image/quancocopy/KingB.png";
		break;
	case -11:
		return "image/quancocopy/QueenB.png";
		break;
	case -12:
		return "image/quancocopy/PawnB.png";
		break;

	default:
		return nullptr;
		break;
	}
}

int main(int argc, char *argv[])
{
	struct sockaddr_in server;
	int sock, r_connect, r_send, r_recv, line_ori, column_ori, line_prox, column_prox, test_gamer = 0, test = 0, l, c, client_gamer;
	char message[1000], server_reply[2000];

	// criando o socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		printf("ERRO: nao foi possivel criar o socket");
		return 1;
	}

	printf("# SOCKET CRIADO #\n");

	// configurando o servidor de destino da conexao
	server.sin_family = AF_INET;				 // IPv4
	server.sin_addr.s_addr = inet_addr(argv[1]); // endereco IP do servidor
	server.sin_port = htons(atoi(argv[2]));		 // porta en que servidor irá aguardar conexoes
	client_gamer = 1;							 // cliente jogador

	// conectando com o servidor
	r_connect = connect(sock, (struct sockaddr *)&server, sizeof(server));
	if (r_connect < 0)
	{
		printf("ERRO: conexao com o servidor falhou");
		return 2;
	}
	printf("# CONNECTADO #\n");

	int check = 0;
	int inmenu = 0;
	int inbanco = 0;
	int tamdung = 0;
	int cauhoa = 0;
	int chiuthua = 0;
	int servertamdung = 0;
	int servercauhoa = 0;
	int serverchiuthua = 0;
	int chapnhancauhoa = 0;
	int icon = 0;
	int servericon = 0;
	int quan = 0;
	int quananduoc[16] = {0};
	// while (1)
	// {

	strcpy(server_reply, "");
	int mouseX = -1, mouseY = -1;
	int mouseX1 = -1, mouseY1 = -1;

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
						int a, b;
						SDL_GetMouseState(&a, &b);
						if (a > 380 && a < 480 && b > 180 && b < 230)
						{
							inmenu = 1;
							inbanco = 1;
						}
						if (inbanco == 1)
						{
							// tam dung
							if (a > 10 && a < 150 && b > 590 && b < 660)
							{
								send(sock, "tamdung", strlen("tamdung"), 0);
								tamdung = 1;
							}

							if (tamdung == 1)
							{
								if (a > 100 && a < 500 && b > 200 && b < 600)
								{
									tamdung = 0;
									send(sock, "tieptuc", strlen("tieptuc"), 0);
								}
							}

							// cau hoa
							if (a > 260 && a < 450 && b > 590 && b < 660)
							{
								send(sock, "cauhoa", strlen("cauhoa"), 0);
								cauhoa = 1;
							}

							// chiu thua
							if (a > 500 && a < 700 && b > 590 && b < 660)
							{
								send(sock, "chiuthua", strlen("chiuthua"), 0);
								chiuthua = 1;
							}

							// icon
							if (a > 530 && a < 600 && b > 430 && b < 480)
							{
								send(sock, "icon", strlen("icon"), 0);
							}

							if (servericon == 1)
							{
								if (a > 100 && a < 500 && b > 200 && b < 600)
								{
									servericon = 0;
								}
							}

							// ket thuc
							// if (chapnhancauhoa == 1 || chiuthua == 1 || serverchiuthua == 1)
							// {
							// 	if (a > 100 && a < 500 && b > 200 && b < 600)
							// 	{
							// 		inbanco = 0;
							// 		inmenu = 1;
							// 	}
							// }

							if (servercauhoa == 1)
							{
								SDL_GetMouseState(&a, &b);
								if (a > 20 && a < 150 && b > 100 && b < 600)
								{
									chapnhancauhoa = 1;
									send(sock, "chapnhancauhoa", strlen("chapnhancauhoa"), 0);
								}
								else if (a > 200 && a < 500 && b > 100 && b < 600)
								{
									servercauhoa = 0;
									send(sock, "tuchoicauhoa", strlen("tuchoicauhoa"), 0);
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
								if (board[line_ori][column_ori] > 6)
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
									movePiece(column_ori, line_ori, column_prox, line_prox, 1);

									test_gamer = 1;

									if (exists_king_gamer2 == 0)
									{ // NOT EXISTS PIECES GAMER 2 OR NOT EXISTS THE KING OF GAMER 2
										serverchiuthua = 1;
										send(sock, "defeat", strlen("defeat"), 0);
										test_gamer = 0;

										// close(sock);
										// return 1;
										// quit = 1;
									}
								}
								else
									test_gamer = 0;

								if (test_gamer != 0)
								{
									// Create message
									snprintf(message, sizeof(message), "1,%d,%d,%d,%d,%d,%d,%d,%d", line_ori, column_ori, line_prox, column_prox,
											 line_ori + line_prox, column_ori + column_prox, line_ori + column_prox, line_prox + column_prox);

									// // Send some data
									r_send = send(sock, message, strlen(message), 0);
									check = 1;
								}
							}

							r_recv = recv(sock, server_reply, 2000, MSG_DONTWAIT);
							if (r_recv > 0)
							{
								if (strcmp(server_reply, "tamdung") == 0)
								{
									servertamdung = 1;
									memset(server_reply, 0, sizeof(server_reply));
								}
								else if (strcmp(server_reply, "tieptuc") == 0)
								{
									servertamdung = 0;
									memset(server_reply, 0, sizeof(server_reply));
								}
								else if (strcmp(server_reply, "cauhoa") == 0)
								{
									servercauhoa = 1;
									memset(server_reply, 0, sizeof(server_reply));
								}
								else if (strcmp(server_reply, "chiuthua") == 0)
								{
									serverchiuthua = 1;
									memset(server_reply, 0, sizeof(server_reply));
								}
								else if (strcmp(server_reply, "defeat") == 0)
								{
									chiuthua = 1;
									memset(server_reply, 0, sizeof(server_reply));
								}
								else if (strcmp(server_reply, "icon") == 0)
								{
									servericon = 1;
									memset(server_reply, 0, sizeof(server_reply));
								}
								else if (strcmp(server_reply, "chapnhancauhoa") == 0)
								{
									chapnhancauhoa = 1;
									memset(server_reply, 0, sizeof(server_reply));
									// close(sock);
									// return 1;
									// quit = 1;
								}
								else if (strcmp(server_reply, "tuchoicauhoa") == 0)
								{
									cauhoa = 0;
									memset(server_reply, 0, sizeof(server_reply));
								}
								else
								{
									receivedVerifyMessage(server_reply);

									// Clear buffer
									memset(server_reply, 0, sizeof(server_reply));
								}
							}
							else if (r_recv == 0)
							{
								serverchiuthua = 1;
								// close(sock);
								// return 1;
								// quit = 1;
							}
						}
					}
				}
				if (inmenu == 0)
					inMenu();

				if (inbanco == 1)
				{
					ImageInfo image1, image2, image3, image4, image5, image6, image7, image8;

					// Load thông tin cho mỗi ảnh
					if (
						!loadMedia(&image1, "image/dsonl.jpg", 0, 0) ||
						!loadMedia(&image2, "image/nguoichoi1.jpg", 530, 0) ||
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

					r_recv = recv(sock, server_reply, 2000, MSG_DONTWAIT);
					if (r_recv > 0)
					{
						if (strcmp(server_reply, "tamdung") == 0)
						{
							servertamdung = 1;
							memset(server_reply, 0, sizeof(server_reply));
						}
						else if (strcmp(server_reply, "tieptuc") == 0)
						{
							servertamdung = 0;
							memset(server_reply, 0, sizeof(server_reply));
						}
						else if (strcmp(server_reply, "cauhoa") == 0)
						{
							servercauhoa = 1;
							memset(server_reply, 0, sizeof(server_reply));
						}
						else if (strcmp(server_reply, "chiuthua") == 0)
						{
							serverchiuthua = 1;
							memset(server_reply, 0, sizeof(server_reply));
						}
						else if (strcmp(server_reply, "icon") == 0)
						{
							servericon = 1;
							memset(server_reply, 0, sizeof(server_reply));
						}
						else if (strcmp(server_reply, "defeat") == 0)
						{
							chiuthua = 1;
							memset(server_reply, 0, sizeof(server_reply));
						}
						else if (strcmp(server_reply, "chapnhancauhoa") == 0)
						{
							chapnhancauhoa = 1;
							memset(server_reply, 0, sizeof(server_reply));
							// close(sock);
							// return 1;
							// quit = 1;
						}
						else if (strcmp(server_reply, "tuchoicauhoa") == 0)
						{
							cauhoa = 0;
							memset(server_reply, 0, sizeof(server_reply));
						}
						else
						{
							receivedVerifyMessage(server_reply);

							// Clear buffer
							memset(server_reply, 0, sizeof(server_reply));
						}
					}
					else if (r_recv == 0)
					{
						serverchiuthua = 1;
						// close(sock);
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

					if (servertamdung == 1)
					{
						ImageInfo image1;
						if (loadMedia(&image1, "image/yctamdung.jpg", 0, 80))
						{
							SDL_BlitSurface(image1.surface, NULL, gScreenSurface, &image1.position);
						}
						closeImage(&image1);
					}
					if (servercauhoa == 1)
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
					if (serverchiuthua == 1)
					{
						ImageInfo image1;
						if (loadMedia(&image1, "image/win.jpg", 0, 80))
						{
							SDL_BlitSurface(image1.surface, NULL, gScreenSurface, &image1.position);
						}
						closeImage(&image1);
					}
					if (servericon == 1)
					{
						ImageInfo image1;
						if (loadMedia(&image1, "image/icon.png", 0, 80))
						{
							SDL_BlitSurface(image1.surface, NULL, gScreenSurface, &image1.position);
						}
						closeImage(&image1);
					}
				}

				SDL_UpdateWindowSurface(gWindow);
			}
			SDL_DestroyWindow(gWindow);
			SDL_Quit();
		}
	}
	// }

	return 0;
}
