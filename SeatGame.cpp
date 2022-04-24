#include "SetGame.hpp"

SetGame::SetGame(const InitData& init) : IScene(init) {
	cards = new CardDeck();
	plotCards = new CardDeck();

	const String str = U"0123456789";
	for (int i = 0; i < 10; i++) {
		buttons.emplace_back(String(1, str[i]), i, Rect(43 * (i + 1) + i * 80, 550, 80, 60));
	}

	buttons.emplace_back(U"10", 10, Rect(43 * (4 + 1) + 4 * 80 + 160 + 43 + 5, 652, 80, 60)); // 43はボタンの間の長さ
	buttons.emplace_back(U"start", 11, Rect(43 * (4 + 1) + 4 * 80 + 240 + 43 + 10, 652, 180, 60));
	buttons.emplace_back(U"reset", 12, Rect(43 * (4 + 1) + 4 * 80 + 420 + 43 + 15, 652, 180, 60));

	for (int i = 0; i < 60; i++) {
		RectF rect(15 + i % 15 * (cards->pack.width() + 15), 15 + (i / 15) * (cards->pack.height() + 15), 69, 111.64435);
		backrects.push_back(rect);
	}
}

SetGame::~SetGame()
{
}

void SetGame::update() {
	SimpleGUI::RadioButtons(shuffleNum, { U"Hindu Shuffle", U"Farrow Shuffle" }, Vec2(100, 630));
	
	if (shuffleNum == 0) {
		CardShuffle* shuffle = new HinduShuffle();
		cards->setShuffle(shuffle);
		plotCards->setShuffle(shuffle);
	} else {
		CardShuffle* shuffle = new FarrowShuffle();
		cards->setShuffle(shuffle);
		plotCards->setShuffle(shuffle);
	}
	for (auto& button : buttons) {//数字ボタンの判定
		button.update();
		if (button.rect().leftClicked()) {
			int num = button.value;
			if (num == 11 && numberText.size() > 0) {
				getData().roop = Parse<int>(numberText);
				//getData().roop = 0;
				getData().shuffleKind = shuffleNum;
				getData().procards = cards;

				cards->doShuffle(Parse<int>(numberText));
				//cards->doShuffle(0);
				getData().cards = cards;
				changeScene(State::AgentMemoryGame, 0.3s);
				break;
			} else if (num == 12) {//カードのリセット処理
				delete(cards);
				cards = new CardDeck();
				delete(plotCards);
				plotCards = new CardDeck();
				numberText.erase(0, numberText.size());
				break;
			} else if (num == 10 && numberText) {//バックスペースキー
				numberText.pop_back();
				plotCards->setCards(cards->getCards());
				plotCards->setIntCards(cards->getIntCards());
				if (numberText.size() != 0) {
					plotCards->doShuffle(Parse<int>(numberText));
				}
			} else if (numberText.size() < 3) {//数字キーを押されたとき
				if (num != 0 || numberText.size() != 0) {//数字をテキストエリアに数字を入れる処理
					String s = Format(num);
					numberText.insert(numberText.size(), s);
				}
				plotCards->setCards(cards->getCards());
				plotCards->setIntCards(cards->getIntCards());
				plotCards->doShuffle(Parse<int>(numberText));

			}
		}
	}

	for (int i = 0; i < backrects.size(); i++) {//カード入れ替え
		if (backrects[i].leftClicked()) {
			moveCardsIndex = i;
			break;
		} else if (backrects[i].mouseOver() && MouseL.up()) {
			PlayingCard::Card card = cards->getCard(i);
			cards->setCard(i, cards->getCard(moveCardsIndex));
			cards->setCard(moveCardsIndex, card);

			int intcard = cards->getIntCard(i);
			cards->setIntCard(i, cards->getIntCard(moveCardsIndex));
			cards->setIntCard(moveCardsIndex, intcard);
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
		hintDraw();
	} else {
		cardsDraw();
	}
	if (m_plotButton.mouseOver()) {//plotボタン
		plotDraw();
	}
	buttonDraw();
	numberDraw();
	
}

void SetGame::cardsDraw() const {//カードの描画
	for (int i = 0; i < 60; i++) {
		const Vec2 center(15 + i % 15 * (cards->pack.width() + 15), 15 + (i / 15) * (cards->pack.height() + 15));
		cards->pack(cards->getCard(i)).draw(center);
		//plotCards->pack(plotCards->getCard(i)).draw(center);
	}
}

void SetGame::hintDraw() const {
	for (int i = 0; i < 60; i++) {
		const Vec2 center(15 + i % 15 * (cards->pack.width() + 15), 15 + (i / 15) * (cards->pack.height() + 15));
		plotCards->pack(plotCards->getCard(i)).draw(center);
	}

}

void SetGame::plotDraw() const {
	Rect(240, 10, 800, 500).draw(ColorF(0.8, 0.9, 1.0));//左下(240,510)
	for (int i = 0; i < plotCards->getIntCards().size(); i++) {
		Circle(240 + ((i + 1) * distanceXPoint), 510 - ((plotCards->getIntCard(i) + 1) * distanceYPoint), 6).draw(Palette::Black);

	}
}

void SetGame::buttonDraw() const {
	for (const auto& button : buttons) {
		button.draw();
		if (button.value == 10) {
			Triangle(button.rect().center(), 48, -90_deg).movedBy(2, 0).draw(ColorF(0.2, 0.4, 0.6));
			Shape2D::Cross(9.5, 3.6, button.rect().center().movedBy(2, 0)).draw(ColorF(0.9, 0.92, 0.94));
		} else {
			FontAsset(U"Number")(button.label()).drawAt(button.rect().center(), ColorF(0.2, 0.4, 0.6));
		}

	}

	m_hintButton.draw(ColorF(1.0, m_hintTransition.value())).drawFrame(2);
	FontAsset(U"Menu")(U"hint").drawAt(m_hintButton.center(), ColorF(0.25));
	m_plotButton.draw(ColorF(1.0, m_plotTransition.value())).drawFrame(2);
	FontAsset(U"Menu")(U"plot").drawAt(m_plotButton.center(), ColorF(0.25));
}

void SetGame::numberDraw() const {//数字の表示
	Rect displayRect(43 * (4 + 1) + 4 * 80, 652, 203, 60);
	displayRect.stretched(-1).draw();
	FontAsset(U"Number")(numberText).draw(Arg::rightCenter = displayRect.rightCenter().movedBy(-15, 0), ColorF(0.25));
}

