#pragma once
#include "Common.hpp"
#include "InputNumberButton.hpp"
#include <HamFramework.hpp>
#include <stdio.h>

class SetGame : public MyApp::Scene
{
private:
	size_t index0 = 0;
	const PlayingCard::Pack pack = PlayingCard::Pack(69, Palette::Red);
	Array<PlayingCard::Card> cards;
	Array<PlayingCard::Card> plotcards;
	Array<RectF> rects;
	Array<InputNumberButton> buttons;
	String text;
	int savei;
	Array<Vec2> cardData;
	Array<int> intcards;
	double distanceXPoint = 13.1;
	double distanceYPoint = 23.8;

	Rect m_hintButton = Rect(430, 652, 100, 60);
	Transition m_hintTransition = Transition(0.4s, 0.2s);
	Rect m_plotButton = Rect(325, 652, 100, 60);
	Transition m_plotTransition = Transition(0.4s, 0.2s);

public:

	SetGame(const InitData& init);
	void update() override;
	void draw() const override;

	void plotDraw() const;
	void plotcardsShuffle();

	void setIntCards();
	Array<PlayingCard::Card> setCards(Array<PlayingCard::Card> plotcards);

	Array<PlayingCard::Card> hinduShuffle(Array<PlayingCard::Card> cards, int roop = 0);
	Array<PlayingCard::Card> farrowShuffle(Array<PlayingCard::Card> cards, int roop = 0);
	Array<int> hinduShuffle(Array<int> cards, int roop = 0);
	Array<int> farrowShuffle(Array<int> cards, int roop = 0);
	std::random_device seed_gen;
	std::default_random_engine engine = std::default_random_engine(seed_gen());

};