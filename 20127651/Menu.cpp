#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <conio.h>
#include "Menu.h"
#include "Function.h"

using namespace std;

#define SUITS 4
#define FACES 13

// GAME FOR 1 PLAYER
void singlePlayer() {
	system("cls");

	// Input data
	int numOfGames, numOfPlayers = 1;
	inputNumOfGames(numOfGames);

	// Loop the game
	for (int i = 1; i <= numOfGames; i++) {
		system("cls");

		// Shuffle and print cards
		int deck[SUITS][FACES] = { 0 };
		shuffleCards(deck);
		printCardsShuffling(deck);

		// Dealing for hand
		int*** hands = dealingForHands(deck, numOfPlayers);

		// Print hand
		cout << "ROUND " << i << endl;
		cout << "\t\t\t\t\t\t\t YOUR HAND" << endl;
		printHand(hands[0]);

		// Free memory
		memFree_ListOf2D(hands, numOfPlayers, 5);
		system("pause");
	}
	cout << "\n\t\t\t\t\t===== T H E   G A M E   E N D S =====\n" << endl;
	system("pause");
}

// GAME FOR MULTIPLAYER
void Multiplayer() {
	system("cls");

	// Input data
	int numOfGames, numOfPlayers;
	inputNumOfGames(numOfGames);
	inputNumOfPlayers(numOfPlayers);

	// Each player's score
	int* Score = new int[numOfPlayers];

	// Loop the game
	for (int i = 1; i <= numOfGames; i++) {
		system("cls");

		// Shuffle and print cards
		int deck[SUITS][FACES] = { 0 };
		shuffleCards(deck);
		printCardsShuffling(deck);

		// Dealing for hand
		int*** hands = dealingForHands(deck, numOfPlayers);

		// Print hand
		cout << "ROUND " << i << endl;
		printHands(hands, numOfPlayers);

		// Print Rank
		int* rank = new int[numOfPlayers];
		rank = rankingHands(hands, numOfPlayers);
		printRankingHands(rank, numOfPlayers);

		// Score Update
		Score = evaluateHands(Score, rank, numOfPlayers);

		// Print the winner
		cout << "\nThe Players Win This Game: ";
		printHighestRank(rank, numOfPlayers);
		cout << "\nThe Players Have The Currently Highest Score: ";
		printHighestRank(Score, numOfPlayers);
		cout << endl;

		// Free memory
		delete[] rank;
		memFree_ListOf2D(hands, numOfPlayers, 5);
		system("pause");
	}
	delete[] Score;
	cout << "\n\t\t\t\t\t===== T H E   G A M E   E N D S =====\n" << endl;
	system("pause");
}

// TEST HAND
void testHand() {
	system("cls");

	// Input data
	int numOfGames = 1, numOfPlayers = 1;

	// Loop the game
	for (int i = 1; i <= numOfGames; i++) {
		system("cls");

		// Shuffle and print cards
		int deck[SUITS][FACES] = { 0 };
		shuffleCards(deck);
		printCardsShuffling(deck);

		// Dealing for hand
		int*** hands = memAlloc_ListOf2D(numOfPlayers, 5, 2);

		// Input data
		cout << "\t\t\t\t\t\t    TEST HAND\n" << endl;
		int cardPosition[5];
		for (int i = 0; i < 5; i++) {
			cout << "Draw #" << i + 1 << " Card: ";
			cin >> cardPosition[i];
		}
		hands[0] = createHandTest(deck, cardPosition);

		// Print hand
		cout << "\nROUND " << i << endl;
		cout << "\t\t\t\t\t\t    YOUR HAND" << endl;
		printHand(hands[0]);

		// Free memory
		memFree_ListOf2D(hands, numOfPlayers, 5);
		system("pause");
	}
	cout << "\n\t\t\t\t\t===== T H E   G A M E   E N D S =====\n" << endl;
	system("pause");
}

// GAME FOR DEALER
void dealerSide() {
	system("cls");

	// Input data
	int numOfGames, numOfPlayers = 1;
	inputNumOfGames(numOfGames);

	// Loop the game
	for (int i = 1; i <= numOfGames; i++) {
		system("cls");

		// Shuffle and print cards
		int deck[SUITS][FACES] = { 0 };
		shuffleCards(deck);
		printCardsShuffling(deck);

		// Dealing for hand
		int*** hands = dealingForHands(deck, numOfPlayers);

		// Print the DEALER's hand
		cout << "ROUND " << i << endl;
		cout << "\n\t\t\t\t\t\t       DEALER'S HAND" << endl;
		printHand(hands[0]);

		// Drawing new cards
		drawingNewCards(deck, hands[0]);

		// Print the DEALER's hand
		cout << "\n\t\t\t\t\t\t   DEALER'S HAND (AFTER)" << endl;
		printHand(hands[0]);

		// Free memory
		memFree_ListOf2D(hands, numOfPlayers, 5);
		system("pause");
	}
	cout << "\n\t\t\t\t\t===== T H E   G A M E   E N D S =====\n" << endl;
	system("pause");
}

