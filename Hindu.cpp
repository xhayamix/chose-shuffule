#include "Hindu.hpp"


Hindu::Hindu(const InitData& init) : IScene(init){
	setCards();
	const String str = U"0123456789";
	for (int i = 0; i < 10; i++) {
		buttons.emplace_back(String(1, str[i]), i, Rect(43*(i+1)+i*80, 550, 80, 60));
	}

	buttons.emplace_back(U"10", 10, Rect(43 * (4 + 1) + 4 * 80 + 160 + 43 + 5, 652, 80, 60));//43はボタンの間の長さ
	buttons.emplace_back(U"OK", 11, Rect(43 * (4 + 1) + 4 * 80 + 240 + 43 + 10, 652, 80, 60));
	buttons.emplace_back(U"reset", 12, Rect(43 * (4 + 1) + 4 * 80 + 320 + 43 + 15, 652, 180, 60));

	for (int i = 0; i < 60; i++) {
		RectF rect(15 + i % 15 * (pack.width() + 15), 15 + (i / 15) * (pack.height() + 15), 69, 111.64435);
		rects.push_back(rect);
	}

}

void Hindu::update(){
	for (auto& button : buttons){//数字ボタンの判定
		button.update();
		if (button.rect().leftClicked()) {
			int num = button.value;
			if (num == 11) {
				if (text.size() > 0) {
					cards = shuffle(cards, Parse<int>(text));
					
				}
				break;
			}
			if (num == 12) {
				setCards();
				text.erase(0, text.size());
				break;
			}
			if (num == 10) {
				if (text) {
					text.pop_back();
				} 
			} else if (text.size() < 3) {
				if (num != 0 || text.size() != 0) {
					String s = Format(num);
					text.insert(text.size(), s);
				}
				
			}
		}
	}

	for (int i = 0; i < rects.size(); i++) {//カード入れ替え
		if (rects[i].leftClicked()) {
			savei = i;
			break;
		} else if (rects[i].mouseOver() && MouseL.up()) {
			PlayingCard::Card card = cards[i];
			cards[i] = cards[savei];
			cards[savei] = card;
			break;
		}
	}

	if (MouseR.pressed()) {//titleに戻る
		changeScene(State::Title, 0.3s);
	}
}

void Hindu::draw() const{
	for (int i = 0; i < 60; i++) {//カードの描画
		const Vec2 center(15 + i % 15 * (pack.width() + 15), 15 + (i / 15) * (pack.height() + 15));
		pack(cards[i]).draw(center);
	}
	
	for (const auto& button : buttons){//ボタンの描画
		button.draw();
		if (button.value == 10) {
			Triangle(button.rect().center(), 48, -90_deg).movedBy(2, 0).draw(ColorF(0.2, 0.4, 0.6));
			Shape2D::Cross(9.5, 3.6, button.rect().center().movedBy(2, 0)).draw(ColorF(0.9, 0.92, 0.94));
		} else {
			FontAsset(U"Number")(button.label()).drawAt(button.rect().center(), ColorF(0.2, 0.4, 0.6));
		}
		
	}

	Rect displayRect(43 * (4 + 1) + 4 * 80, 652, 203, 60);//数字の表示
	displayRect.stretched(-1).draw();
	FontAsset(U"Number")(text).draw(Arg::rightCenter = displayRect.rightCenter().movedBy(-15, 0), ColorF(0.25));

}

Array<PlayingCard::Card> Hindu::shuffle(Array<PlayingCard::Card> cards, int roop) {//シャッフル
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
	return afterCards;
}

void Hindu::setCards() {//カードの初期セット
	cards.clear();
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

}