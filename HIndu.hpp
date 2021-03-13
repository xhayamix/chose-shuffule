#pragma once
#include "Common.hpp"
#include "InputNumberButton.hpp"
#include <HamFramework.hpp>
#include <random>
#include <fstream>
#include <stdio.h>

class Hindu : public MyApp::Scene
{
private:
	const PlayingCard::Pack pack = PlayingCard::Pack(69, Palette::Red);
	Array<PlayingCard::Card> cards;
	Array<InputNumberButton> buttons;
	int roop;
	String text;

public:

	Hindu(const InitData& init);
	void update() override;
	void draw() const override;
	Array<PlayingCard::Card> shuffle(Array<PlayingCard::Card> cards, int roop = 0);
	std::random_device seed_gen;
	std::default_random_engine engine = std::default_random_engine(seed_gen());
	Array<PlayingCard::Card> setCards();

};