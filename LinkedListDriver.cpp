#include "LinkedList.h"
int main() {
	linked::LinkedList list1;
	list1.push_back(8);
	list1.push_back(3);
	list1.push_back(14);
	list1.push_back(-13);
	list1.push_back(0);
	list1.push_back(3);
	auto it = list1.begin();
	++it;
	list1.insert(it, 144);
	list1.insert(list1.end(), 44);
	list1.pop_back();
	const linked::LinkedList list2 = list1;
	list1.sort();
	std::cout << "List 1: " << list1 << std::endl;
	std::cout << "List 2: " << list2 << std::endl;
	auto beg1 = list1.begin();
	auto end1 = list1.end();
	end1--;
	auto beg2 = list2.begin();
	auto end2 = list2.end();
	bool found1 = linked::seqSearch(beg1, end1, 144);
	bool found2 = linked::seqSearch(beg2, end2, 144);
	std::cout << std::boolalpha << found1 << " " << found2 << std::endl;
	std::cin.get();
	return 0;
}