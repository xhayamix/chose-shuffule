#include "FarrowShuffle.hpp"

FarrowShuffle::FarrowShuffle() : CardShuffle() {

}

Array<PlayingCard::Card> FarrowShuffle::shuffle(Array<PlayingCard::Card> cards, int roop) {
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

Array<int> FarrowShuffle::shuffle(Array<int> cards, int roop) {
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