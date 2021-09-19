#include <iostream>
#include <Windows.h>
#include <io.h> // Thư Viện Để Dùng Unicode
#include <fcntl.h> // Thư Viện Để Dùng Unicode
#include "Function.h"

using namespace std;

#define SUITS 4
#define FACES 13
wstring suits[SUITS] = { L"♥", L"♦", L"♣", L"♠" };
wstring faces[FACES] = { L"A", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"10", L"J", L"Q", L"K" };


// ALLOCATE MEMORY
int** memAlloc_2D(int row, int col) {
	int** a = new int* [row];
	for (int i = 0; i < row; i++) {
		a[i] = new int[col];
	}
	return a;
}

int*** memAlloc_ListOf2D(int num2DArr, int row, int col) {
	int*** a = new int** [num2DArr];
	for (int i = 0; i < num2DArr; i++) {
		a[i] = memAlloc_2D(row, col);
	}
	return a;
}


// FREE MEMORY
void memFree_2D(int** a, int row) {
	for (int i = 0; i < row; i++) {
		delete[] a[i];
	}
	delete[] a;
}

void memFree_ListOf2D(int*** a, int num2DArr, int row) {
	for (int i = 0; i < num2DArr; i++) {
		memFree_2D(a[i], row);
	}
	delete[] a;
}


// INPUT DATA
void inputNumOfGames(int& numOfGames) {
	do {
		system("cls");
		GoTo(8, 3);
		cout << "The number of games = ";
		cin >> numOfGames;
		if (numOfGames < 1 || numOfGames > 50) {
			cout << "The number of games must be 1-50!" << endl;
			system("pause");
		}
	} while (numOfGames < 1 || numOfGames > 50);
}

void inputNumOfPlayers(int& numOfPlayers) {
	do {
		system("cls");
		GoTo(8, 3);
		cout << "The number of players = ";
		cin >> numOfPlayers;
		if (numOfPlayers < 2 || numOfPlayers > 10) {
			cout << "The number of players must be 2-10!" << endl;
			system("pause");
		}
	} while (numOfPlayers < 2 || numOfPlayers > 10);
}

void inputNumOfReplacedCards(int& numOfReplacedCards) {
	do {
		cout << "\n\t\t\t\tThe Number Of Cards You Want To Draw: ";
		cin >> numOfReplacedCards;
		if (numOfReplacedCards < 1 || numOfReplacedCards > 3) {
			cout << "\t\t\t\tThe Number Of Cards Must Be 1-3!" << endl;
		}
	} while (numOfReplacedCards < 1 || numOfReplacedCards > 3);
}


// PRINTING FUNCTIONS
void printCardsShuffling(int deck[SUITS][FACES]) {
	_setmode(_fileno(stdout), _O_U16TEXT); // Use UNICODE text
	wcout << L"       ORDER    DECK" << endl;
	for (int card = 1; card <= 52; card++) {
		for (int i = 0; i < SUITS; i++) {
			for (int j = 0; j < FACES; j++) {
				if (deck[i][j] == card) {
					if (card < 10) {
						wcout << "\t#" << card << "\t " << faces[j] << suits[i] << endl;
					}
					else {
						wcout << "\t#" << card << "\t " << faces[j] << suits[i] << endl;
					}
				}
			}
		}
	}
	wcout << endl;
	_setmode(_fileno(stdout), _O_TEXT); // Use ASCII text
}

void printHand(int** hand) {
	_setmode(_fileno(stdout), _O_U16TEXT); // Use UNICODE text
	wstring handLine[9];

	for (int card = 0; card < 5; card++) {
		addHandLine(handLine, hand[card][0], hand[card][1]);
	}

	for (int i = 0; i <= 8; i++) {
		wcout << "\t\t\t\t" << handLine[i] << endl;
	}
	_setmode(_fileno(stdout), _O_TEXT); // Use ASCII text
	cout << "\t\t\t\t    #1           #2          #3          #4          #5\n" << endl;
	printStatus(hand);
	cout << endl;
}

