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
	Array<Vec2> cards;
	int roop = 0;
	int shuffleKind = 0;

};

using MyApp = SceneManager<State, CommonData>;