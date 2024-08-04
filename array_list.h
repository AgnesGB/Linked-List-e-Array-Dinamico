#ifndef __ARRAY_LIST_IFRN__
#define __ARRAY_LIST_IFRN__

#include <functional>
#include <algorithm>

class array_list {
private:
    int* data;
    unsigned int size_, capacity_;
    std::function<void(array_list&)> increase_capacity_strategy;

public:
    // Construtor com escolha de estratégia de aumento de capacidade
    array_list(std::function<void(array_list&)> strategy)
        : data(nullptr), size_(0), capacity_(0), increase_capacity_strategy(strategy) {}

    // Destrutor
    ~array_list() {
        delete[] data;
    }

    // Retorna a quantidade de elementos armazenados
    unsigned int size() const {
        return size_;
    }

    // Retorna o espaço reservado para armazenar os elementos
    unsigned int capacity() const {
        return capacity_;
    }

    // Retorna um valor entre 0.0 a 1.0 com o percentual da memória usada
    double percent_occupied() const {
        return (capacity_ == 0) ? 0.0 : static_cast<double>(size_) / capacity_;
    }

    // Insere elemento no índice index
    bool insert_at(unsigned int index, int value) {
        if (index > size_) return false;
        if (size_ == capacity_) increase_capacity_strategy(*this);
        for (unsigned int i = size_; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size_++;
        return true;
    }

    // Remove elemento do índice index
    bool remove_at(unsigned int index) {
        if (index >= size_) return false;
        for (unsigned int i = index; i < size_ - 1; i++) {
            data[i] = data[i + 1];
        }
        size_--;
        return true;
    }

    // Retorna elemento no índice index, -1 se índice inválido
    int get_at(unsigned int index) const {
        if (index >= size_) return -1;
        return data[index];
    }

    // Remove todos os elementos, deixando o vetor no estado inicial
    void clear() {
        size_ = 0;
    }

    // Adiciona um elemento no "final" do vetor
    void push_back(int value) {
        if (size_ == capacity_) increase_capacity_strategy(*this);
        data[size_++] = value;
    }

    // Adiciona um elemento no "início" do vetor
    void push_front(int value) {
        insert_at(0, value);
    }

    // Remove um elemento do "final" do vetor
    bool pop_back() {
        if (size_ == 0) return false;
        size_--;
        return true;
    }

    // Remove um elemento do "início" do vetor
    bool pop_front() {
        return remove_at(0);
    }

    // Retorna o elemento do "final" do vetor
    int back() const {
        if (size_ == 0) return -1;
        return data[size_ - 1];
    }

    // Retorna o elemento do "início" do vetor
    int front() const {
        if (size_ == 0) return -1;
        return data[0];
    }

    // Remove value do vetor caso esteja presente
    bool remove(int value) {
        int index = find(value);
        if (index != -1) {
            return remove_at(index);
        }
        return false;
    }

    // Retorna o índice de value, -1 caso value não esteja presente
    int find(int value) const {
        for (unsigned int i = 0; i < size_; i++) {
            if (data[i] == value) {
                return i;
            }
        }
        return -1;
    }

    // Retorna quantas vezes value ocorre no vetor
    int count(int value) const {
        int count = 0;
        for (unsigned int i = 0; i < size_; i++) {
            if (data[i] == value) {
                count++;
            }
        }
        return count;
    }

    // Retorna a soma dos elementos do vetor
    int sum() const {
        int total = 0;
        for (unsigned int i = 0; i < size_; i++) {
            total += data[i];
        }
        return total;
    }

    // Métodos amigos para acessar os atributos privados
    friend void increase_capacity_100(array_list&);
    friend void increase_capacity_1000(array_list&);
    friend void increase_capacity_double(array_list&);
};

void increase_capacity_100(array_list& list) {
    unsigned int new_capacity = list.capacity_ + 100;
    int* new_data = new int[new_capacity];
    std::copy(list.data, list.data + list.size_, new_data);
    delete[] list.data;
    list.data = new_data;
    list.capacity_ = new_capacity;
}

void increase_capacity_1000(array_list& list) {
    unsigned int new_capacity = list.capacity_ + 1000;
    int* new_data = new int[new_capacity];
    std::copy(list.data, list.data + list.size_, new_data);
    delete[] list.data;
    list.data = new_data;
    list.capacity_ = new_capacity;
}

void increase_capacity_double(array_list& list) {
    unsigned int new_capacity = (list.capacity_ == 0) ? 8 : list.capacity_ * 2;
    int* new_data = new int[new_capacity];
    std::copy(list.data, list.data + list.size_, new_data);
    delete[] list.data;
    list.data = new_data;
    list.capacity_ = new_capacity;
}

#endif // __ARRAY_LIST_IFRN__
