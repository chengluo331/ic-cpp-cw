#include <iostream>
#include <cmath>
#include <vector>
#include <iterator>
/*
*	Cheng Luo CID:01153695
*/
// Q2----------------------------------------------------------------------------------------

/*
*	display the the first n elements of a vector separated by space
*/
void display_vector(const std::vector<unsigned int>& v, size_t n){
	std::vector<unsigned int>::const_iterator begin = v.begin();
	copy(begin, begin + n, std::ostream_iterator<unsigned int>(std::cout, " "));
}

/*
*	display the content of a vector separated by space
*/
void display_vector(const std::vector<unsigned int>& v){
	copy(v.begin(), v.end(), std::ostream_iterator<unsigned int>(std::cout, " "));
}

/*
*	perform a m-shuffling on the cards held in a vector and return the reference of the cards
*	params:
*		m: the m of m-shuffle
*		cards: the stack of the cards
*/
const std::vector<unsigned int>& m_shuffle(unsigned int m, std::vector<unsigned int>& cards){
	// create the stack holding the first m cards
	std::vector<unsigned int>::const_iterator it1 = cards.begin();
	std::vector<unsigned int>::const_iterator it2 = cards.begin() + m;
	const std::vector<unsigned int> first_stack(it1, it2);
	// create the stack holding the second m cards
	it1 = it2;
	it2 = it2 + m;
	const std::vector<unsigned int> second_stack(it1, it2);

	// shuffle
	bool from_first_stack = false;
	size_t m2 = 2 * m;
	size_t j = 0;
	for (size_t i = 0; i < m2; i++)
	{
		if (from_first_stack) // pick a card from the first stack
		{
			cards[i] = first_stack[j];
			from_first_stack = false;
			j++; // increment counter when a cycle finish
		}
		else  { // pick a card from the second stack
			cards[i] = second_stack[j];
			from_first_stack = true;
		}
	}
	return cards;
}

/*
*	perform a complete shuffle on the cards held in a vector, record the top card of every m-shuffle, and return the reference of the cards
*	params:
*		k: the half size of the cards
*		cards: the stack of the cards
*		top_cards: record top card of every m-shuffle
*/
const std::vector<unsigned int>& complete_shuffle(size_t k, std::vector<unsigned int>& cards, std::vector<unsigned int>& top_cards){
	for (size_t i = 0; i < k; i++) // 1 to k m-shuffle
	{
		m_shuffle(i + 1, cards);
		top_cards.push_back(cards[0]);
	}
	for (size_t i = 0; i < k; i++) // k to 1 m-shuffle
	{
		m_shuffle(k - i, cards);
		top_cards.push_back(cards[0]);
	}
	return cards;
}

/*
*	adapted quicksort algorithm for card and its frequency
*	partition function used by quicksort. return the split index
*		frequency: the vector presenting the occurrences of cards
*		cards: the vector presenting all the cards corresponding its frequency
*		low: the first index of the vector
*		high: the last index of the vector
*/
int partition(std::vector<unsigned int>& frequency, std::vector<unsigned int>& cards, int low, int high){
	unsigned int pivot = frequency[low];
	int i = low + 1;
	int j = high;

	while (true){
		while (i <= j && (frequency[i] > pivot || (frequency[i] == pivot && cards[i] < cards[low]))){
			i++;
		}
		while (j >= i && (frequency[j] < pivot || (frequency[j] == pivot && cards[j] > cards[low]))){
			j--;
		}
		if (i < j){
			unsigned int tmp = frequency[i];
			frequency[i] = frequency[j];
			frequency[j] = tmp;
			tmp = cards[i];
			cards[i] = cards[j];
			cards[j] = tmp;
		}
		else{
			frequency[low] = frequency[j];
			frequency[j] = pivot;
			unsigned int tmp = cards[low];
			cards[low] = cards[j];
			cards[j] = tmp;
			return j;
		}
	}
}

/*
*	adapted quicksort algorithm for card and its frequency
*	sort frequency vector and permute cards vector according to its frequency
*	params:
*		frequency: the vector presenting the occurrences of cards
*		cards: the vector presenting all the cards corresponding its frequency
*		low: the first index of the vector
*		high: the last index of the vector
*/
void quicksort(std::vector<unsigned int>& frequency, std::vector<unsigned int>& cards, int low, int high){
	if (low < high){
		int p = partition(frequency, cards, low, high);
		quicksort(frequency, cards, low, p - 1);
		quicksort(frequency, cards, p + 1, high);
	}
}

/*
*	find the cards that were on top of the stack most frequently during the shuffling and display the result
*	params:
*		n: the n most frequent
*		cards: the stack of the cards
*		top_cards: the recorded top cards during shuffling
*/
void most_frequent(size_t n, const std::vector<unsigned int>& cards, const std::vector<unsigned int>& top_cards){
	std::vector<unsigned int> frequency(cards.size()); // create vector recording the frequency
	std::vector<unsigned int> sorted_cards(cards); // create vector by copy to track the order
	for (size_t i = 0; i < frequency.size(); i++)
	{
		frequency[i] = 0;
	}
	for (size_t i = 0; i < cards.size(); i++)
	{
		for (size_t j = 0; j < top_cards.size(); j++)
		{
			if (cards[i] == top_cards[j]){
				frequency[i]++;
			}
		}
	}
	// sort the frequency vector and permute the order vector according to the frequency
	quicksort(frequency, sorted_cards, 0, frequency.size()-1);

	std::cout << "The cards that were on top of the stack most frequently during the shuffling: ";
	display_vector(sorted_cards, n);
	std::cout << ", frequency: ";
	display_vector(frequency, n);
	std::cout << std::endl;
}

/*
*	find at which shuffling was the topmost card on top for the first time and return the number
*	params:
*		n: the n most frequent
*		cards: the stack of the cards
*		top_cards: the recorded top cards during shuffling
*/
unsigned int find_which_shuffling(const std::vector<unsigned int>& cards, const std::vector<unsigned int>& top_cards){
	unsigned int shuffle = 1;
	for (size_t i = 0; i < top_cards.size(); i++)
	{
		if (top_cards[i] == cards[0]){
			return shuffle;
		}
		shuffle++;
	}
	return shuffle;
}

/*
*	find how often was the topmost card on top throughout the shuffling and return the frequency
*	params:
*		cards: the stack of the cards
*		top_cards: the recorded top cards during shuffling
*/
unsigned int most_frequent_topmost(const std::vector<unsigned int>& cards, const std::vector<unsigned int>& top_cards){
	unsigned int counter = 0;
	for (size_t j = 0; j < top_cards.size(); j++)
	{
		if (cards[0] == top_cards[j]){
			counter++;
		}
	}
	return counter;
}

int main(){
	std::vector<unsigned int> cards;
	size_t k;
	std::cout << "Please enter a number between 2 and 5000: ";
	std::cin >> k;
	//if (k<2 || k>5000){
	//	return -1;
	//}
	size_t n = 3; // the top n cards are of interest
	size_t cards_number = 2 * k;
	for (size_t i = 1; i <= cards_number; i++)
	{
		cards.push_back(i);
	}
	std::vector<unsigned int> top_cards;
	complete_shuffle(k, cards, top_cards);
	std::cout << "The " << n << " topmost cards after complete shuffle: ";
	display_vector(cards, n);
	std::cout << std::endl;
	most_frequent(n, cards, top_cards);
	std::cout << "At the " << find_which_shuffling(cards, top_cards);
	std::cout << " shuffling, the topmost card on top for the first time, frequency: ";
	std::cout << most_frequent_topmost(cards, top_cards) << std::endl;
	
	return 0;
}