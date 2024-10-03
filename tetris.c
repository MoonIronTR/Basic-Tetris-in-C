#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WIDTH 22
#define MAX_HEIGHT 40
#define MAX_HIGH_SCORES 10


void initializeGameBoard(char board[MAX_HEIGHT][MAX_WIDTH], int boardHeight, int boardWidth);
void printGameBoard(char board[MAX_HEIGHT][MAX_WIDTH], int boardHeight, int boardWidth);
void printPiece(char piece[4][4]);
void generateRandomPiece(char piece[4][4], int *pieceWidth, int *pieceHeight);
void rotatePiece(char piece[4][4], int *pieceWidth, int *pieceHeight, int clockwise);
void placePiece(char board[MAX_HEIGHT][MAX_WIDTH], char piece[4][4], int boardWidth, int boardHeight, int pieceWidth, int pieceHeight, int positionX);
int checkLines(char board[MAX_HEIGHT][MAX_WIDTH], int boardWidth, int boardHeight, int *score, int *highScore);



int main() {
    int choice, gameRunning = 1, isInGame = 0, posX, x, i, j, gameOverChoice, updateIndex;
    int boardWidth, boardHeight, score, highScore = 0;
    char board[MAX_HEIGHT][MAX_WIDTH];
    int pieceWidth, pieceHeight;
    int highScores[MAX_HIGH_SCORES] = {0};
    char rotation;

    srand((unsigned int)time(NULL));

    while (gameRunning) {
        printf("Main Menu:\n");
        printf("1 - Start Game\n");
        printf("2 - Check My Scores\n");
        printf("3 - How to Play\n");
        printf("4 - Exit Game\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            score = 0;
            isInGame = 1;
            printf("Welcome to Simple Tetris\n");
            printf("Enter board dimensions (Width Height): ");
            scanf("%d %d", &boardWidth, &boardHeight);

            if (boardWidth >= 6 && boardWidth <= MAX_WIDTH-2 && boardHeight >= 8 && boardHeight <= MAX_HEIGHT) {
                initializeGameBoard(board, boardHeight, boardWidth);

                while (isInGame) {
                    char currentPiece[4][4];
                    generateRandomPiece(currentPiece, &pieceWidth, &pieceHeight);
                    printf("Score: %d\n", score);
                    printGameBoard(board, boardHeight, boardWidth);
					
					// D�nd�rme
                    int rotate = 1;
                    while (rotate) {
                        printf("Enter rotation choice ('a' for left, 'd' for right, any other key for stop rotating): ");
                        scanf(" %c", &rotation);

                        if (rotation == 'a' || rotation == 'A') {
                            rotatePiece(currentPiece, &pieceWidth, &pieceHeight, 0);
                        } else if (rotation == 'd' || rotation == 'D') {
                            rotatePiece(currentPiece, &pieceWidth, &pieceHeight, 1);
                        } else {
                            rotate = 0;
                        }
                        printGameBoard(board, boardHeight, boardWidth);
                    }
					
					// Par�a Yerle�tirme
					
                    printPiece(currentPiece);
                    printGameBoard(board, boardHeight, boardWidth);
                    printf("Enter X position for the piece (1 to %d): ", boardWidth - pieceWidth + 1);
                    scanf("%d", &posX);

                    if (posX < 1 || posX + pieceWidth > boardWidth + 1) {
                        printf("Invalid position. Try again.\n");
                    } else {
                        placePiece(board, currentPiece, boardWidth, boardHeight, pieceWidth, pieceHeight, posX);
                        
                        // Sat�rda 0 yoksa sat�r� silme ve puan ekleme
                        
                        if (checkLines(board, boardWidth, boardHeight, &score, &highScore) > 0) {
                            printf("Lines cleared!\n");
                        }
                        printGameBoard(board, boardHeight, boardWidth);
                        printf("Score: %d High Score: %d \n", score,highScore);

                        	
								// En �st sat�ra par�a gelmi�se oyun bitimi
            
						    	for (x = 1; x <= boardWidth && isInGame; x++) {
						        if (board[0][x] != '0') {
						            printf("Game Over! Final score: %d\n", score);
						            isInGame = 0;
						            
						        }
						    }
						
						    // Kullan�c�n�n oyunu bitirme kontrol�
						    
						    if (isInGame) {
						        char continuePlayingChoice;
						        printf("Continue playing? (q for quit any other key to continue): ");
						        scanf(" %c", &continuePlayingChoice);
						
						        if (continuePlayingChoice == 'q' || continuePlayingChoice == 'Q') {
						        	printf("Game Over! Final score: %d\n", score);
						            isInGame = 0;
						        }
						    }
					}
					
					// HighScore Kontrol�
					
                    if (!isInGame) {
					    updateIndex = -1;
					    i = 0;
					    while (i < MAX_HIGH_SCORES && updateIndex == -1) {
					        if (score > highScores[i]) {
					            updateIndex = i;
					        }
					        i++;
					    }
					
					    if (updateIndex != -1) {
					        // Y�ksek skor listesinde yer a�mak i�in skorlar� birer pozisyon geri kayd�r
					        for (i = MAX_HIGH_SCORES - 1; i > updateIndex; i--) {
					        highScores[i] = highScores[i - 1];
					        }
					        // Yeni skoru bulunan pozisyona yerle�tir
        					highScores[updateIndex] = score;
					    }
					}
                }
            } else {
                printf("Invalid board size! Width must be between 6 and %d, height must be between 8 and %d.\n", MAX_WIDTH-2, MAX_HEIGHT);
            }
            
        // HighScore listesi
        
        } else if (choice == 2) {
            printf("High Scores:\n");
            for (i = 0; i < MAX_HIGH_SCORES; i++) {
                printf("%d. %d\n", i + 1, highScores[i]);
            }
            
        // Tan�t�m ve Kurallar
        
        } else if (choice == 3) {
	    printf("Game Introduction:\n");
		printf("1. At the start of the game, you will be asked to enter the dimensions of the game board (width and height).\n");
		printf("2. The game board is represented by a grid where '0' indicates an empty space.\n");
		printf("3. There are 7 different pieces in the game, each represented by a unique number from 1 to 7.\n");
		printf("Game Rules:\n");
		printf("4. Pieces of different shapes fall from the top of the board.\n");
		printf("5. Use the 'a' or 'A' and 'd' or 'D' keys to rotate the pieces left or right respectively.\n");
		printf("6. The player must move and rotate the pieces to form horizontal lines of blocks without gaps.\n");
		printf("7. When such a line is created, it disappears, and any block above the deleted line will fall.\n");
		printf("8. The game continues until the stack of pieces reaches the top of the board and no new pieces can enter.\n");
		printf("9. The player can press 'q' or 'Q' during the game to quit early.\n");
		printf("10. The goal is to clear as many lines as possible to achieve a high score.\n");
		printf("11. The score is calculated by multiplying the number of cleared lines with the board's width.\n");
		printf("Enter '1' to start a new game or '3' to exit.\n");

        } else if (choice == 4) {
            gameRunning = 0;
        }
    }

    printf("Thank you for playing!\n");
    return 0;
}

