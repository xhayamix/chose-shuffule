#pragma once
#include "Common.hpp"
#include "InputNumberButton.hpp"
#include <HamFramework.hpp>
#include <random>
#include <fstream>

class Hindu : public MyApp::Scene
{
private:
	const PlayingCard::Pack pack = PlayingCard::Pack(69, Palette::Red);
	Array<PlayingCard::Card> cards;
	Array<InputNumberButton> buttons;

public:

	Hindu(const InitData& init);
	void update() override;
	void draw() const override;
	void shuffle(int roop);
	std::random_device seed_gen;
	std::default_random_engine engine = std::default_random_engine(seed_gen());


};