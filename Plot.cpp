#include "Plot.hpp"

Plot::Plot(const InitData& init) : IScene(init) {
	setCards();
	const String str = U"0123456789";
	for (int i = 0; i < 10; i++) {
		buttons.emplace_back(String(1, str[i]), i, Rect(43 * (i + 1) + i * 80, 550, 80, 60));
	}

	buttons.emplace_back(U"10", 10, Rect(43 * (4 + 1) + 4 * 80 + 160 + 43 + 5, 652, 80, 60)); // 43はボタンの間の長さ
	buttons.emplace_back(U"OK", 11, Rect(43 * (4 + 1) + 4 * 80 + 240 + 43 + 10, 652, 80, 60));
	buttons.emplace_back(U"reset", 12, Rect(43 * (4 + 1) + 4 * 80 + 320 + 43 + 15, 652, 180, 60));

}

void Plot::update() {
	SimpleGUI::RadioButtons(index0, { U"Hindu Shuffle", U"Farrow Shuffle"}, Vec2(100, 630));
	for (auto& button : buttons) {//数字ボタンの判定
		button.update();
		if (button.rect().leftClicked()) {
			int num = button.value;
			if (num == 11) {
				if (text.size() > 0) {
					setCards();
					if (index0 == 0) {//シャッフルの種類選択
						cards = hinduShuffle(cards, Parse<int>(text));
					}
					else {
						cards = farrowShuffle(cards, Parse<int>(text));
					}

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
			}
			else if (text.size() < 3) {
				if (num != 0 || text.size() != 0) {
					String s = Format(num);
					text.insert(text.size(), s);
				}

			}
		}
	}

	if (MouseR.pressed()) {//titleに戻る
		changeScene(State::Title, 0.3s);
	}

}

void Plot::draw() const {

	Rect(240, 10, 800, 500).draw();//左下(240,510)

	for (int i = 0; i < cards.size(); i++) {
		Circle(240 + ((i + 1) * distanceXPoint), 510 - ((cards[i] + 1) * distanceYPoint), 6).draw(Palette::Black);

	}

	for (const auto& button : buttons) {//ボタンの描画
		button.draw();
		if (button.value == 10) {
			Triangle(button.rect().center(), 48, -90_deg).movedBy(2, 0).draw(ColorF(0.2, 0.4, 0.6));
			Shape2D::Cross(9.5, 3.6, button.rect().center().movedBy(2, 0)).draw(ColorF(0.9, 0.92, 0.94));
		}
		else {
			FontAsset(U"Number")(button.label()).drawAt(button.rect().center(), ColorF(0.2, 0.4, 0.6));
		}

	}

	Rect displayRect(43 * (4 + 1) + 4 * 80, 652, 203, 60);//数字の表示
	displayRect.stretched(-1).draw();
	FontAsset(U"Number")(text).draw(Arg::rightCenter = displayRect.rightCenter().movedBy(-15, 0), ColorF(0.25));

}

void Plot::setCards() {//カードの初期セット
	cards.clear();
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 3; j++) {
			cards.push_back(i);
		}
	}

}

Array<int> Plot::hinduShuffle(Array<int> cards, int roop) {
	int count;
	int now;
	std::normal_distribution<> dist(10, 5 / 3);
	Array<int> afterCards = cards.slice(0);
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
Array<int> Plot::farrowShuffle(Array<int> cards, int roop) {
	int acount;
	int bcount;
	int now;
	Array<int> afterCards = cards.slice(0);
	std::binomial_distribution<> dist(cards.size(), 0.5);
	for (int j = 0; j < roop; j++) {
		now = cards.size();
		int div = dist(engine);
		Array<int> a;
		Array<int> b;
		for (int i = 0; i < div; i++) {
			a.push_back(afterCards[i]);
		}
		for (int i = 0; i < cards.size() - div; i++) {
			b.push_back(afterCards[i + div]);
		}
		acount = div;
		bcount = cards.size() - div;

		while (acount > 0 || bcount > 0) {
			if (acount == 0) {
				for (int i = 0; i < bcount; i++) {
					afterCards[i] = b[i];
				}
				break;
			}
			if (bcount == 0) {
				for (int i = 0; i < acount; i++) {
					afterCards[i] = a[i];
				}
				break;
			}
			double x = acount / (double)(acount + bcount);
			if (x >= Random(0.0, 1.0)) {
				afterCards[now - 1] = a[acount - 1];
				now--;
				acount--;
			}
			else {
				afterCards[now - 1] = b[bcount - 1];
				now--;
				bcount--;
			}
		}
	}
	return afterCards;

}