void initializeGameBoard(char board[MAX_HEIGHT][MAX_WIDTH], int boardHeight, int boardWidth) {
    int i, j;
    for (i = 0; i < boardHeight; i++) {
        board[i][0] = '|';
        for (j = 1; j <= boardWidth; j++) {
            board[i][j] = '0';
        }
        board[i][boardWidth + 1] = '|';
    }
}

void printGameBoard(char board[MAX_HEIGHT][MAX_WIDTH], int boardHeight, int boardWidth) {
    int i, j;
    for (i = 0; i < boardHeight; i++) {
        for (j = 0; j <= boardWidth + 1; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("*-");
    for (j = 1; j <= boardWidth; j++) {
        printf("--");
    }
    printf("*\n");
}


void printPiece(char piece[4][4]) {
    int i, j;
    printf("Piece:\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%c ", piece[i][j]);
        }
        printf("\n");
    }
}



void generateRandomPiece(char piece[4][4], int *pieceWidth, int *pieceHeight) {
    int pieceType;
    char pieceChar;
    int i, j;

    // Par�an�n ba�lang�� durumunu temizle
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            piece[i][j] = ' ';
        }
    }

    pieceType = rand() % 7; // 7 farkl� Tetris par�as� i�in rastgele se�im
     
  	//pieceType = 0; // Manuel Par�a se�imi(Bug kontrol� i�in)
  	
    pieceChar = '1' + pieceType;

     	// I par�as�
    if (pieceType == 0) { 
        for (i = 0; i < 4; i++) piece[i][0] = pieceChar;
        
    	// O par�as�
    } else if (pieceType == 1) { 
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                piece[i][j] = pieceChar;
            }
        }
        
		// T par�as�
    } else if (pieceType == 2) { 
        for (i = 0; i < 3; i++) piece[0][i] = pieceChar;
        piece[1][1] = pieceChar;
        
        // S par�as�
    } else if (pieceType == 3) { 
        piece[0][1] = pieceChar; piece[0][2] = pieceChar;
        piece[1][0] = pieceChar; piece[1][1] = pieceChar;
        
        // Z par�as�
    } else if (pieceType == 4) { 
        piece[0][0] = pieceChar; piece[0][1] = pieceChar;
        piece[1][1] = pieceChar; piece[1][2] = pieceChar;
        
        // J par�as�
    } else if (pieceType == 5) { 
        piece[2][0] = pieceChar;
        for (i = 0; i < 3; i++) piece[i][1] = pieceChar;
        
        // L par�as�
    } else if (pieceType == 6) { 
        piece[2][1] = pieceChar;
        for (i = 0; i < 3; i++) piece[i][0] = pieceChar;
    }

    // Par�an�n geni�li�ini ve y�ksekli�ini hesapla
    *pieceWidth = 0;
    *pieceHeight = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (piece[i][j] != ' ') {
                if (j + 1 > *pieceWidth) {
                    *pieceWidth = j + 1;
                }
                if (i + 1 > *pieceHeight) {
                    *pieceHeight = i + 1;
                }
            }
        }
	}

    printPiece(piece);
}