void printHands(int*** hands, int numOfPlayers) {
	for (int order = 1; order <= numOfPlayers; order++) { // The variable order is the order of the player
		if (numOfPlayers != 1) {
			cout << "\n\t\t\t\t\t\t     #" << order << " PLAYER'S HAND" << endl;
		}
		printHand(hands[order - 1]);
	}
}

void printResult(int** dealerHand, int** playerHand) {
	if (getStatusOfHand(dealerHand) > getStatusOfHand(playerHand)) {
		cout << "\t\t\t\t\t\t    ==== YOU LOSE ====\n" << endl;
	}
	else if (getStatusOfHand(dealerHand) < getStatusOfHand(playerHand)) {
		cout << "\t\t\t\t\t\t    ==== YOU WIN! ====\n" << endl;
	}
	else {
		int playerHighestCard = getHighestCard(playerHand);
		int dealerHighestCard = getHighestCard(dealerHand);

		_setmode(_fileno(stdout), _O_U16TEXT); // Use UNICODE text
		wcout << L"\t\t\t\tYOUR HIGHEST CARD: " << faces[playerHighestCard] << endl;
		wcout << L"\t\t\t\tDEALER'S HIGHEST CARD: " << faces[dealerHighestCard] << endl;
		_setmode(_fileno(stdout), _O_TEXT); // Use ASCII text

		if ((dealerHighestCard > playerHighestCard && playerHighestCard != 0) || (dealerHighestCard == 0 && playerHighestCard != 0)) {
			cout << "\n\t\t\t\t\t\t    ==== YOU LOSE ====\n" << endl;
		}
		else if ((dealerHighestCard < playerHighestCard && dealerHighestCard != 0) || (dealerHighestCard != 0 && playerHighestCard == 0)) {
			cout << "\n\t\t\t\t\t\t    ==== YOU WIN! ====\n" << endl;
		}
		else {
			cout << "\n\t\t\t\t\t\tTHIS GAME IS A TIE\n" << endl;
		}
	}
}

void printChangedCards(int numOfReplacedCards, int cardPosition[]) {
	Sleep(1000);
	cout << "\t\t\t\tTHE DEALER HAS DRAWN " << numOfReplacedCards << " CARDS" << endl;
	Sleep(1000);

	cout << "\n\t\t\t\tTHE CARDS ARE DISCARDED: ";
	for (int i = 0; i < 5; i++) {
		if (cardPosition[i] != 0) {
			cout << "#" << cardPosition[i] << " ";
		}
	}
	cout << endl;
	Sleep(1000);
}


// SHUFFLE AND DEAL CARDS
void shuffleCards(int deck[SUITS][FACES]) {
	int x, y;
	randomCard(x, y);
	for (int card = 1; card <= 52; card++) {
		while (deck[x][y] != 0) {
			randomCard(x, y);
		}
		deck[x][y] = card;
	}
}

