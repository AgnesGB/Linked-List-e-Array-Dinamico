#include <iostream>
#include <chrono>
#include "linked_list.hpp"

void print_list_state(const linked_list& list) {
    std::cout << "Size: " << list.size() << ", Capacity: " << list.capacity() << std::endl;
}

void run_tests(linked_list& list) {
    using namespace std::chrono;

    std::cout << "Testing linked list:\n";

    auto start = high_resolution_clock::now();

    // Teste de inserção de 10000 elementos
    for (int i = 0; i < 10000; ++i) {
        list.push_back(i);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Insertion of 10000 elements: " << duration << " ms" << std::endl;
    print_list_state(list);

    start = high_resolution_clock::now();

    // Teste de remoção de 5000 elementos
    for (int i = 0; i < 5000; ++i) {
        list.pop_back();
    }

    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Removal of 5000 elements: " << duration << " ms" << std::endl;
    print_list_state(list);

    start = high_resolution_clock::now();

    // Teste de inserção em diferentes índices
    for (int i = 0; i < 1000; ++i) {
        list.insert_at(i % 100, i); // Insere elementos em índices variados
    }

    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Insertion at varying indices: " << duration << " ms" << std::endl;
    print_list_state(list);

    start = high_resolution_clock::now();

    // Teste de remoção em diferentes índices
    for (int i = 0; i < 1000; ++i) {
        list.remove_at(i % 100); // Remove elementos em índices variados
    }

    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Removal at varying indices: " << duration << " ms" << std::endl;
    print_list_state(list);

    start = high_resolution_clock::now();

    // Teste de busca de elementos
    int search_value = 5000;
    int index = list.find(search_value);

    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Finding element " << search_value << ": Index " << index << ", Time: " << duration << " ms" << std::endl;

    start = high_resolution_clock::now();

    // Teste de contagem de elementos
    int count_value = 500;
    int count = list.count(count_value);

    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Counting occurrences of " << count_value << ": " << count << ", Time: " << duration << " ms" << std::endl;

    start = high_resolution_clock::now();

    // Teste de soma dos elementos
    int sum = list.sum();

    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Sum of elements: " << sum << ", Time: " << duration << " ms" << std::endl;

    start = high_resolution_clock::now();

    // Teste de remoção de todos os elementos
    list.clear();

    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Clearing all elements: " << duration << " ms" << std::endl;
    print_list_state(list);

    std::cout << "\n";
}

int main() {
    linked_list list;

    run_tests(list);

    return 0;
}
