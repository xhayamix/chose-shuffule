#include "Hindu.hpp"


Hindu::Hindu(const InitData& init) : IScene(init){
	for (int i = 1; i <= 10; i++) {
		for (int j = 0; j < 3; j++) {
			cards.push_back(PlayingCard::Card(PlayingCard::Suit::Spade, i));
		}
	}
	for (int i = 1; i <= 10; i++) {
		for (int j = 0; j < 3; j++) {
			cards.push_back(PlayingCard::Card(PlayingCard::Suit::Diamond, i));
		}
	}
	const String str = U"0123456789";
	for (int i = 0; i < 10; i++) {
		buttons.emplace_back(String(1, str[i]), i, Rect(43*(i+1)+i*80, 550, 80, 60));
	}
	

}

void Hindu::update(){
	ClearPrint();

	Print << Cursor::Pos(); // 現在のマウスカーソル座標を表示

	Print << U"X: " << Cursor::Pos().x; // X 座標だけを表示

	Print << U"Y: " << Cursor::Pos().y; // Y 座標だけを表示

}

void Hindu::draw() const{
	for (int i = 0; i < 60; i++) {
		const Vec2 center(15 + i % 15 * (pack.width() + 15), 15 + (i / 15) * (pack.height() + 15));
		pack(cards[i]).draw(center);
	}
	
	for (const auto& button : buttons){
		button.draw();
		FontAsset(U"Number")(button.label()).drawAt(button.rect().center(), ColorF(0.2, 0.4, 0.6));
	}
}

void Hindu::shuffle(int roop) {
	int count;
	int now;
	std::normal_distribution<> dist(10, 5/3);
	Array<PlayingCard::Card> afterCards = cards.slice(0);
	for (int i = 0; i < roop; i++) {
		cards = afterCards.slice(0);
		count = cards.size();
		now = 0;
		while (count > 0) {
			int stack = (int)dist(engine);
			for (int i = stack; i > 0; i--) {
				if (now + i - 1 >= afterCards.size()) {
					continue;
				}
				afterCards[count - 1] = cards[now + i - 1];
				count--;
				if (count <= 0) {
					break;
				}
			}
			now += stack;
		}
	}

}