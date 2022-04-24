#pragma once
#include "Common.hpp"

class AgentMemoryGame : public MyApp::Scene {
public:
	AgentMemoryGame(const InitData& init);
	~AgentMemoryGame();

	void update() override;
	void draw() const override;
	void cardsDraw() const;

	void probabilityCal(int roop, CardDeck* cards);

private:
	CardDeck* cards;

	bool gameResult[60];
	Array<RectF> backrects;
	Effect titleEffect;

	Grid<int> grid;
	Array<int> canSlelctCards;
	Array<int> notOpenCards;
	int cardCount = 0;
	int saveOpenCard[3];
	bool turn = true;
	bool turnStart = true;
	int firstdorwcard;
	int max;

	
};

struct TurnEffect2 : IEffect {
	Vec2 m_start;

	String m_text;

	Font m_font;



	TurnEffect2(const Vec2& start, String text, const Font& font);

	bool update(double t) override;
};