int** dealingForHand(int deck[SUITS][FACES], int order, int numOfPlayers) {
	int** hand = memAlloc_2D(5, 2);
	resetArray_2D(hand, 5, 2);

	int handCard = 0;
	for (int deckCard = order; deckCard <= 5 * numOfPlayers; deckCard += numOfPlayers) {
		int flag = 0;
		for (int i = 0; i < SUITS; i++) {
			for (int j = 0; j < FACES; j++) {
				if (deck[i][j] == deckCard) {
					hand[handCard][0] = i;
					hand[handCard][1] = j;
					handCard++;

					deck[i][j] = 0; // Means this card has been dealt to hand

					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				break;
			}
		}
	}

	// Sort the hand
	sortHand(hand);

	return hand;
}

int*** dealingForHands(int deck[SUITS][FACES], int numOfPlayers) {
	int*** hands = memAlloc_ListOf2D(numOfPlayers, 5, 2);
	for (int order = 1; order <= numOfPlayers; order++) { // The variable order is the order of the player
		hands[order - 1] = dealingForHand(deck, order, numOfPlayers);
	}
	return hands;
}

int** createHandTest(int deck[SUITS][FACES], int a[]) { 
	int** hand = memAlloc_2D(5, 2);
	resetArray_2D(hand, 5, 2);

	int handCard = 0;
	for (int deckCard = 0; deckCard < 5; deckCard++) {
		int flag = 0;
		for (int i = 0; i < SUITS; i++) {
			for (int j = 0; j < FACES; j++) {
				if (deck[i][j] == a[deckCard]) {
					hand[handCard][0] = i;
					hand[handCard][1] = j;
					handCard++;

					deck[i][j] = 0; // Means this card has been dealt to hand

					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				break;
			}
		}
	}

	// Sort the hand
	sortHand(hand);

	return hand;
}


// CHECK STATUS
int isFourOfAKind(int** hand) {
	// Four cards of one rank and one card of another rank
	for (int face = 0; face < FACES; face++) {
		int count = 0;
		for (int i = 0; i < 5; i++) {
			if (hand[i][1] == face) {
				count++;
			}
		}
		if (count == 4) {
			return 1;
		}
	}
	return 0;
}

int isFullHouse(int** hand) {
	// Three cards of one rank and two cards of another rank
	if (isThreeOfAKind(hand) && isPair(hand)) {
		return 1;
	}
	return 0;
}

int isFlush(int** hand) {
	// Five cards all of the same suit, not all of sequential rank
	for (int suit = 0; suit < SUITS; suit++) {
		int count = 0;
		for (int i = 0; i < 5; i++) {
			if (hand[i][0] == suit) {
				count++;
			}
		}
		if (count == 5) {
			return 1;
		}
	}
	return 0;
}

int isStraight(int** hand) {
	// Five cards of sequential rank, not all of the same suit
	// Highest Straight: 10 J Q K A
	if ((hand[0][1] == 9) && (hand[1][1] == 10) && (hand[2][1] == 11) && (hand[3][1] == 12) && (hand[4][1] == 0)) {
		return 1;
	}
	// Lower Straights
	if ((hand[1][1] == hand[0][1] + 1) && (hand[2][1] == hand[1][1] + 1) && (hand[3][1] == hand[2][1] + 1) && (hand[4][1] == hand[3][1] + 1)) {
		return 1;
	}
	return 0;
}

int isStraightFlush(int** hand) { // Five cards of sequential rank, all of the same suits
	if (isStraight(hand) && isFlush(hand)) {
		return 1;
	}
	return 0;
}

int isThreeOfAKind(int** hand) {
	// Three cards of one rank and two cards of two other ranks
	for (int face = 0; face < FACES; face++) {
		int count = 0;
		for (int i = 0; i < 5; i++) {
			if (hand[i][1] == face) {
				count++;
			}
		}
		if (count == 3) {
			return 1;
		}
	}
	return 0;
}

int isTwoPairs(int** hand) {
	// Two cards of one rank, two cards of another rankand one card of a third rank
	int numOfPair = 0;
	for (int face = 0; face < FACES; face++) {
		int count = 0;
		for (int i = 0; i < 5; i++) {
			if (hand[i][1] == face) {
				count++;
			}
		}
		if (count == 2) {
			numOfPair++;
		}
	}
	if (numOfPair == 2) {
		return 1;
	}
	return 0;
}

int isPair(int** hand) {
	// Two cards of one rank and three cards of three other ranks
	int numOfPair = 0;
	for (int face = 0; face < FACES; face++) {
		int count = 0;
		for (int i = 0; i < 5; i++) {
			if (hand[i][1] == face) {
				count++;
			}
		}
		if (count == 2) {
			numOfPair++;
		}
	}
	if (numOfPair == 1) {
		return 1;
	}
	return 0;
}

int getHighestCard(int** hand) {
	sortHand(hand);
	return hand[4][1];
}


// PRINT STATUS
int getStatusOfHand(int** hand) {
	int category = 0; // <=> High Card
	if (isStraightFlush(hand)) {
		category = 8;
	}
	else if (isFourOfAKind(hand)) {
		category = 7;
	}
	else if (isFullHouse(hand)) {
		category = 6;
	}
	else if (isFlush(hand)) {
		category = 5;
	}
	else if (isStraight(hand)) {
		category = 4;
	}
	else if (isThreeOfAKind(hand)) {
		category = 3;
	}
	else if (isTwoPairs(hand)) {
		category = 2;
	}
	else if (isPair(hand)) {
		category = 1;
	}
	return category;
}

void printStatus(int** hand) {
	int category = getStatusOfHand(hand);
	switch (category) {
	case 8:
		cout << "\t\t\t\t\t\t===== STRAIGHT FLUSH! =====" << endl;
		break;
	case 7:
		cout << "\t\t\t\t\t\t===== FOUR OF A KIND! =====" << endl;
		break;
	case 6:
		cout << "\t\t\t\t\t\t  ===== FULL HOUSE! =====" << endl;
		break;
	case 5:
		cout << "\t\t\t\t\t\t    ===== FLUSH! =====" << endl;
		break;
	case 4:
		cout << "\t\t\t\t\t\t   ===== STRAIGHT! =====" << endl;
		break;
	case 3:
		cout << "\t\t\t\t\t\t===== THREE OF A KIND! =====" << endl;
		break;
	case 2:
		cout << "\t\t\t\t\t\t  ===== TWO PAIRS! =====" << endl;
		break;
	case 1:
		cout << "\t\t\t\t\t\t     ===== PAIR! =====" << endl;
		break;
	case 0:
		cout << "\t\t\t\t\t\t   ===== HIGH CARD! =====" << endl;
		break;
	}
}


// RANKING IN 1 ROUND
int* rankingHands(int*** hands, int numOfPlayers) {
	int* rank = new int[numOfPlayers];
	for (int i = 0; i < numOfPlayers; i++) {
		rank[i] = getStatusOfHand(hands[i]);
	}
	return rank;
}

void printRankingHands(int* rank, int numOfPlayers) {
	cout << "\t\t\t\t\t\t     SCORE BOARD " << endl;
	for (int i = 0; i < numOfPlayers; i++) {
		cout << "\t\t\t\t\t\t\t#" << i + 1 << ": " << rank[i] << endl;
	}
}


// RANKING IN ALL ROUND
void printHighestRank(int* rank, int numOfPlayers) {
	int highestRank = findMax(rank, numOfPlayers);
	for (int i = 0; i < numOfPlayers; i++) {
		if (rank[i] == highestRank) {
			cout << "#" << i + 1 << " ";
		}
	}
	cout << endl;
}

int* evaluateHands(int* Score, int* rank, int numOfPlayers) {
	// Increase point for the winner
	int highestRank = findMax(rank, numOfPlayers);
	for (int i = 0; i < numOfPlayers; i++) {
		if (rank[i] == highestRank) {
			Score[i] += 1;
		}
	}
	return Score;
}


// CARD REPLACEMENT FUNCTIONS
void replaceCard(int deck[SUITS][FACES], int** hand, int cardPosition) {
	// Draw a new card from the top 
	int topCard = findTopCard(deck);

	int flag = 0;
	for (int i = 0; i < SUITS; i++) {
		for (int j = 0; j < FACES; j++) {
			if (deck[i][j] == topCard) {
				hand[cardPosition - 1][0] = i;
				hand[cardPosition - 1][1] = j;

				deck[i][j] = 0; // This card in deck is set to 0

				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			break;
		}
	}
}

void randomReplace(int deck[SUITS][FACES], int** hand) {
	// Input data
	int numOfReplacedCards = 1 + rand() % 3;
	int cardPosition[5] = { 0 };

	// Drawing new cards
	for (int i = 0; i < numOfReplacedCards; i++) {
		bool isExist = true;
		int Card;
		do {
			Card = 1 + rand() % 5;
			isExist = checkDrawn(cardPosition, Card);
		} while (isExist == false);
		cardPosition[i] = Card;
		replaceCard(deck, hand, cardPosition[i]);
	}

	// Sort the hand
	sortHand(hand);

	// Print the change
	printChangedCards(numOfReplacedCards, cardPosition);
}

void betterReplace(int deck[SUITS][FACES], int** hand) {

	int** tempHand = memAlloc_2D(5, 2);
	int tempDeck[SUITS][FACES] = { 0 };

	int numOfReplacedCards, drawingTurn;
	int cardPosition[5];
	bool better = false;

	// Loop until better, if loopTimes = 100000 but not better then stop
	int loopTimes = 0;
	do {
		loopTimes++;
		// Reset tempHand and tempDeck
		copyHandAToHandB(hand, tempHand);
		copyDeckAToDeckB(deck, tempDeck);

		// Input data
		numOfReplacedCards = 1 + rand() % 3;
		drawingTurn = 0;
		resetArray(cardPosition, 5);

		// Drawing new cards
		for (int i = 0; i < numOfReplacedCards; i++) {
			bool isExist = true;
			int Card;
			do {
				Card = 1 + rand() % 5;
				isExist = checkDrawn(cardPosition, Card);
			} while (isExist == false);
			cardPosition[i] = Card;

			replaceCard(tempDeck, tempHand, cardPosition[i]);
			drawingTurn++;

			if (getStatusOfHand(tempHand) > getStatusOfHand(hand)) {
				better = true;
				break;
			}
		}

		// Sort the hand
		sortHand(tempHand);
	} while (better == false && loopTimes < 100000);

	if (better == true) {
		if (drawingTurn < numOfReplacedCards) {
			numOfReplacedCards = drawingTurn;
		}

		// Print the change
		printChangedCards(numOfReplacedCards, cardPosition);

		copyHandAToHandB(tempHand, hand);
		copyDeckAToDeckB(tempDeck, deck);
	}
	else {
		Sleep(1000);
		cout << "\t\t\t\tCAN'T DRAW BETTER IN THIS SITUATION!" << endl;
	}
	// Free memory
	memFree_2D(tempHand, 5);
}

void selectReplace(int deck[SUITS][FACES], int** hand) {
	// Input data
	int numOfReplacedCards;
	inputNumOfReplacedCards(numOfReplacedCards);
	int cardPosition[5] = { 0 };

	for (int i = 0; i < numOfReplacedCards; i++) {
		bool isExist = true;
		int Card;
		do {
			cout << "\n\t\t\t\tDiscard The Card: ";
			cin >> Card;
			isExist = checkDrawn(cardPosition, Card);
			if (isExist == false) {
				cout << "\t\t\t\tThis Card Has Been Selected Or Does Not Exist!" << endl;
			}
		} while (isExist == false);
		cardPosition[i] = Card;
		replaceCard(deck, hand, cardPosition[i]);
	}

	// Sort the hand
	sortHand(hand);
	cout << endl;
}

void drawingNewCards(int deck[SUITS][FACES], int** hand) {
	int selection;
	cout << "\t\t\t\t  * * * * * * * * Drawing Cards * * * * * * * *" << endl;
	cout << "\t\t\t\t  *   1. Random Replacement.                  *" << endl;
	cout << "\t\t\t\t  *   2. Replace To Get Better Situation.     *" << endl;
	cout << "\t\t\t\t  * * * * * * * * * * * * * * * * * * * * * * *" << endl;
	do {
		cout << "\n\t\t\t\tYour Choice: ";
		cin >> selection;
		if (selection != 1 && selection != 2) {
			cout << "\t\t\t\tTry Again!" << endl;
		}
	} while (selection != 1 && selection != 2);
	cout << endl;
	switch (selection) {
	case 1:
		randomReplace(deck, hand);
		break;
	case 2:
		betterReplace(deck, hand);
		break;
	}
}

void askDealerToDraw(int deck[SUITS][FACES], int** hand, bool& Ans) {
	if (getStatusOfHand(hand) == 0) { // High card ==> Draw
		Ans = true;
	}
	else { // Other things ==> Draw or not
		int selection = rand() % 2;
		if (selection == 1) {
			Ans = true;
		}
		else {
			Ans = false;
		}
	}

	if (Ans == true) {
		cout << "\n\t\t\t\tTHE DEALER WANTS TO DRAW CARDS" << endl;
		Sleep(1000);

		// Input data
		int numOfReplacedCards = 1 + rand() % 3;

		// Print the DEALER's previous hand
		cout << "\n\t\t\t\t\t\t  DEALER'S HAND (BEFORE)" << endl;
		printHand(hand);

		// Drawing new cards
		int cardPosition[5] = { 0 };
		for (int i = 0; i < numOfReplacedCards; i++) {
			bool isExist = true;
			int Card;
			do {
				Card = 1 + rand() % 5;
				isExist = checkDrawn(cardPosition, Card);
			} while (isExist == false);
			cardPosition[i] = Card;
			replaceCard(deck, hand, cardPosition[i]);
		}

		// Sort the hand
		sortHand(hand);

		// Print the change
		printChangedCards(numOfReplacedCards, cardPosition);
	}
	else {
		cout << "\n\t\t\t\tTHE DEALER DOESN'T WANT TO DRAW CARDS" << endl;
		Sleep(1000);
	}
}

void askPlayerToDraw(int deck[SUITS][FACES], int** hand, bool& Ans) {
	int selection;
	do {
		cout << "\t\t\t\tDo You Want To Draw Cards? (0 or 1). Your Choice: ";
		cin >> selection;
		if (selection != 0 && selection != 1) {
			cout << "\t\t\t\tTry Again!" << endl;
		}
	} while (selection != 0 && selection != 1);
	if (selection == 1) {
		Ans = true;
		// Drawing new cards
		selectReplace(deck, hand);
	}
	else {
		Ans = false;
		cout << endl;
	}
}


// CONSOLE SETTING FUNCTIONS
void addHandLine(wstring handLine[], int suit, int face) {
	handLine[0].append(L"┌─────────┐ ");

	handLine[1].append(L"│ ");
	handLine[1].append(faces[face]);
	if (face == 9) {
		handLine[1].append(L"      │ ");
	}
	else {
		handLine[1].append(L"       │ ");
	}

	handLine[2].append(L"│         │ ");

	handLine[3].append(L"│         │ ");

	handLine[4].append(L"│    ");
	handLine[4].append(suits[suit]);
	handLine[4].append(L"    │ ");

	handLine[5].append(L"│         │ ");

	handLine[6].append(L"│         │ ");

	handLine[7].append(L"│       ");
	handLine[7].append(faces[face]);
	if (face == 9) {
		handLine[7].append(L"│ ");
	}
	else {
		handLine[7].append(L" │ ");
	}

	handLine[8].append(L"└─────────┘ ");

}

void pokerArt() {
	cout << "\n\n\n\t\t\t\t$$$$$$$\\   $$$$$$\\  $$\\   $$\\ $$$$$$$$\\ $$$$$$$\\  " << endl;
	cout << "\t\t\t\t$$  __$$\\ $$  __$$\\ $$ | $$  |$$  _____|$$  __$$\\ " << endl;
	cout << "\t\t\t\t$$ |  $$ |$$ /  $$ |$$ |$$  / $$ |      $$ |  $$ |" << endl;
	cout << "\t\t\t\t$$$$$$$  |$$ |  $$ |$$$$$  /  $$$$$\\    $$$$$$$  |" << endl;
	cout << "\t\t\t\t$$  ____/ $$ |  $$ |$$  $$<   $$  __|   $$  __$$< " << endl;
	cout << "\t\t\t\t$$ |      $$ |  $$ |$$ |\\$$\\  $$ |      $$ |  $$ |" << endl;
	cout << "\t\t\t\t$$ |       $$$$$$  |$$ | \\$$\\ $$$$$$$$\\ $$ |  $$ |" << endl;
	cout << "\t\t\t\t\\__|       \\______/ \\__|  \\__|\\________|\\__|  \\__|" << endl;
}

void endArt() {
	cout << "\n\n\t\t  _____ ______ ______  __     ______  _    _   _            _______ ______ _____  _ " << endl;
	cout << "\t\t / ____|  ____|  ____| \\ \\   / / __ \\| |  | | | |        /\\|__   __|  ____|  __ \\| |" << endl;
	cout << "\t\t| (___ | |__  | |__     \\ \\_/ / |  | | |  | | | |       /  \\  | |  | |__  | |__) | |" << endl;
	cout << "\t\t \\___ \\|  __| |  __|     \\   /| |  | | |  | | | |      / /\\ \\ | |  |  __| |  _  /| |" << endl;
	cout << "\t\t ____) | |____| |____     | | | |__| | |__| | | |____ / ____ \\| |  | |____| | \\ \\|_|" << endl;
	cout << "\t\t|_____/|______|______|    |_|  \\____/ \\____/  |______/_/    \\_\\_|  |______|_|  \\_(_)\n" << endl;
}

void SetColor(int backgound_color, int text_color) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int color_code = backgound_color * 16 + text_color;
	SetConsoleTextAttribute(hStdout, color_code);
}

void GoTo(int posX, int posY) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = posX;
	Position.Y = posY;

	SetConsoleCursorPosition(hStdout, Position);
}

void ShowCur(bool CursorVisibility) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}


