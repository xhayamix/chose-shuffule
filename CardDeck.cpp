#include "CardDeck.hpp"

CardDeck::CardDeck(){
	this->cards = initCards(this->cards);
	this->intcards = initCards(this->intcards);
}

CardDeck::~CardDeck(){
}

Array<PlayingCard::Card> CardDeck::initCards(Array<PlayingCard::Card> cards) {
	cards.clear();
	for (int i = 1; i <= 10; i++) {
		for (int j = 0; j < 3; j++) {
			cards.push_back(PlayingCard::Card(PlayingCard::Suit::Spade, i));
		}
	}
	for (int i = 1; i <= 10; i++) {
		for (int j = 0; j < 3; j++) {
			cards.push_back(PlayingCard::Card(PlayingCard::Suit::Diamond, i));
		}
	}

	return cards;

}
Array<int> CardDeck::initCards(Array<int> cards) {
	cards.clear();
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 3; j++) {
			cards.push_back(i);
		}
	}

	return cards;
}

void CardDeck::doShuffle(int roop) {
	this->cards = shuffle->shuffle(this->cards, roop);
	this->intcards = shuffle->shuffle(this->intcards, roop);
}





CardShuffle* CardDeck::getShuffle() {
	return this->shuffle;
}
void CardDeck::setShuffle(CardShuffle* shuffle) {
	this->shuffle = shuffle;
}


Array<PlayingCard::Card> CardDeck::getCards() {
	return this->cards;
}
void CardDeck::setCards(Array<PlayingCard::Card> cards) {
	this->cards = cards;
}


PlayingCard::Card CardDeck::getCard(int i) {
	return this->cards[i];
}
void CardDeck::setCard(int i, PlayingCard::Card card) {
	this->cards[i] = card;
}


Array<int> CardDeck::getIntCards() {
	return this->intcards;
}
void CardDeck::setIntCards(Array<int> cards) {
	this->intcards = cards;
}


int CardDeck::getIntCard(int i) {
	return this->intcards[i];
}
void CardDeck::setIntCard(int i, int card) {
	this->intcards[i] = card;
}