#include "AgentMemoryGame.hpp"
#include <stdio.h>
#include <stdlib.h>


AgentMemoryGame::AgentMemoryGame(const InitData& init) : IScene(init){
	cards = getData().cards;

	for (int i = 0; i < 60; i++) {
		RectF rect(15 + i % 15 * (cards->pack.width() + 15), 15 + (i / 15) * (cards->pack.height() + 15), 69, 111.64435);
		backrects.push_back(rect);
		cards->setCard(i, cards->getCard(i).flip());
	}

	for (int i = 0; i < 60; i++) {//配列初期化
		gameResult[i] = true;
		canSlelctCards.push_back(i);
		notOpenCards.push_back(i);
	}

	grid.resize(60, 20, 0);
	probabilityCal(getData().roop, getData().procards);
}

AgentMemoryGame::~AgentMemoryGame()
{
}

void AgentMemoryGame::update() {
	titleEffect.update();
	const Vec2 center(Scene::Center().x, 600);

	if (turn) {
		if (turnStart) {
			turnStart = false;
			titleEffect.add<TurnEffect2>(center, U"Your Trun", FontAsset(U"Title"));

		}

		if (cardCount == 3) {//count2の状態でdrowを呼び出すことで間違った場合でも2枚とも表示することができるようにしたが、ごり押し実装なのでもう少し改善したい
			cardCount++;
		}
		for (int i = 0; i < backrects.size(); i++) {//クリックしたカードを表に向ける
			if (backrects[i].leftClicked() && gameResult[i] && cardCount < 3) {
				saveOpenCard[cardCount] = i;
				gameResult[i] = false;
				cards->setCard(i, cards->getCard(i).flip());
				cardCount++;//開いたカードの枚数をカウントする
				break;
			}
		}

		if (cardCount == 4) {
			turn = false;
			static int num[3];
			for (int i = 0; i < 3; i++) {
				num[i] = saveOpenCard[i];
			}
			notOpenCards.remove_if([](int32 n) { return n == num[0]; });
			notOpenCards.remove_if([](int32 n) { return n == num[1]; });
			notOpenCards.remove_if([](int32 n) { return n == num[2]; });

			if (cards->getCard(saveOpenCard[0]).rank == cards->getCard(saveOpenCard[1]).rank && cards->getCard(saveOpenCard[0]).rank == cards->getCard(saveOpenCard[2]).rank) {//カードが一緒かどうか
				turn = true;

				static int num[3];
				for (int i = 0; i < 3; i++) {
					num[i] = saveOpenCard[i];
				}
				canSlelctCards.remove_if([](int32 n) { return n == num[0]; });
				canSlelctCards.remove_if([](int32 n) { return n == num[1]; });
				canSlelctCards.remove_if([](int32 n) { return n == num[2]; });

			} else {

				for (int i = 0; i < 3; i++) {
					gameResult[saveOpenCard[i]] = true;
				}
				System::Sleep(2000);//カード表示時間
				for (int i = 0; i < 3; i++) {
					cards->setCard(saveOpenCard[i], cards->getCard(saveOpenCard[i]).flip());
				}
				turnStart = true;

			}
			cardCount = 0;

		}

	} else {
		//Print << saveIndex;
		if (turnStart) {
			turnStart = false;
			titleEffect.add<TurnEffect2>(center, U"Enemy Trun", FontAsset(U"Title"));
		}
		if (cardCount == 3) {//count2の状態でdrowを呼び出すことで間違った場合でも2枚とも表示することができるようにしたが、ごり押し実装なのでもう少し改善したい
			cardCount++;
		}
		if (cardCount == 0) {
			srand(time(NULL));
			Print << (double)rand() / RAND_MAX + (60.0 - notOpenCards.size()) / 60.0;
			if ((double)rand() / RAND_MAX + (60.0 - notOpenCards.size()) / 60.0 > 0.95) {
			//Print << saveOpenCard[0];
				saveOpenCard[0] = canSlelctCards.choice();
				
				for (int i = 0; i < canSlelctCards.size(); i++) {
					if (cards->getCard(saveOpenCard[0]).rank == cards->getCard(canSlelctCards[i]).rank && saveOpenCard[0] != i) {
						saveOpenCard[1] = i;
						
					}
				}
				for (int i = 0; i < canSlelctCards.size(); i++) {
					if (cards->getCard(saveOpenCard[0]).rank == cards->getCard(canSlelctCards[i]).rank && saveOpenCard[0] != i && saveOpenCard[1] != i) {
						saveOpenCard[2] = i;
					}
				}

			}
			
			else {
				Array<int> saveindex;
				saveindex = canSlelctCards.choice(3);
				for (int i = 0; i < 3; i++) {
					saveOpenCard[i] = saveindex[i];
				}
			}
			
			cardCount = 3;
			//Print << notOpenCards.size();
			for (int i = 0; i < 3; i++) {
				cards->setCard(saveOpenCard[i], cards->getCard(saveOpenCard[i]).flip());
			}
		}
		
		if (cardCount == 4) {
			turn = true;
			static int num[3];
			for (int i = 0; i < 3; i++) {
				num[i] = saveOpenCard[i];
			}
			notOpenCards.remove_if([](int32 n) { return n == num[0]; });
			notOpenCards.remove_if([](int32 n) { return n == num[1]; });
			notOpenCards.remove_if([](int32 n) { return n == num[2]; });
			if (cards->getCard(saveOpenCard[0]).rank == cards->getCard(saveOpenCard[1]).rank && cards->getCard(saveOpenCard[0]).rank == cards->getCard(saveOpenCard[2]).rank) {
				turn = false;

				static int num[3];
				for (int i = 0; i < 3; i++) {
					num[i] = saveOpenCard[i];
				}
				canSlelctCards.remove_if([](int32 n) { return n == num[0]; });
				canSlelctCards.remove_if([](int32 n) { return n == num[1]; });
				canSlelctCards.remove_if([](int32 n) { return n == num[2]; });

			} else {
				for (int i = 0; i < 3; i++) {
					gameResult[saveOpenCard[i]] = true;
				}
				System::Sleep(2000);//カード表示時間
				for (int i = 0; i < 3; i++) {
					cards->setCard(saveOpenCard[i], cards->getCard(saveOpenCard[i]).flip());
				}
				turnStart = true;
				//Print << 1;
			}
			cardCount = 0;
		}

	}

}

