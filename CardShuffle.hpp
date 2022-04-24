#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>

class CardShuffle
{
public:
	CardShuffle();
	virtual Array<PlayingCard::Card> shuffle(Array<PlayingCard::Card> cards, int roop);
	virtual Array<int> shuffle(Array<int> cards, int roop);

private:
	
};
