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
	Array<RectF> rects;
	Array<InputNumberButton> buttons;
	String text;
	int savei;
	Array<Vec2> cardData;

public:

	SetGame(const InitData& init);
	void update() override;
	void draw() const override;
	void setCards();

};