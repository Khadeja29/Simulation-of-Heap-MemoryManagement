#include "my_heap.h"
#include <iostream>
#include <string>

using namespace std;

//Constructor
My_heap :: My_heap()
{
	heap_begin = nullptr;
    blk = nullptr;
	used_bytes=0;
}

memory_block* My_heap :: bump_allocate(int num_bytes)
{
	/*bool check= false;
	memory_block* travel= heap_begin;
	int check_total_allocate=0;
	while(travel!=nullptr)
	{
		if(heap_begin==nullptr) 
		{ check=true;
		  break;
		}
		else
		{
			check_total_allocate += travel->size;
		}
		travel= travel->right;
	}
	if (MAX_CAPACITY-check_total_allocate>= num_bytes) 
	{
		check = true;
	}*/
	if (used_bytes+num_bytes <= MAX_CAPACITY) //(check==true) 
	{ 
		memory_block* new_allocation = new memory_block;
		new_allocation ->used = true;
		new_allocation ->size = num_bytes;
		if( heap_begin == nullptr)
		{
			new_allocation ->left = nullptr;
			new_allocation ->right= nullptr;
			new_allocation ->starting_address= 0;

			heap_begin = new_allocation;
			blk= new_allocation;
			used_bytes = used_bytes+ num_bytes;
		}
		else
		{
			memory_block* traverse = heap_begin;
			while( traverse != nullptr)
			{
				if(traverse->right ==nullptr)
				{break;}
				else{traverse=traverse->right;}
			}

			traverse-> right = new_allocation;
			new_allocation-> left= traverse;
			new_allocation->right = nullptr;
			new_allocation->starting_address = new_allocation->left->size+ new_allocation->left->starting_address;

			blk = new_allocation;
			used_bytes = used_bytes+num_bytes;
		}
		return blk;
	}
	else{
		return nullptr;
	}
	
}

//For deallocation:
//1- at head: either  block has free memory to the right  or block has no free memory to left or right 
//2- at tail: block has free memory to the left  or block has no free memory to left or right 
//3- in middle: // d- Block has no free memory to the left or right 
                // a-Block has free memory to the left 
                // b- block has free memory to the right 
                // c-block had free memory to the left and right 