// DIFFERENT LEVELS 
void easyLevel() { // Dealer Can't Draw (Same As main04)
	system("cls");

	// Input data
	int numOfGames, numOfPlayers = 2;
	inputNumOfGames(numOfGames);

	// Loop the game
	for (int i = 1; i <= numOfGames; i++) {
		system("cls");

		// Shuffle cards
		int deck[SUITS][FACES] = { 0 };
		shuffleCards(deck);

		// Dealing for hand
		int*** hands = dealingForHands(deck, numOfPlayers);

		cout << "ROUND " << i << endl;
		Sleep(500);

		// Print the PLAYER's hand
		cout << "\nYOUR TURN" << endl;
		cout << "\t\t\t\t\t\t\t YOUR HAND" << endl;
		printHand(hands[1]);
		Sleep(500);

		// Ask the PLAYER to draw cards
		bool playerAns;
		askPlayerToDraw(deck, hands[1], playerAns);

		// Check to print the PLAYER's hand
		if (playerAns == 1) {
			cout << "\t\t\t\t\t\t     YOUR HAND (AFTER)" << endl;
			printHand(hands[1]);
		}
		Sleep(500);

		cout << "DEALER'S TURN" << endl;
		Sleep(1000);

		// Print the DEALER's hand
		cout << "\t\t\t\t\t\t       DEALER'S HAND" << endl;
		printHand(hands[0]);
		Sleep(1000);

		// Compare and print the result
		printResult(hands[0], hands[1]);

		// Free memory
		memFree_ListOf2D(hands, numOfPlayers, 5);
		system("pause");
	}
	cout << "\n\t\t\t\t\t===== T H E   G A M E   E N D S =====\n" << endl;
	system("pause");
}

void normalLevel() { // Both Can Draw
	system("cls");

	// Input data
	int numOfGames, numOfPlayers = 2;
	inputNumOfGames(numOfGames);

	// Loop the game
	for (int i = 1; i <= numOfGames; i++) {
		system("cls");

		// Shuflle cards
		int deck[SUITS][FACES] = { 0 };
		shuffleCards(deck);

		// Dealing for hand
		int*** hands = dealingForHands(deck, numOfPlayers);

		cout << "ROUND " << i << endl;
		Sleep(500);

		// Print the PLAYER's hand
		cout << "\nYOUR TURN" << endl;
		cout << "\t\t\t\t\t\t\t YOUR HAND" << endl;
		printHand(hands[1]);
		Sleep(500);

		// Ask the PLAYER to draw cards
		bool playerAns;
		askPlayerToDraw(deck, hands[1], playerAns);

		// Check to print the PLAYER's hand
		if (playerAns == 1) {
			cout << "\t\t\t\t\t\t     YOUR HAND (AFTER)" << endl;
			printHand(hands[1]);
		}
		Sleep(500);

		cout << "DEALER'S TURN" << endl;
		Sleep(1000);

		// Ask the DEALER to draw cards
		bool dealerAns;
		askDealerToDraw(deck, hands[0], dealerAns);

		// Check to print the DEALER's hand
		cout << "\n\t\t\t\t\t\t       DEALER'S HAND" << endl;
		printHand(hands[0]);
		Sleep(1000);

		// Compare and print the result
		printResult(hands[0], hands[1]);

		// Free memory
		memFree_ListOf2D(hands, numOfPlayers, 5);
		system("pause");
	}
	cout << "\n\t\t\t\t\t===== T H E   G A M E   E N D S =====\n" << endl;
	system("pause");
}

void difficultLevel() { // Player Can't Draw
	system("cls");

	// Input data
	int numOfGames, numOfPlayers = 2;
	inputNumOfGames(numOfGames);

	// Loop the game
	for (int i = 1; i <= numOfGames; i++) {
		system("cls");

		// Shuffle cards
		int deck[SUITS][FACES] = { 0 };
		shuffleCards(deck);

		// Dealing for hand
		int*** hands = dealingForHands(deck, numOfPlayers);

		cout << "ROUND " << i << endl;
		Sleep(500);

		// Print the PLAYER's hand
		cout << "\nYOUR TURN" << endl;
		cout << "\t\t\t\t\t\t\t YOUR HAND" << endl;
		printHand(hands[1]);
		Sleep(500);

		cout << "DEALER'S TURN" << endl;
		Sleep(1000);

		// Ask the DEALER to draw cards
		bool dealerAns;
		askDealerToDraw(deck, hands[0], dealerAns);

		// Check to print the DEALER's hand
		cout << "\n\t\t\t\t\t\t       DEALER'S HAND" << endl;
		printHand(hands[0]);
		Sleep(1000);

		// Compare and print the result
		printResult(hands[0], hands[1]);

		// Free memory
		memFree_ListOf2D(hands, numOfPlayers, SUITS);
		system("pause");
	}
	cout << "\n\t\t\t\t\t===== T H E   G A M E   E N D S =====\n" << endl;
	system("pause");
}