void AgentMemoryGame::draw() const {
	cardsDraw();

}

void AgentMemoryGame::cardsDraw() const {//カードの描画
	for (int i = 0; i < 60; i++) {
		const Vec2 center(15 + i % 15 * (cards->pack.width() + 15), 15 + (i / 15) * (cards->pack.height() + 15));
		cards->pack(cards->getCard(i)).draw(center);
	}
}

void AgentMemoryGame::probabilityCal(int roop, CardDeck* cards) {
	CardDeck* copyCards = new CardDeck();
	if (getData().shuffleKind == 0) {
		CardShuffle* shuffle = new HinduShuffle();
		copyCards->setShuffle(shuffle);
	} else {
		CardShuffle* shuffle = new FarrowShuffle();
		copyCards->setShuffle(shuffle);
	}
	for (int i = 0; i < 1000; i++) {
		copyCards->setIntCards(cards->getIntCards());
		copyCards->doShuffle(roop);
		for (int j = 0; j < 60; j++) {
			
			this->grid[copyCards->getIntCard(j)][j]++;
		}
	}
	TextWriter writer(U"tutorial.txt");
	if(!writer) {
		throw Error(U"Failed to open `tutorial.txt`");
	}
	for(int i = 0; i < 20; i++) {
		for (int j = 0; j < 60; j++) {
			writer.write(grid[i][j]);
			writer.write(U',');
		}
		writer.writeln(U',');
	}
	writer.close();
	//Print << grid;
}

TurnEffect2::TurnEffect2(const Vec2& start, String text, const Font& font)
		: m_start(start)
		, m_text(text)
		, m_font(font) {
	}

	bool TurnEffect2::update(double t){
		const HSV color(0, 100, 100, 1.0 - (t * 0.5));

		m_font(m_text).drawAt(m_start, color);

		// 0.5 秒以上経過で消滅
		return t < 2;
	}