void My_heap :: deallocate(memory_block* block_address)
{
	if( heap_begin != nullptr) //heap is not empty and alteast one node
	{
		//1- block_address at head
		if( block_address == heap_begin)
		{
			if( block_address->right->used == false) //Check memory_block to the right,it is free then:
			{
				//More than 2 nodes on the list. blk remians same.starting_add remains same=0
				if ( block_address->right->right !=nullptr)
				{
					block_address->size = block_address->size+ block_address->right->size;
					block_address->used=false;

					block_address->right= block_address->right->right;
					delete block_address->right->left;
					block_address->right->left= block_address;
					used_bytes= used_bytes-block_address->size;
	
				}
				//only two nodes.blk  changes.starting_address same=0
				else
				{
					block_address->size = block_address->size+ block_address->right->size;
					block_address->used=false;
					blk= block_address;
					used_bytes= used_bytes-block_address->size;
					delete block_address->right;
					block_address->right=nullptr;
					
				}
			}
			//Either only one node in the list or the right is not free.blk and heap_begin dont change.
			else if( block_address->right == nullptr ||block_address->right->used ==true)
			{ 
				//Only change status of used and decrement the used bytes
				block_address->used = false;
				used_bytes= used_bytes-block_address->size;
			}
		}
		// 2-To be deallocated is at the end of list
		else if (block_address == blk)
		{
			//Check if free memory_block to the left only
			if(block_address->left->used == false)
			{
				//More than 2 nodes on the list.//only two nodes . heap_begin remians same.blk changes
				
					block_address->left->size = block_address->size+ block_address->left->size;
					blk=block_address->left;
					block_address->left->right=nullptr;
					used_bytes= used_bytes-block_address->size;	
					delete block_address;
					
			}
			//no change to list required.used changed to false and used_bytes decremented 
			else 
			{
				block_address->used =false;
				used_bytes=used_bytes-block_address->size;
			}
		}
		//3- The memeory block to be deallocated is somewhere in the middle of the list
		else
		{
			//memory block to the left is free but memory block to right is occupied.blk remains unchanged,difference in heap_begin
			if(block_address->left->used ==false && block_address->right->used ==true)
			{
				block_address->left->size = block_address->left->size+block_address->size;
				block_address->left->right= block_address->right;
				block_address->right->left= block_address->left;
				used_bytes= used_bytes-block_address->size;
				delete block_address;
					
			}

			//memory block to the right is free but memory block to left is occupied.
			else if (block_address->right->used ==false && block_address->left->used ==true)
			{
				
				//The right free memory block is pointed by blk/is end of the list.Change blk.S
				if(block_address->right->right == nullptr)
				{
					block_address->size = block_address->left->size+block_address->size;
					block_address->used=false;
					blk=block_address;
					used_bytes= used_bytes-block_address->size;	
					delete block_address->right;
					block_address->right=nullptr;
					
				}
				//The right free memeory block is not the tail.blk remains the same.
				else
				{
					block_address->size = block_address->right->size+block_address->size;
					block_address->used=false;
					block_address->right= block_address->right->right;
					delete block_address->right->left;
					block_address->right->left= block_address;
					used_bytes= used_bytes-block_address->size;	
				}	
			}
			//memory block to the left is free and memory block to right is free.
			else if (block_address->right->used ==false && block_address->left->used ==false)
			{				
				//The right free memory block is not pointed by blk/not end.blk same
				if (block_address->right->right != nullptr)
				{
					block_address->left->size =block_address->left->size+ block_address->size + block_address->right->size;

					block_address->left->right= block_address->right->right;
					block_address->right->right->left= block_address->left;
					used_bytes= used_bytes-block_address->size;	
					delete block_address->right;
					delete block_address;
					

				}
				
				//Block address left is th elast node.blk changes.
				else 
				{
					block_address->left->size =block_address->left->size+ block_address->size + block_address->right->size;
					blk= block_address->left;
					block_address->left->right= nullptr;
					used_bytes= used_bytes-block_address->size;	
					delete block_address->right;
					delete block_address;
					
				}
			}
			//No memory_block empty to the right or left of the node in the middle
			else
			{ 
				block_address->used =false;
				used_bytes=used_bytes-block_address->size;
			}
		}
		
	}
}

memory_block * My_heap :: first_fit_allocate(int num_bytes)
{
	memory_block* search_first = heap_begin;
	
	//bool found = false;
	if (heap_begin == nullptr) { return nullptr;}
	while(search_first!= nullptr)
	{
		if( search_first->used== false && num_bytes <= search_first->size )
		{
			search_first->used = true;
			
			used_bytes= used_bytes+search_first->size;
			return(search_first);
		}
		else
		{
			search_first=search_first->right;
		}
	}
	return(bump_allocate(num_bytes));
}

memory_block * My_heap :: best_fit_allocate(int num_bytes)
{
	if (heap_begin == nullptr) 
	{ 
		return nullptr;
	}
	memory_block* search_best = heap_begin;
	int min_difference= INT_MAX;
	memory_block* track= nullptr;
	bool found_best=false;
	while(search_best !=nullptr)
	{
		if(search_best->used== false && num_bytes <= search_best->size)
		{

			if(min_difference >= (search_best->size - num_bytes) )
			{
				min_difference = search_best->size- num_bytes;
				track = search_best;
				found_best=true;
				
			}
		}
		
		search_best= search_best->right;
	}

	if( found_best == false)
	{ 
			return (bump_allocate(num_bytes));

	}
	else
	{
		track->used=true;
		used_bytes = used_bytes+track->size;
		return track;
	}
}