// EXTERNAL FUNCTIONS
void randomCard(int& x, int& y) {
	x = rand() % 4;
	y = rand() % 13;
}

void resetArray(int* a, int lenA) {
	for (int i = 0; i < lenA; i++) {
		a[i] = 0;
	}
}

void resetArray_2D(int** a, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			a[i][j] = 0;
		}
	}
}

int findMax(int* arr, int n) {
	int max = arr[0];
	for (int i = 0; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}

int findMax_2D(int arr[SUITS][FACES], int row, int col) {
	int max = arr[0][0];
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (arr[i][j] > max) {
				max = arr[i][j];
			}
		}
	}
	return max;
}

int findTopCard(int deck[SUITS][FACES]) {
	int topCard = 0;

	// Initialize min equal to the first NON-ZERO value in array
	for (int i = 0; i < SUITS; i++) {
		for (int j = 0; j < FACES; j++) {
			if (deck[i][j] != 0) {
				topCard = deck[i][j];
				break;
			}
		}
		if (topCard != 0) {
			break;
		}
	}

	// Find the NON-ZERO minimum value in array 
	for (int i = 0; i < SUITS; i++) {
		for (int j = 0; j < FACES; j++) {
			if (deck[i][j] < topCard && deck[i][j] != 0) {
				topCard = deck[i][j];
			}
		}
	}

	return topCard;
}

