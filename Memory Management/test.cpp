#include "my_heap.h"
#include <iostream>
using namespace std;


int main(){
    My_heap heap;

    memory_block* b1 = heap.bump_allocate(10);
    cout << "~~~~~~~~~~~~~~\n";
    cout << "Bump allocate 10\n";
    cout << "~~~~~~~~~~~~~~\n";
    memory_block* b2 = heap.first_fit_allocate(20);
    cout << "~~~~~~~~~~~~~~\n";
    cout << "First fit allocate 20\n";
    cout << "~~~~~~~~~~~~~~\n";
    memory_block* b3 = heap.first_fit_split_allocate(10);
    cout << "~~~~~~~~~~~~~~\n";
    cout << "First fit split allocate 10\n";
    cout << "~~~~~~~~~~~~~~\n";
    memory_block* b4 = heap.best_fit_allocate(15);
    cout << "~~~~~~~~~~~~~~\n";
    cout << "Best fit allocate 15\n";
    cout << "~~~~~~~~~~~~~~\n";
    heap.print_heap();

    heap.deallocate(b4);
    cout << "~~~~~~~~~~~~~~\n";
    cout << "deallocate\n";
    cout << "~~~~~~~~~~~~~~\n";
    heap.print_heap();
    heap.deallocate(b2);
    cout << "~~~~~~~~~~~~~~\n";
    cout << "deallocate\n";
    cout << "~~~~~~~~~~~~~~\n";
    heap.print_heap();

    memory_block* b5 = heap.best_fit_allocate(12);
    cout << "~~~~~~~~~~~~~~\n";
    cout << "Best fit allocate 12\n";
    cout << "~~~~~~~~~~~~~~\n";
    heap.print_heap();

    memory_block* b6 = heap.first_fit_split_allocate(16);
    cout << "~~~~~~~~~~~~~~\n";
    cout << "First fit split allocate 16\n";
    cout << "~~~~~~~~~~~~~~\n";
    heap.print_heap();

    heap.deallocate(b3);
    cout << "~~~~~~~~~~~~~~\n";
    cout << "deallocate\n";
    cout << "~~~~~~~~~~~~~~\n";
    heap.print_heap();
    heap.deallocate(b5);
    cout << "~~~~~~~~~~~~~~\n";
    cout << "deallocate\n";
    cout << "~~~~~~~~~~~~~~\n";
    heap.print_heap();
    memory_block* b7 = heap.first_fit_allocate(16);
    cout << "~~~~~~~~~~~~~~\n";
    cout << "First fit allocate 16\n";
    cout << "~~~~~~~~~~~~~~\n";
    heap.print_heap();

    
    return 0;
}
/*
OUTPUT:
~~~~~~~~~~~~~~
Bump allocate 10
~~~~~~~~~~~~~~
~~~~~~~~~~~~~~
First fit allocate 20
~~~~~~~~~~~~~~
~~~~~~~~~~~~~~
First fit split allocate 10
~~~~~~~~~~~~~~
~~~~~~~~~~~~~~
Best fit allocate 15
~~~~~~~~~~~~~~
Maximum capacity of heap: 512B
Currently used memory (B): 55
Total memory blocks: 4
Total used memory blocks: 4
Total free memory blocks: 0
Fragmentation: 0%
------------------------------
Block 0		Used: True	Size (B): 10	Starting address: 0x0
Block 1		Used: True	Size (B): 20	Starting address: 0xa
Block 2		Used: True	Size (B): 10	Starting address: 0x1e
Block 3		Used: True	Size (B): 15	Starting address: 0x28
------------------------------
------------------------------
~~~~~~~~~~~~~~
deallocate
~~~~~~~~~~~~~~
Maximum capacity of heap: 512B
Currently used memory (B): 40
Total memory blocks: 4
Total used memory blocks: 3
Total free memory blocks: 1
Fragmentation: 3.17797%
------------------------------
Block 0		Used: True	Size (B): 10	Starting address: 0x0
Block 1		Used: True	Size (B): 20	Starting address: 0xa
Block 2		Used: True	Size (B): 10	Starting address: 0x1e
Block 3		Used: False	Size (B): 15	Starting address: 0x28
------------------------------
------------------------------
~~~~~~~~~~~~~~
deallocate
~~~~~~~~~~~~~~
Maximum capacity of heap: 512B
Currently used memory (B): 20
Total memory blocks: 4
Total used memory blocks: 2
Total free memory blocks: 2
Fragmentation: 7.11382%
------------------------------
Block 0		Used: True	Size (B): 10	Starting address: 0x0
Block 1		Used: False	Size (B): 20	Starting address: 0xa
Block 2		Used: True	Size (B): 10	Starting address: 0x1e
Block 3		Used: False	Size (B): 15	Starting address: 0x28
------------------------------
------------------------------
~~~~~~~~~~~~~~
Best fit allocate 12
~~~~~~~~~~~~~~
Maximum capacity of heap: 512B
Currently used memory (B): 35
Total memory blocks: 4
Total used memory blocks: 3
Total free memory blocks: 1
Fragmentation: 4.19287%
------------------------------
Block 0		Used: True	Size (B): 10	Starting address: 0x0
Block 1		Used: False	Size (B): 20	Starting address: 0xa
Block 2		Used: True	Size (B): 10	Starting address: 0x1e
Block 3		Used: True	Size (B): 15	Starting address: 0x28
------------------------------
------------------------------
~~~~~~~~~~~~~~
First fit split allocate 16
~~~~~~~~~~~~~~
Maximum capacity of heap: 512B
Currently used memory (B): 51
Total memory blocks: 5
Total used memory blocks: 4
Total free memory blocks: 1
Fragmentation: 0.867679%
------------------------------
Block 0		Used: True	Size (B): 10	Starting address: 0x0
Block 1		Used: True	Size (B): 16	Starting address: 0xa
Block 2		Used: False	Size (B): 4	Starting address: 0x1a
Block 3		Used: True	Size (B): 10	Starting address: 0x1e
Block 4		Used: True	Size (B): 15	Starting address: 0x28
------------------------------
------------------------------
~~~~~~~~~~~~~~
deallocate
~~~~~~~~~~~~~~
Maximum capacity of heap: 512B
Currently used memory (B): 41
Total memory blocks: 4
Total used memory blocks: 3
Total free memory blocks: 1
Fragmentation: 2.9724%
------------------------------
Block 0		Used: True	Size (B): 10	Starting address: 0x0
Block 1		Used: True	Size (B): 16	Starting address: 0xa
Block 2		Used: False	Size (B): 14	Starting address: 0x1a
Block 3		Used: True	Size (B): 15	Starting address: 0x28
------------------------------
------------------------------
~~~~~~~~~~~~~~
deallocate
~~~~~~~~~~~~~~
Maximum capacity of heap: 512B
Currently used memory (B): 26
Total memory blocks: 3
Total used memory blocks: 2
Total free memory blocks: 1
Fragmentation: 5.96708%
------------------------------
Block 0		Used: True	Size (B): 10	Starting address: 0x0
Block 1		Used: True	Size (B): 16	Starting address: 0xa
Block 2		Used: False	Size (B): 29	Starting address: 0x1a
------------------------------
------------------------------
~~~~~~~~~~~~~~
First fit allocate 16
~~~~~~~~~~~~~~
Maximum capacity of heap: 512B
Currently used memory (B): 55
Total memory blocks: 3
Total used memory blocks: 3
Total free memory blocks: 0
Fragmentation: 0%
------------------------------
Block 0		Used: True	Size (B): 10	Starting address: 0x0
Block 1		Used: True	Size (B): 16	Starting address: 0xa
Block 2		Used: True	Size (B): 29	Starting address: 0x1a
------------------------------
------------------------------
At destruction, the heap had a memory leak of 55 bytes
*/