#pragma once
#include <Siv3D.hpp>
enum class State
{
	Title
};

struct CommonData
{

};

using MyApp = SceneManager<State, CommonData>;