#ifndef _FUNCTION_H_
#define _FUNCTION_H_

using namespace std;

#define SUITS 4
#define FACES 13


// ALLOCATE MEMORY
int** memAlloc_2D(int row, int col);

int*** memAlloc_ListOf2D(int num2DArr, int row, int col);


// FREE MEMORY
void memFree_2D(int** a, int row);

void memFree_ListOf2D(int*** a, int num2DArr, int row);


// INPUT DATA
void inputNumOfGames(int& numOfGames);

void inputNumOfPlayers(int& numOfPlayers);

void inputNumOfReplacedCards(int& numOfReplacedCards);


// PRINTING FUNCTIONS
void printCardsShuffling(int deck[SUITS][FACES]);

void printHand(int** hand);

void printHands(int*** hands, int numOfPlayers);

void printResult(int** dealerHand, int** playerHand);

void printChangedCards(int numOfReplacedCards, int cardPosition[]);


// SHUFFLE AND DEAL CARDS
void shuffleCards(int deck[SUITS][FACES]);

int** dealingForHand(int deck[SUITS][FACES], int order, int numOfPlayers);

int*** dealingForHands(int deck[SUITS][FACES], int numOfPlayers);

int** createHandTest(int deck[SUITS][FACES], int a[]);


// CHECK STATUS
int isFourOfAKind(int** hand);

int isFullHouse(int** hand);

int isFlush(int** hand);

int isStraight(int** hand);

int isStraightFlush(int** hand);

int isThreeOfAKind(int** hand);

int isTwoPairs(int** hand);

int isPair(int** hand);

int getHighestCard(int** hand);


// PRINT STATUS
int getStatusOfHand(int** hand);

void printStatus(int** hand);


// RANKING IN 1 ROUND
int* rankingHands(int*** hands, int numOfPlayers);

void printRankingHands(int* rank, int numOfPlayers);


// RANKING IN ALL ROUND
void printHighestRank(int* rank, int numOfPlayers);

int* evaluateHands(int* Score, int* rank, int numOfPlayers);


// CARD REPLACEMENT FUNCTIONS
void replaceCard(int deck[SUITS][FACES], int** hand, int cardPosition);

void randomReplace(int deck[SUITS][FACES], int** hand);

void betterReplace(int deck[SUITS][FACES], int** hand);

void selectReplace(int deck[SUITS][FACES], int** hand);

void drawingNewCards(int deck[SUITS][FACES], int** hand);

void askDealerToDraw(int deck[SUITS][FACES], int** hand, bool& Ans);

void askPlayerToDraw(int deck[SUITS][FACES], int** hand, bool& Ans);


// CONSOLE INTERFACE FUNCTIONS
void pokerArt();

void endArt();

void SetColor(int backgound_color, int text_color);

void GoTo(int posX, int posY);

void ShowCur(bool CursorVisibility);


// EXTERNAL FUNCTIONS
void randomCard(int& x, int& y);

void resetArray(int* a, int lenA);

void resetArray_2D(int** a, int row, int col);

int findMax(int* arr, int n);

int findMax_2D(int arr[SUITS][FACES], int row, int col);

int findTopCard(int deck[SUITS][FACES]);

void copyHandAToHandB(int** A, int** B);

void copyDeckAToDeckB(int A[SUITS][FACES], int B[SUITS][FACES]);

void addHandLine(wstring handLine[], int suit, int face);

bool checkDrawn(int drawnCard[], int cardPosition);

void Swap(int& a, int& b);

void sortHand(int** hand);

#endif