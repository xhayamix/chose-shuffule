
# include <Siv3D.hpp> // OpenSiv3D v0.4.3
#include <HamFramework.hpp>
#include "Common.hpp"
#include "Title.hpp"
#include "Hindu.hpp"


void Main()
{
    Scene::SetBackground(ColorF(0.8, 0.9, 1.0));
    Window::Resize(1280, 720);
	MyApp manager;
	manager
		.add<Title>(State::Title)
		.add<Hindu>(State::Hindu)
		.init(State::Title);
	FontAsset::Register(U"Title", 70, Typeface::Regular);
	FontAsset::Register(U"Menu", 30, Typeface::Regular);

	while (System::Update())
	{
		if (!manager.update())
		{
			break;
		}
	}
}


