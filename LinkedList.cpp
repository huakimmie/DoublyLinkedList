#include "LinkedList.h"

linked::node::node(int _val) : val(_val), prev(nullptr), next(nullptr) {}  // node stores value but points to null on either side

linked::iterator::iterator(node* n, const LinkedList* ell) : curr(n), container(ell) {} // iterator references node n for list ell

linked::iterator& linked::iterator::operator++() { //prefix++
	curr = curr->next;
	return *this;
}

linked::iterator linked::iterator::operator++(int dum) { //postfix++
	iterator copy = *this;
	curr = curr->next;
	return copy;
}

linked::iterator& linked::iterator::operator--() { //prefix--
	if (curr == container->first) {
		throw std::logic_error("Invalid adress");
	}
	else if (curr == nullptr) {
		curr = container->last;
	}
	else {
		curr = curr->prev;
	}
	return *this;
}

linked::iterator linked::iterator::operator--(int dum) { //postfix--
	iterator copy(*this);
	--(*this);
	return copy;
}

int& linked::iterator::operator*() { //dereferencing operator
	return curr->val;
}

bool linked::iterator::operator==(const iterator& rhs) const { //comparison
	return ((curr == rhs.curr) && (container == rhs.container));
}

linked::node* linked::iterator::get_curr() const { //accessor 
	return curr;
}

const linked::LinkedList* linked::iterator::get_container() const {
	return container;
}

linked::const_iterator::const_iterator(node* n, const LinkedList* ell) : curr(n), container(ell) {}

linked::const_iterator::const_iterator(iterator it) : curr(it.get_curr()), container(it.get_container()) {}

linked::node* linked::const_iterator::get_curr() const { //accessor to get curr
	return curr;
}

linked::const_iterator& linked::const_iterator::operator++() { //prefix++
	curr = curr->next;
	return *this;
}

linked::const_iterator linked::const_iterator::operator++(int dum) { //postfix++
	const_iterator copy = *this;
	curr = curr->next;
	return copy;
}

linked::const_iterator& linked::const_iterator::operator--() { //prefix--
	curr = curr->prev;
	return *this;
}

linked::const_iterator linked::const_iterator::operator--(int dum) { //postfix--
	const_iterator copy = *this;
	curr = curr->prev;
	return copy;
}

int linked::const_iterator::operator*() const { //dereferencing to get value in node
	return curr->val;
}

bool linked::const_iterator::operator==(const const_iterator& rhs) const { //comparison
	if (curr == nullptr && rhs.get_curr() == nullptr)
		return true;
	else if (curr == nullptr || rhs.get_curr() == nullptr)
		return false;
	return curr->val == *rhs ? true : false;
}

bool linked::operator!=(const iterator& rhs, const iterator& lhs) { //not equal 
	return !(rhs == lhs);
}

bool linked::operator!=(const const_iterator& rhs, const const_iterator& lhs) { //not equal
	return !(rhs == lhs);
}

linked::LinkedList::LinkedList() : first(nullptr), last(nullptr) {} //default

linked::LinkedList::LinkedList(const LinkedList& rhs) : first(nullptr), last(nullptr) { //copy
	for (auto itr = rhs.begin(); itr != rhs.end(); ++itr) {
		push_back(*itr);
	}
}

linked::LinkedList::LinkedList(LinkedList&& rhs) : first(rhs.first), last(rhs.last) { //move
	rhs.first = rhs.last = nullptr;
}

linked::LinkedList::~LinkedList() { //destructor
	node *n = first; // start at first node
	while (n != nullptr) { // while not past the end denoted by nullptr
		node *temp = n->next; // temporarily store the next position
		delete n; // delete the node on heap
		n = temp; // move n right
	}
}

linked::LinkedList& linked::LinkedList::operator=(LinkedList rhs) { //assignment operator
	std::swap(first, rhs.first);
	std::swap(last, rhs.last);
	return *this;
}

void linked::LinkedList::push_back(int val) {
	node *n = new node(val); // create a new node
	if (last) { // if last node not null
		last->next = n; // make last point to n
		n->prev = last; // make n have last as its previous
		last = n; // update the last position
	}
	else { // in this case the last node is null so list is empty
		first = last = n; // both equal to n
	}
}

