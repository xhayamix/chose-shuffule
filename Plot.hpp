#pragma once
#include "Common.hpp"
#include "InputNumberButton.hpp"
#include <HamFramework.hpp>

class Plot : public MyApp::Scene {
private:
	size_t index0 = 0;
	Array<InputNumberButton> buttons;
	int roop;
	String text;
	Array<int> cards;
	double distanceXPoint = 13.1;
	double distanceYPoint = 23.8;

public:
	Plot(const InitData& init);
	void update() override;
	void draw() const override;
	void setCards();
	Array<int> hinduShuffle(Array<int> cards, int roop = 0);
	Array<int> farrowShuffle(Array<int> cards, int roop = 0);
	std::random_device seed_gen;
	std::default_random_engine engine = std::default_random_engine(seed_gen());

};