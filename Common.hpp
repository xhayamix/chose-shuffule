#pragma once
#include <Siv3D.hpp>
#include "CardDeck.hpp"

enum class State {
	Title,
	SetGame,
	MemoryGame,
	AgentSetGame,
	AgentMemoryGame
};

struct CommonData {
	CardDeck* cards;
	CardDeck* procards;
	int roop = 0;
	int shuffleKind = 0;

};

using MyApp = SceneManager<State, CommonData>;