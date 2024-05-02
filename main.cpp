
#pragma once
#include<iostream>
#include<string>
#include<random>
#include<vector>

namespace funct {

    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    template<typename K, typename T>
    struct Pair {
        K _key;
        T _value;
        Pair(K key, T value) : _key(key), _value(value) {}
        Pair() : _key(K()), _value(T()) {}
    };

    template<typename K, typename T>
    struct Node {
        Pair<K, T> _pair;
        Node<K, T>* _next;
        Node(const Pair<K, T>& data) : _pair(data), _next(nullptr) {}
        Node() : _pair(Pair<K, T>()), _next(nullptr) {}
    };

    template<typename K, typename T>
    class HashTable {
    private:
        size_t _size;
        std::vector<Node<K, T>*> _data;

        size_t hash(const K& key) {
            return key % _data.size();
        }

    public:
        HashTable(size_t size) : _data(size), _size(0) {}
        HashTable(size_t size, size_t str_length) : _data(size), _size(0){
            std::random_device rd;
            std::mt19937 generator(rd());
            std::uniform_int_distribution<int> charDistribution(0, alphabet.size() - 1);

            for (size_t i = 0; i < _data.size(); ++i) {
                if (_data[i] == nullptr) {
                    std::string randomString= "";
                    for (size_t j = 0; j < str_length; j++) {
                        randomString += alphabet[charDistribution(generator)];
                    }
                    insert(charDistribution(generator), randomString);
                }
            }
        }

        ~HashTable() {
            clear();
        }

        void clear() {
            for (size_t i = 0; i < _data.size(); i++) {
                if (_data[i]) {
                    Node<K, T>* head = _data[i];
                    while (head != nullptr) {
                        Node<K, T>* temp = head;
                        head = head->_next;
                        delete temp;
                    }
                }
            }
            _data.clear();
        }

        HashTable(const HashTable& other) : _data(other._data.size()), _size(0) {
            for (size_t i = 0; i < other._data.size(); ++i) {
                if (other._data[i]) {
                    Node<K, T>* current = other._data[i];
                    while (current != nullptr) {
                        insert(current->_pair._key, current->_pair._value);
                        current = current->_next;
                    }
                }
            }
        }

        HashTable& operator=(const HashTable& other) {
            if (this != &other) {
                clear();
                _size = other._size;
                _data.resize(other._data.size(), nullptr);
                for (size_t i = 0; i < other._data.size(); ++i) {
                    Node<K, T>* current = other._data[i];
                    Node<K, T>* prev = nullptr;
                    while (current != nullptr) {
                        Node<K, T>* newNode = new Node<K, T>(current->_pair);
                        if (prev == nullptr) {
                            _data[i] = newNode;
                        }
                        else {
                            prev->_next = newNode;
                        }
                        prev = newNode;
                        current = current->_next;
                    }
                }
            }
            return *this;
        }

        void print() const {
            for (size_t i = 0; i < _data.size(); i++) {
                if (_data[i] != nullptr) {
                    Node<K, T>* ptr = _data[i];
                    while (ptr != nullptr) {
                        std::cout << "(" << ptr->_pair._key << ", '" << ptr->_pair._value << "') ";
                        ptr = ptr->_next;
                    }
                }
            }
            std::cout << std::endl;
        }

        size_t count(K key) const {
            size_t index = hash(key);
            int count = 0;
            Node<K, T>* node = _data[index];
            while (node != nullptr) {
                if (node->_pair._key == key) {
                    count++;
                }
                node = node->_next;
            }
            return count;
        }

        bool contains(K key) {
            size_t index = hash(key);
            if (!_data[index]) {
                return false;
            }
            Node<K, T>* ptr = _data[index];
            while (ptr) {
                if (ptr->_pair._key == key) {
                    return true;
                }
                ptr = ptr->_next;
            }
            return false;
        }

        void insert(K key, T value) {
            if (contains(key)) {
                return;
            }
            size_t index = hash(key);

            if (!_data[index]) {
                _data[index] = new Node<K, T>(Pair<K, T>(key, value));
            }
            else {
                Node<K, T>* newNode = new Node<K, T>(Pair<K, T>(key, value));
                newNode->_next = _data[index];
                _data[index] = newNode;
            }
            _size++;
        }

        void insert_or_assign(const K& key, const T& value) {
            size_t index = hash(key);
            Node<K, T>* newNode = new Node<K, T>(Pair<K, T>(key, value));
            newNode->_next = _data[index];
            _data[index] = newNode;
            _size++;
        }

        T* search(const K& key) {
            size_t index = hash(key);
            Node<K, T>* node = _data[index];
            while (node != nullptr && node->_pair._key != key) {
                node = node->_next;
            }
            if (node != nullptr) {
                return &node->_pair._value;
            }
            return nullptr;
        }

		bool erase(const K& key) {
            size_t index = hash(key);
            Node<K, T>* prev = nullptr;
            Node<K, T>* current = _data[index];
			while (current != nullptr && current->_pair._key != key) {
				prev = current;
				current = current->_next;
			}
			if (current != nullptr) {
				if (prev == nullptr) {
					_data[index] = current->_next;
				}
				else {
					prev->_next = current->_next;
				}
				delete current;
				return true;
			}
			return false;
		}
	};

}