void copyHandAToHandB(int** A, int** B) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 2; j++) {
			B[i][j] = A[i][j];
		}
	}
}

void copyDeckAToDeckB(int A[SUITS][FACES], int B[SUITS][FACES]) {
	for (int i = 0; i < SUITS; i++) {
		for (int j = 0; j < FACES; j++) {
			B[i][j] = A[i][j];
		}
	}
}

bool checkDrawn(int drawnCard[], int cardPosition) {
	if (cardPosition == 1 || cardPosition == 2 || cardPosition == 3 || cardPosition == 4 || cardPosition == 5) {
		for (int i = 0; i < 5; i++) {
			if (drawnCard[i] == cardPosition) { // Means this card has been drawn
				return false;
			}
		}
		return true;
	}
	return false;
}

void Swap(int& a, int& b) {
	int c = a;
	a = b;
	b = c;
}

void sortHand(int** hand) {
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 5; j++) {
			if ((hand[i][1] > hand[j][1] && hand[j][1] != 0) || (hand[i][1] == 0 && hand[j][1] != 0)) {
				Swap(hand[i][1], hand[j][1]);
				Swap(hand[i][0], hand[j][0]);
			}
			else if (hand[i][1] == hand[j][1]) {
				if (hand[i][0] < hand[j][0]) {
					Swap(hand[i][1], hand[j][1]);
					Swap(hand[i][0], hand[j][0]);
				}
			}
		}
	}
}