#pragma once
#include <iostream>
using namespace std;

namespace bit {
	template<class T>
	struct ListNode{
		T _data;
		ListNode<T>* _next;
		ListNode<T>* _pre;
		ListNode(const T& data) :_next(nullptr),_pre(nullptr) {
			_data = data;
		}
		ListNode() :_next(nullptr), _pre(nullptr) {}
	};
	template <class T,class Ref,class Ptr>
	struct __list_iterator{
		typedef ListNode<T> _node;
		typedef __list_iterator <T, Ref, Ptr> self;
		_node* Node;
		
		__list_iterator(_node* node):Node(node) {	}
		Ref operator *() {
			return Node->_data;
		}
		Ptr operator ->() {
			return &Node->_data;
		}
		self& operator --() {
			Node=Node->_pre;
			return *this;
		}
		self& operator --(int) {
			self tmp = *this;
			Node = Node->_pre;
			return tmp;
		}
		self& operator ++() {
			Node = Node->_next;
			return *this;
		}
		self& operator ++(int) {
			self tmp = *this;
			Node = Node->_next;
			return tmp;
		}
		bool operator ==(const self& s) {
			return Node == s.Node;
		}
		bool operator !=(const self& s) {
			return Node != s.Node;
		}
		
	};
	template <class T>
	class list {
		typedef ListNode<T> _node;
		typedef __list_iterator<T, T&, T*> iterator;
		int size;
	public:
		list() {
			List_init();
		}
		list(const list<T>& val) {
			List_init();
			for (auto e : val) {
				push_back(e);
			}
		}
		~list() {
			clear();
			delete ListHead;
			ListHead= nullptr;
			
		}
		void clear() {
			iterator it = begin();
			while (it != end()) {
				erase(it);
			}
		}
		iterator begin() {
			return ListHead->_next;
		}
		iterator end() {
			return ListHead;
		}
		iterator begin() const{
			return ListHead->_next;
		}
		iterator end() const {
			return ListHead;
		}
		void List_init() {
			ListHead = new _node;
			ListHead->_next = ListHead;
			ListHead->_pre = ListHead;
			
		}
		void push_back(const T& value) {
			insert(ListHead, value);

		}
		void push_front(const T& value)
		{
			insert(ListHead->_next, value);
			
		}
		void pop_back() {
			erase(--end());
		}
		void pop_front()
		{
			erase(begin);
		}
		iterator insert(iterator pos,const T& value) {
			_node* tmp = new _node(value);
			pos.Node->_pre->_next = tmp;
			tmp->_next = pos.Node;
			tmp->_pre = pos.Node->_pre;
			pos.Node->_pre = tmp;
			return iterator(tmp);

		}
		iterator erase(iterator pos) {
			_node* next = pos.Node->_next;
			pos.Node->_pre->_next = pos.Node->_next;
			pos.Node->_next->_pre = pos.Node->_pre;
			pos.Node->_next = nullptr;
			pos.Node->_pre = nullptr;
			delete pos.Node;
			return next;

		}
	private:
		_node* ListHead;
	};
	void test() {
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);

	}
}
