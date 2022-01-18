#include "SetGame.hpp"


SetGame::SetGame(const InitData& init) : IScene(init) {
	this->cards = setCards(this->cards);
	this->plotcards = setCards(this->plotcards);
	setIntCards();

	const String str = U"0123456789";
	for (int i = 0; i < 10; i++) {
		buttons.emplace_back(String(1, str[i]), i, Rect(43 * (i + 1) + i * 80, 550, 80, 60));
	}

	buttons.emplace_back(U"10", 10, Rect(43 * (4 + 1) + 4 * 80 + 160 + 43 + 5, 652, 80, 60)); // 43はボタンの間の長さ
	buttons.emplace_back(U"start", 11, Rect(43 * (4 + 1) + 4 * 80 + 240 + 43 + 10, 652, 180, 60));
	buttons.emplace_back(U"reset", 12, Rect(43 * (4 + 1) + 4 * 80 + 420 + 43 + 15, 652, 180, 60));
	//buttons.emplace_back(U"hint", 13, Rect(350, 652, 180, 60));

	for (int i = 0; i < 60; i++) {
		RectF rect(15 + i % 15 * (pack.width() + 15), 15 + (i / 15) * (pack.height() + 15), 69, 111.64435);
		rects.push_back(rect);
	}

}

void SetGame::update() {
	SimpleGUI::RadioButtons(index0, { U"Hindu Shuffle", U"Farrow Shuffle"}, Vec2(100, 630));
	for (auto& button : buttons) {//数字ボタンの判定
		button.update();
		if (button.rect().leftClicked()) {
			int num = button.value;
			if (num == 11) {
				if (text.size() > 0) {
					for (int i = 0; i < 60; i++) {//カード配置の確認
						int j = 0;
						if (cards[i].isDiamond()) {
							j = 1;
						}
						cardData << Vec2(cards[i].rank, j);
					}
					getData().cards = cardData;
					getData().roop = Parse<int>(text);
					getData().shuffleKind = index0;
					changeScene(State::Memorygame, 0.3s);
				}
				break;
			}else if (num == 12) {//カードのリセット処理
				this->cards = setCards(this->cards);
				this->plotcards = setCards(this->plotcards);
				setIntCards();
				text.erase(0, text.size());
				break;
			}else if (num == 10) {//バックスペースキー
				if (text) {
					text.pop_back();
				}
				this->plotcards = this->cards.slice(0);
			}else if (text.size() < 3) {//数字キーを押されたとき
				if (num != 0 || text.size() != 0) {//数字をテキストエリアに数字を入れる処理
					String s = Format(num);
					text.insert(text.size(), s);
				}
				plotcardsShuffle();
				
			}
		}
	}

	for (int i = 0; i < rects.size(); i++) {//カード入れ替え
		if (rects[i].leftClicked()) {
			savei = i;
			break;
		}
		else if (rects[i].mouseOver() && MouseL.up()) {
			PlayingCard::Card card = cards[i];
			cards[i] = cards[savei];
			cards[savei] = card;
			break;
		}
	}
	

	if (MouseR.pressed()) {//titleに戻る
		changeScene(State::Title, 0.3s);
	}

	m_hintTransition.update(m_hintButton.mouseOver());
	m_plotTransition.update(m_plotButton.mouseOver());
	
	
}

void SetGame::draw() const {

	if (m_hintButton.mouseOver()) {//hintボタン
		plotDraw();
	} else {
		for (int i = 0; i < 60; i++) {//カードの描画
			const Vec2 center(15 + i % 15 * (pack.width() + 15), 15 + (i / 15) * (pack.height() + 15));
			pack(cards[i]).draw(center);
		}
	}
	if (m_plotButton.mouseOver()) {//plotボタン
		Rect(240, 10, 800, 500).draw(ColorF(0.8, 0.9, 1.0));//左下(240,510)
		for (int i = 0; i < intcards.size(); i++) {
			Circle(240 + ((i + 1) * distanceXPoint), 510 - ((intcards[i] + 1) * distanceYPoint), 6).draw(Palette::Black);

		}
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

	m_hintButton.draw(ColorF(1.0, m_hintTransition.value())).drawFrame(2);
	FontAsset(U"Menu")(U"hint").drawAt(m_hintButton.center(), ColorF(0.25));
	m_plotButton.draw(ColorF(1.0, m_plotTransition.value())).drawFrame(2);
	FontAsset(U"Menu")(U"plot").drawAt(m_plotButton.center(), ColorF(0.25));
	

}
void SetGame::plotDraw() const {
	for (int i = 0; i < 60; i++) {//カードの描画
		const Vec2 center(15 + i % 15 * (pack.width() + 15), 15 + (i / 15) * (pack.height() + 15));
		pack(plotcards[i]).draw(center);
	}

}


void SetGame::setIntCards() {//カードの初期セット
	intcards.clear();
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 3; j++) {
			intcards.push_back(i);
		}
	}

}

Array<PlayingCard::Card> SetGame::setCards(Array<PlayingCard::Card> cards) {//カードの初期セット
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

	return cards;
}


void SetGame::plotcardsShuffle()  {
	this->plotcards = this->cards.slice(0);
	setIntCards();
	if (index0 == 0) {
		this->plotcards = hinduShuffle(this->plotcards, Parse<int>(text));
		this->intcards = hinduShuffle(this->intcards, Parse<int>(text));
	} else {
		this->plotcards = farrowShuffle(this->plotcards, Parse<int>(text));
		this->intcards = farrowShuffle(this->intcards, Parse<int>(text));
	}
}

Array<PlayingCard::Card> SetGame::hinduShuffle(Array<PlayingCard::Card> cards, int roop) {
	int count;
	int now;
	std::normal_distribution<> dist(10, 5 / 3);
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
Array<PlayingCard::Card> SetGame::farrowShuffle(Array<PlayingCard::Card> cards, int roop) {
	int acount;
	int bcount;
	int now;
	Array<PlayingCard::Card> afterCards = cards.slice(0);
	std::binomial_distribution<> dist(cards.size(), 0.5);
	for (int j = 0; j < roop; j++) {
		now = cards.size();
		int div = dist(engine);
		Array<PlayingCard::Card> a;
		Array<PlayingCard::Card> b;
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

Array<int> SetGame::hinduShuffle(Array<int> cards, int roop) {
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
Array<int> SetGame::farrowShuffle(Array<int> cards, int roop) {
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