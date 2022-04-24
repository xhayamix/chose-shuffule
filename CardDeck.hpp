#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "FarrowShuffle.hpp"
#include "HinduShuffle.hpp"

class CardDeck
{
public:
	CardDeck();
	~CardDeck();

	Array<int> initCards(Array<int> cards);
	Array<PlayingCard::Card> initCards(Array<PlayingCard::Card> cards);

	void doShuffle(int roop = 0);

	CardShuffle* getShuffle();
	void setShuffle(CardShuffle* shuffle);

	Array<PlayingCard::Card> getCards();
	void setCards(Array<PlayingCard::Card> cards);

	PlayingCard::Card getCard(int i);
	void setCard(int i, PlayingCard::Card card);

	Array<int> getIntCards();
	void setIntCards(Array<int> cards);

	int getIntCard(int i);
	void setIntCard(int i, int card);

	const PlayingCard::Pack pack = PlayingCard::Pack(69, Palette::Red);
	

private:
	CardShuffle* shuffle;

	Array<PlayingCard::Card> cards;
	Array<int> intcards;

};

