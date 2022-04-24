
# include <Siv3D.hpp> // OpenSiv3D v0.4.3
#include "Common.hpp"
#include "Title.hpp"
#include "SetGame.hpp"
#include "MemoryGame.hpp"
#include "AgentSetGame.hpp"
#include "AgentMemoryGame.hpp"

void Main() {
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));
	Window::Resize(1280, 720);
	MyApp manager;
	manager
		.add<Title>(State::Title)
		.add<SetGame>(State::SetGame)
		.add<MemoryGame>(State::MemoryGame)
		.add<AgentSetGame>(State::AgentSetGame)
		.add<AgentMemoryGame>(State::AgentMemoryGame)
		.init(State::Title);
	FontAsset::Register(U"Title", 70, Typeface::Regular);
	FontAsset::Register(U"Menu", 30, Typeface::Regular);
	FontAsset::Register(U"Number", 40, Typeface::Bold);

	while (System::Update()) {
		if (!manager.update()) {
			break;
		}
	}
}


