#pragma once
#include <Siv3D.hpp>
enum class State{
	Title,
	Hindu,
	Farrow,
	SetGame,
	Memorygame
};

struct CommonData{
	Array<PlayingCard::Card> cards;
	int roop = 0;
	int shuffleKind = 0;

};

using MyApp = SceneManager<State, CommonData>;