memory_block * My_heap :: first_fit_split_allocate(int num_bytes)
{
	memory_block* search_tosplit = heap_begin;
	bool found_tosplit = false;
	if (heap_begin == nullptr) 
	{ 
		return nullptr;
	}
	while(search_tosplit!= nullptr) // && found_tosplit==false)
	{
		if( search_tosplit->used== false && num_bytes <= search_tosplit->size )
		{ 
			 if( num_bytes == search_tosplit->size)
			 {
				 search_tosplit->used = true;
				 used_bytes= used_bytes+num_bytes;
				 found_tosplit==true;
				 return (search_tosplit);
				 
			 }
			 else
			 {
				 memory_block * temp = new memory_block;
				 temp->size= search_tosplit->size-num_bytes;
				 temp->used=false;
				 temp-> starting_address= search_tosplit->starting_address+num_bytes;
				 temp->right = search_tosplit->right;
				 temp->left= search_tosplit;
				 search_tosplit->right->left= temp;
				 used_bytes= used_bytes+num_bytes;

				 search_tosplit->size= num_bytes;
				 search_tosplit->used= true;
				 search_tosplit->right=temp;
				 found_tosplit==true;
				 return (search_tosplit);
			 }
		}
		else
		{
			search_tosplit=search_tosplit->right;
		}
	}

	if(found_tosplit == false)
	{
		if(bump_allocate(num_bytes) == nullptr)
		{
			return nullptr;
		}
	}
}

float My_heap ::  get_fragmantation()
{
	float free_memory,biggest_free_block;
	free_memory= 512-used_bytes;
	memory_block*look=heap_begin;
	float totalallocated=0;
	while(look!=nullptr)
	{
		totalallocated= look->size+totalallocated;
		look=look->right;
	}

	biggest_free_block= 512-totalallocated;
	float fragmentation=(free_memory-biggest_free_block)/free_memory * 100 ;
	return fragmentation;
}

void My_heap :: print_heap()
{
	cout <<"Maximum capacity of heap: 512B"<<endl;
	cout<<"Currently used memory (B): "<< dec<<used_bytes<<endl;
    int Total_used=0, Total_blocks=0,Total_free=0;
	if (heap_begin != nullptr)
	{
		memory_block* trans= heap_begin;
		while(trans!=nullptr)
		{
			Total_blocks++;
			if( trans->used == false)
			{
				Total_free++;
			}
			else if(trans->used == true)
			{
				Total_used++;
			}
			trans=trans->right;
		}
	}
	cout<<"Total memory blocks: "<<dec<< Total_blocks<<endl;
	cout<<"Total used memory blocks: "<<dec<< Total_used<<endl;
	cout<<"Total free memory blocks: "<<dec<< Total_free<<endl;
	cout<<"Fragmentation: "<<get_fragmantation()<<"%"<<endl;
	cout<<"------------------------------"<<endl;

	memory_block* tra= heap_begin;
	int index=0;
	string bool_use;
	while( tra!=nullptr)
	{
		
		if( tra->used ==true) {
			bool_use= "True";
		}
		else
		{
			bool_use= "False";
		}

		cout<< "Block "<<dec<< index<<"\t\t"<< "Used: "<<bool_use<< "\tSize (B): "<<dec<<tra->size<<"\tStarting Address: 0x" << hex<<tra->starting_address<<"\n";
		tra=tra->right;
		index++;
	}
	cout<<"------------------------------"<<endl;
	cout<<"------------------------------"<<endl;
}

My_heap::~My_heap()
{
	cout << "At destruction, the heap had a memory leak of " <<dec<< used_bytes<< " bytes" << endl;


	memory_block* remove=heap_begin;
	while(heap_begin!=nullptr)
	{
		remove =heap_begin;
		heap_begin=heap_begin->right;
		delete remove;
	}	

}
