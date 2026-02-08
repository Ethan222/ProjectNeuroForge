#include<iostream>
#include <vector>
#include<chrono>
#include<string>
#include<algorithm>
#include<random>
#include<cctype>
using namespace std;
int main() {
	cout << "Trig Identities Practice\n\n";

	vector<pair<string, string>> cards = {
		{"cos^2(x) - sin^2(x)", "cos(2x)"},
		{"1 + tan^2(x)", "sec^2(x)"},
		{"1 + cot^2(x)", "csc^2(x)"},
		{"sin(2x)", "2sin(x)cos(x)"}
	};
	// add the reverse of each card above
	const size_t originalSize = cards.size();
	for (int i = 0; i < originalSize; ++i) {
		cards.push_back({ cards[i].second, cards[i].first });
	}

	// shuffle
	unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
	mt19937 rng(seed);
	shuffle(cards.begin(), cards.end(), rng);

	int correct = 0, asked = 0;
	for (const auto& card : cards) {
		++asked;
		cout << "Card " << asked << "/" << cards.size() << ": " << card.first << "\n";
		cout << "Your answer: ";
		string ans;
		if (!getline(cin, ans)) {
			cout << "Input error. Exiting.\n";
			return 1;
		}
		if (!ans.empty() && ans == card.second) {
			cout << "Correct!\n\n";
			++correct;
		}
		else {
			cout << "Incorrect. The correct answer is: " << card.second << "\n\n";
		}
	}

	cout << "Final score: " << correct << "/" << asked << "\n";
	system("pause");
	return 0;
}