
# include <Siv3D.hpp> // OpenSiv3D v0.4.3
#include <HamFramework.hpp>
#include "Common.hpp"
#include "Title.hpp"
#include "Hindu.hpp"
#include "Farrow.hpp"
#include "SetGame.hpp"
#include "Memorygame.hpp"
#include "Plot.hpp"


void Main(){
    Scene::SetBackground(ColorF(0.8, 0.9, 1.0));
    Window::Resize(1280, 720);
	MyApp manager;
	manager
		.add<Title>(State::Title)
		.add<Hindu>(State::Hindu)
		.add<Farrow>(State::Farrow)
		.add<SetGame>(State::SetGame)
		.add<Memorygame>(State::Memorygame)
		.add<Plot>(State::Plot)
		.init(State::Title);
	FontAsset::Register(U"Title", 70, Typeface::Regular);
	FontAsset::Register(U"Menu", 30, Typeface::Regular);
	FontAsset::Register(U"Number", 40, Typeface::Bold);

	while (System::Update()){
		if (!manager.update()){
			break;
		}
	}
}


