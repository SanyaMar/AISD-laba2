#include <gtest/gtest.h>
#include "main.cpp"
#include <stdexcept>
#include <iostream>

using namespace funct;
using namespace std;

TEST(HashTableTest, InsertString) {
	HashTable<int, string> a(10);
	a.insert(5, "Cat");
	a.insert(3, "Dog");
	a.insert(9, "Pig");
	HashTable<int, string> b(a);
	a.print();
	b.print();
}

TEST(HashTableTest, InsertInt) {
	HashTable <int, int> a(10);
	a.insert(1, 15);
	a.insert(1, 9);
	a.insert(3, 26);
	a.insert(6, 7);
	a.print();
}

TEST(HashTableTest, HashTable) {
	HashTable<int, string> a(10);
	a.insert(5, "Cat");
	a.insert(3, "Dog");
	a.insert(9, "Pig");
	a.insert(7, "Mice");
	a.insert(1, "Frog");
	a.insert(2, "Parrot");
	a.print();
	
}
