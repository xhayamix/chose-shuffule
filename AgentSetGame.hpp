#pragma once
#include "Common.hpp"
#include "InputNumberButton.hpp"
#include "CardDeck.hpp"
#include <HamFramework.hpp>

class AgentSetGame : public MyApp::Scene
{
public:
	AgentSetGame(const InitData& init);
	~AgentSetGame();

	void update() override;

	void draw() const override;
	void cardsDraw() const;
	void buttonDraw() const;
	void numberDraw() const;
	void plotDraw() const;
	void hintDraw() const;

private:
	CardDeck* cards;
	CardDeck* plotCards;

	String numberText;
	size_t shuffleNum = 0;
	int moveCardsIndex = 0;

	double distanceXPoint = 13.1;
	double distanceYPoint = 23.8;

	Array<RectF> backrects;
	Array<InputNumberButton> buttons;

	Rect m_hintButton = Rect(430, 652, 100, 60);
	Transition m_hintTransition = Transition(0.4s, 0.2s);
	Rect m_plotButton = Rect(325, 652, 100, 60);
	Transition m_plotTransition = Transition(0.4s, 0.2s);

};