void rotatePiece(char piece[4][4], int *pieceWidth, int *pieceHeight, int clockwise) {
    char temp[4][4];
    int i, j;

    // Par�ay� ge�ici bir matrise kopyala
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            temp[i][j] = piece[i][j];
        }
    }

    // Par�ay� d�nd�r
    if (clockwise) {
        for (i = 0; i < *pieceHeight; i++) {
            for (j = 0; j < *pieceWidth; j++) {
                piece[j][*pieceHeight - 1 - i] = temp[i][j]; // Saat y�n�nde d�nd�r
            }
        }
    } else {
        for (i = 0; i < *pieceHeight; i++) {
            for (j = 0; j < *pieceWidth; j++) {
                piece[*pieceWidth - 1 - j][i] = temp[i][j]; // Saat y�n�n�n tersine d�nd�r
            }
        }
    }

    // Par�an�n yeni geni�li�ini ve y�ksekli�ini hesapla
    int newWidth = *pieceHeight;
    int newHeight = *pieceWidth;

    // Par�ay� sola kayd�r, e�er sol en s�tun bo�sa(yerle�tirme i�in)
    int columnEmpty = 1;
    for (i = 0; i < newHeight && columnEmpty; i++) {
        if (piece[i][0] != ' ') {
            columnEmpty = 0;
        }
    }

    if (columnEmpty) {
        for (i = 0; i < newHeight; i++) {
            for (j = 0; j < newWidth - 1; j++) {
                piece[i][j] = piece[i][j + 1];
            }
            piece[i][newWidth - 1] = ' '; // Kayd�rd�ktan sonra son s�tunu temizle
        }
        newWidth--; // E�er par�ay� sola kayd�rd�ysak geni�li�i azalt
    }

    // Par�a matrisini g�ncelle
    for (i = newHeight; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            piece[i][j] = ' '; // Kullan�lmayan sat�rlar� temizle
        }
    }
    for (j = newWidth; j < 4; j++) {
        for (i = 0; i < newHeight; i++) {
            piece[i][j] = ' '; // Kullan�lmayan s�tunlar� temizle
        }
    }

    *pieceWidth = newWidth;
    *pieceHeight = newHeight;
    printPiece(piece);
}

void placePiece(char board[MAX_HEIGHT][MAX_WIDTH], char piece[4][4], int boardWidth, int boardHeight, int pieceWidth, int pieceHeight, int positionX) {
    int i, j, y;
    int canPlace = 0;
    int piecePlaced = 0; // Bu flag par�an�n yerle�tirilip yerle�tirilmedi�ini kontrol eder

    for (y = 0; y <= boardHeight && !piecePlaced; y++) {
        canPlace = 1;

        for (i = 0; i < pieceHeight && canPlace; i++) {
            for (j = 0; j < pieceWidth && canPlace; j++) {
                if (piece[i][j] != ' ' && (y + i >= boardHeight || board[y + i][positionX + j] != '0')) {
                    canPlace = 0;
                }
            }
        }

        if (!canPlace && y > 0) {
            y--;
            for (i = 0; i < pieceHeight; i++) {
                for (j = 0; j < pieceWidth; j++) {
                    if (piece[i][j] != ' ' && y + i < boardHeight) {
                        board[y + i][positionX + j] = piece[i][j]; // Par�an�n kendine �zg� karakterini kullan
                    }
                }
            }
            piecePlaced = 1; // Par�a yerle�tirildi, d�ng�y� sonland�rmak i�in flag'i g�ncelle
        }
    }

    if (!piecePlaced) { // E�er piecePlaced flag'i hala 0 ise, par�a yerle�tirilememi� demektir.
        printf("Par�a yerle�tirilemedi! Oyun Bitti veya Hatal� Giri�.\n");
    }
}



int checkLines(char board[MAX_HEIGHT][MAX_WIDTH], int boardWidth, int boardHeight, int *score, int *highScore) {
    int full, i, j, linesCleared = 0;
    int k;

    for (i = 0; i < boardHeight; i++) {
        full = 1;
        for (j = 1; j <= boardWidth && full; j++) {
            if (board[i][j] == '0') {
                full = 0;
            }
        }

        if (full) {
            for (j = 1; j <= boardWidth; j++) {
                board[i][j] = '0';
            }
            for (k = i; k > 0; k--) {
                for (j = 1; j <= boardWidth; j++) {
                    board[k][j] = board[k - 1][j];
                }
            }

            for (j = 1; j <= boardWidth; j++) {
                board[0][j] = '0';
            }
            board[0][0] = '|'; // En �st sat�r�n sol kenar� korunur

            linesCleared++;
            *score += boardWidth * 10;
        }
    }

    if (*score > *highScore) {
        *highScore = *score;
    }

    return linesCleared;
}



