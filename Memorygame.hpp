#pragma once
#include "Common.hpp"
#include "InputNumberButton.hpp"
#include <HamFramework.hpp>
#include <random>
#include <fstream>
#include <stdio.h>

class Memorygame : public MyApp::Scene
{
private:
	const PlayingCard::Pack pack = PlayingCard::Pack(69, Palette::Red);
	Array<PlayingCard::Card> cards;
	Array<InputNumberButton> buttons;
	Array<RectF> rects;
	int roop;
	String text;
	int savei[3];
	bool gameResult[60];
	Array<Vec2> cardData;
	int count = 0;//開いているカードのカウント
	int time = 0;

public:

	Memorygame(const InitData& init);
	void update() override;
	void draw() const override;
	Array<PlayingCard::Card> hinduShuffle(Array<PlayingCard::Card> cards, int roop = 0);
	Array<PlayingCard::Card> farrowShuffle(Array<PlayingCard::Card> cards, int roop = 0);
	std::random_device seed_gen;
	std::default_random_engine engine = std::default_random_engine(seed_gen());
	//Array<PlayingCard::Card> setCards();
	void setCards();

};