void moreLevels() {
	system("cls");
	ShowCur(0);
	int Set[7];
	Set[0] = 14;
	for (int i = 1; i <= 3; i++) {
		Set[i] = 0;
	}
	int counter = 1;
	char key;
	pokerArt();
	while (true) {
		GoTo(54, 13);
		SetColor(3, Set[0]);
		cout << "EASY" << endl;

		GoTo(53, 15);
		SetColor(3, Set[1]);
		cout << "NORMAL" << endl;

		GoTo(52, 17);
		SetColor(3, Set[2]);
		cout << "DIFFICULT" << endl;

		GoTo(54, 21);
		SetColor(3, Set[3]);
		cout << "BACK" << endl;

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 4)) {
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 3)) {
			counter++;
		}
		if (key == '\r') {
			if (counter == 1) {
				system("color 3F");
				easyLevel();

				system("cls");
				break;
			}
			if (counter == 2) {
				system("color 3F");
				normalLevel();

				system("cls");
				break;
			}
			if (counter == 3) {
				system("color 3F");
				difficultLevel();

				system("cls");
				break;
			}
			if (counter == 4) {
				break;
			}
		}
		for (int i = 0; i <= 3; i++) {
			Set[i] = 0;
		}
		Set[counter - 1] = 14;

	}
}

// MENU
void playWithoutDealer() {
	system("cls");
	ShowCur(0);
	int Set[7];
	Set[0] = 14;
	for (int i = 1; i <= 3; i++) {
		Set[i] = 0;
	}
	int counter = 1;
	char key;
	pokerArt();
	while (true) {
		GoTo(50, 13);
		SetColor(3, Set[0]);
		cout << "SINGLE-PLAYER" << endl;

		GoTo(51, 15);
		SetColor(3, Set[1]);
		cout << "MULTIPLAYER" << endl;

		GoTo(52, 17);
		SetColor(3, Set[2]);
		cout << "TEST HAND" << endl;

		GoTo(54, 21);
		SetColor(3, Set[3]);
		cout << "BACK" << endl;

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 4)) {
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 3)) {
			counter++;
		}
		if (key == '\r') {
			if (counter == 1) {
				system("color 3F");
				singlePlayer();

				system("cls");
				break;
			}
			if (counter == 2) {
				system("color 3F");
				Multiplayer();

				system("cls");
				break;
			}
			if (counter == 3) {
				system("color 3F");
				testHand();

				system("cls");
				break;
			}
			if (counter == 4) {
				break;
			}
		}
		for (int i = 0; i <= 3; i++) {
			Set[i] = 0;
		}
		Set[counter - 1] = 14;

	}
}

void playWithDealer() {
	system("cls");
	ShowCur(0);
	int Set[7];
	Set[0] = 14;
	for (int i = 1; i <= 2; i++) {
		Set[i] = 0;
	}
	int counter = 1;
	char key;
	pokerArt();
	while (true) {
		GoTo(51, 13);
		SetColor(3, Set[0]);
		cout << "DEALER SIDE" << endl;

		GoTo(51, 15);
		SetColor(3, Set[1]);
		cout << "MORE LEVELS" << endl;

		GoTo(54, 19);
		SetColor(3, Set[2]);
		cout << "BACK" << endl;

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 3)) {
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 2)) {
			counter++;
		}
		if (key == '\r') {
			if (counter == 1) {
				system("color 3F");
				dealerSide();

				system("cls");
				break;
			}
			if (counter == 2) {
				system("color 3F");
				moreLevels();

				system("cls");
				pokerArt();
			}
			if (counter == 3) {
				break;
			}
		}
		for (int i = 0; i <= 2; i++) {
			Set[i] = 0;
		}
		Set[counter - 1] = 14;
	}
}

void menu() {
	ShowCur(0);
	system("color 3F");
	int Set[7];
	Set[0] = 14;
	for (int i = 1; i <= 2; i++) {
		Set[i] = 0;
	}
	int counter = 1;
	char key;
	pokerArt();
	while (true) {
		GoTo(54, 13);
		SetColor(3, Set[0]);
		cout << "PLAY" << endl;

		GoTo(50, 15);
		SetColor(3, Set[1]);
		cout << "PLAY WITH DEALER" << endl;

		GoTo(54, 19);
		SetColor(3, Set[2]);
		cout << "EXIT" << endl;

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 3)) {
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 2)) {
			counter++;
		}
		if (key == '\r') {
			if (counter == 1) {
				system("color 3F");
				playWithoutDealer();

				system("cls");
				pokerArt();
			}
			if (counter == 2) {
				system("color 3F");
				playWithDealer();

				system("cls");
				pokerArt();
			}
			if (counter == 3) {
				system("cls");
				endArt();
				break;
			}
		}
		for (int i = 0; i <= 2; i++) {
			Set[i] = 0;
		}
		Set[counter - 1] = 14;

	}
}