#include "HinduShuffle.hpp"

HinduShuffle::HinduShuffle() : CardShuffle(){

}

Array<PlayingCard::Card> HinduShuffle::shuffle(Array<PlayingCard::Card> cards, int roop){
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

Array<int> HinduShuffle::shuffle(Array<int> cards, int roop) {
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