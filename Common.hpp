#pragma once
#include <Siv3D.hpp>
enum class State{
	Title,
	Hindu,
	Farrow,
	SetGame
};

struct CommonData{

};

using MyApp = SceneManager<State, CommonData>;