void linked::LinkedList::pop_back() {
	if (!last) { // list is empty if last null
		throw std::logic_error("pop back on empty list");
	}
	else if (first == last) { // if just one element
		delete first; // free heap memory
		first = last = nullptr; // make both null because empty again
	}
	else {
		node *newlast = last->prev; // store the new last node
		newlast->next = nullptr; // set its next pointer to null
		delete last; // free the heap memory
		last = newlast; // update the last value
	}
}

void linked::LinkedList::push_front(int val) {
	node *n = new node(val); // create a new node
	if (first) { // if first node not null
		first->prev = n; // make first point to n
		n->next = first; // make n have first as its next
		first = n; // update the last position
	}
	else { // in this case the first node is null so list is empty
		first = n; // both equal to n
	}
} // add to beginning

void linked::LinkedList::pop_front() {
	if (!last) { // list is empty if last null
		throw std::logic_error("pop back on empty list");
	}
	else if (last == first) { // if just one element
		delete last; // free heap memory
		last = first = nullptr; // make both null because empty again
	}
	else {
		node *newfirst = first->next; // store the new first node
		newfirst->prev = nullptr; // set its prev pointer to null
		delete first; // free the heap memory
		first = newfirst; // update the first value
	}
}

linked::const_iterator linked::LinkedList::begin() const {	// member function overloaded on const, returning iterators to the beginning;
	const_iterator it(first, this);
	return it;
}

linked::iterator linked::LinkedList::begin() {
	iterator it(first, this);
	return it;
}

linked::const_iterator linked::LinkedList::end() const { //member function overloaded on const returning iterators to the past-the-end;
	const_iterator it(nullptr, this);
	return it;
}

linked::iterator linked::LinkedList::end() {
	iterator it(nullptr, this);
	return it;
}

void linked::LinkedList::insert(iterator it, int val) {
	if (it.curr == nullptr) { // then inserting before past-the-end
		push_back(val);
	}
	else if (it.curr == first) { // then at beginning
		push_front(val);
	}
	else { // then in middle
		node *n = new node(val); // create new node
		n->next = it.curr; // set n’s next
		n->prev = it.curr->prev; // set n’s previous
		it.curr->prev->next = n; // make current previous’ next node into n
		it.curr->prev = n; // make current previous node into n
	}
}

void linked::LinkedList::erase(iterator it) {
	if (it.curr == first) { // removing first
		pop_front(); // remove first
	}
	else if (it.curr == last) { // removing last
		pop_back(); // remove last
	}
	else {
		it.curr->prev->next = it.curr->next; // reroute next of previous
		it.curr->next->prev = it.curr->prev; // reroute previous of next
		delete it.curr; // free the heap memory of item being removed
	} // erase value at position
}

int linked::LinkedList::size() {
	int counter = 1; //counter to keep track of size
	node* fcopy = first;
	while (fcopy != last) { //iterator through each node
		counter++;
		fcopy = fcopy->next;
	}
	return counter;
}

void linked::LinkedList::sort() {
	node* fcopy = first;
	int counter = 0;
	while (fcopy != nullptr) { //loop through all positions in List
		if (fcopy == last) { //if first equals last, check if anything was swapped, if it was, recursively call sort
			if (counter != 0)
				sort();
			fcopy = fcopy->next;
		}
		else if (fcopy->val > fcopy->next->val) { //if out of order, swap values of nodes
			int copy = fcopy->val;
			fcopy->val = fcopy->next->val;
			fcopy->next->val = copy;
			counter++;
			fcopy = fcopy->next;
		}
		else {  //not out of order, advance node pointer
			fcopy = fcopy->next;
		}
	}
}

std::ostream& linked::operator<<(std::ostream& out, LinkedList list) {
	iterator start = list.begin();
	while (start != list.end()) {//loop thoruhg all positions in List
		out << *start << " "; //output value at this position
		++start;
	}

	return out;
}

bool linked::seqSearch(linked::const_iterator a, linked::const_iterator b, int value) {
	while (a != b) {  //loop through all positions between iterators
		if (*a == value) //check if value equals target value
			return true;
		++a; //increment iterator
	}
	return false;
}


