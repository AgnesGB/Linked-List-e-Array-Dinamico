#ifndef __LINKED_LIST_IFRN__
#define __LINKED_LIST_IFRN__

#include <iostream>

class linked_list {
private:
    // Estrutura do nó da lista duplamente ligada
    struct int_node {
        int value;
        int_node* next;
        int_node* prev;

        int_node(int val) : value(val), next(nullptr), prev(nullptr) {}
    };

    int_node* head;
    int_node* tail;
    unsigned int size_;

public:
    // Construtor
    linked_list() : head(nullptr), tail(nullptr), size_(0) {}

    // Destrutor
    ~linked_list() {
        clear();
    }

    // Retorna a quantidade de elementos armazenados
    unsigned int size() const {
        return size_;
    }

    // Retorna o espaço reservado para armazenar os elementos (sempre igual a size_ para lista ligada)
    unsigned int capacity() const {
        return size_;
    }

    // Insere elemento no índice index
    bool insert_at(unsigned int index, int value) {
        if (index > size_) return false;

        int_node* new_node = new int_node(value);

        if (index == 0) {
            new_node->next = head;
            if (head) head->prev = new_node;
            head = new_node;
            if (size_ == 0) tail = new_node;
        } else if (index == size_) {
            new_node->prev = tail;
            if (tail) tail->next = new_node;
            tail = new_node;
        } else {
            int_node* current = head;
            for (unsigned int i = 0; i < index; ++i) {
                current = current->next;
            }
            new_node->next = current;
            new_node->prev = current->prev;
            if (current->prev) current->prev->next = new_node;
            current->prev = new_node;
        }

        size_++;
        return true;
    }

    // Remove elemento do índice index
    bool remove_at(unsigned int index) {
        if (index >= size_) return false;

        int_node* current = head;
        for (unsigned int i = 0; i < index; ++i) {
            current = current->next;
        }

        if (current->prev) current->prev->next = current->next;
        if (current->next) current->next->prev = current->prev;
        if (index == 0) head = current->next;
        if (index == size_ - 1) tail = current->prev;

        delete current;
        size_--;
        return true;
    }

    // Retorna elemento no índice index, -1 se índice inválido
    int get_at(unsigned int index) const {
        if (index >= size_) return -1;

        int_node* current = head;
        for (unsigned int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    // Remove todos os elementos, deixando o vetor no estado inicial
    void clear() {
        while (size_ > 0) {
            pop_front();
        }
    }

    // Adiciona um elemento no "final" do vetor
    void push_back(int value) {
        int_node* new_node = new int_node(value);
        if (size_ == 0) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        size_++;
    }

    // Adiciona um elemento no "início" do vetor
    void push_front(int value) {
        int_node* new_node = new int_node(value);
        if (size_ == 0) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        size_++;
    }

    // Remove um elemento do "final" do vetor
    bool pop_back() {
        if (size_ == 0) return false;

        int_node* to_delete = tail;
        if (size_ == 1) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete to_delete;
        size_--;
        return true;
    }

    // Remove um elemento do "início" do vetor
    bool pop_front() {
        if (size_ == 0) return false;

        int_node* to_delete = head;
        if (size_ == 1) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete to_delete;
        size_--;
        return true;
    }

    // Retorna o elemento do "final" do vetor
    int back() const {
        if (size_ == 0) return -1;
        return tail->value;
    }

    // Retorna o elemento do "início" do vetor
    int front() const {
        if (size_ == 0) return -1;
        return head->value;
    }

    // Remove value do vetor caso esteja presente
    bool remove(int value) {
        int_node* current = head;
        for (unsigned int i = 0; i < size_; ++i) {
            if (current->value == value) {
                if (current->prev) current->prev->next = current->next;
                if (current->next) current->next->prev = current->prev;
                if (i == 0) head = current->next;
                if (i == size_ - 1) tail = current->prev;

                delete current;
                size_--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Retorna o índice de value, -1 caso value não esteja presente
    int find(int value) const {
        int_node* current = head;
        for (unsigned int i = 0; i < size_; ++i) {
            if (current->value == value) {
                return i;
            }
            current = current->next;
        }
        return -1;
    }

    // Retorna quantas vezes value ocorre no vetor
    int count(int value) const {
        int count = 0;
        int_node* current = head;
        for (unsigned int i = 0; i < size_; ++i) {
            if (current->value == value) {
                count++;
            }
            current = current->next;
        }
        return count;
    }

    // Retorna a soma dos elementos do vetor
    int sum() const {
        int total = 0;
        int_node* current = head;
        for (unsigned int i = 0; i < size_; ++i) {
            total += current->value;
            current = current->next;
        }
        return total;
    }
};

#endif // __LINKED_LIST_IFRN__