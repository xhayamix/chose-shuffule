#pragma once
#include "CardShuffle.hpp"
#include <random>

class HinduShuffle : public CardShuffle
{
public:
	HinduShuffle();
	Array<PlayingCard::Card> shuffle(Array<PlayingCard::Card> cards, int roop) override;
	Array<int> shuffle(Array<int> cards, int roop) override;
	
private:
	

	std::random_device seed_gen;
	std::default_random_engine engine = std::default_random_engine(seed_gen());

};

