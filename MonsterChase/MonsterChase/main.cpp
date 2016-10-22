#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <crtdbg.h>
#include "Monster.h"
#include "Player.h"
#include "MonsterController.h"
#include "Debug.h"
#include "MemoryAllocator.h"
#include "MemoryAllocatorTest.h"
#include "time.h"

void printList(BlockDescriptorList);
int main() {
	/*
	srand((unsigned int)time(NULL));
	int num_monsters;
	printf("Please enter the number of monsters you'd like to create:\n");
	scanf_s("%d", &num_monsters);
	assert(num_monsters > 0, "Invalid number of monsters");
	MonsterController monster_controller;

	Monster *monsters = new Monster[num_monsters];
	for (int i = 0; i < num_monsters; i++) {
		Monster monster;
		char *monster_name = new char[30];
		printf("Please enter your name for monster number %d: ", i);
		scanf_s("%s", monster_name, sizeof(monster_name));
		monsters[i].set_name(monster_name);
	}
	Player player;
	char player_name[30];
	printf("Please enter your name for the player: ");
	scanf_s("%s", player_name, sizeof(player_name));
	player.set_name(player_name);
	printf("\nPlayer %s is at position [%.2f, %.2f]\n", player.get_name(), player.get_position().x(), player.get_position().y());
	monster_controller.print_monsters(monsters, num_monsters);
	printf("Press Enter to continue...\n");

	// Main game loop
	int input;
	while (input = toupper(_getch()) != 'Q') {
		printf("Move your player. Left: A, Right: D, Up: W, Down: S\n");
		input = toupper(_getch());
		assert((input == 'A' || input == 'W' || input == 'S' || input == 'D'), "Invalid input");
		player.move(input);
		printf("\nPlayer %s is at position [%.2f, %.2f]\n", player.get_name(), player.get_position().x(), player.get_position().y());

		monster_controller.print_monsters(monsters, num_monsters);

		if (monster_controller.should_add_monster()) {
			printf("A monster has been added to the game...\n");
			monsters = monster_controller.add_monster(monsters, num_monsters);
		}

		if (monster_controller.should_delete_monster(num_monsters)) {
			printf("A monster has been deleted from the game...\n");
			monster_controller.destroy_monster(monsters, num_monsters);
		}
		printf("\nPress Enter to continue...\n");
		printf("Or press Q to quit game.\n");
	}
	*/
	/*
	printf("Allocating Memory...\n");
	MemoryAllocator mem_alloc;
	printf("Now total number of bytes in memory is: %d \n", (int)mem_alloc.mem_free.head->block_size);
	printf("Requesting 12 bytes of memory...\n");
	mem_alloc.alloc_mem((size_t)12);
	printf("Now total number of bytes available is: %d \n", (int)mem_alloc.mem_free.head->block_size);
	printf("\n");
	*/
	
	MemoryAllocator allocator;
	srand((unsigned int)time(NULL));
	printf("\n\n-------------TEST ALLOCATION-------------\n");
	for (int i = 0; i < 10; i++) {
		size_t requested_size = rand() % 100 + 1;
		printf("\nallocating %zu bytes of memory\n", requested_size);
		allocator.alloc_mem(requested_size);
	}
	printf("\n\n>>>>>>memory in use\n");
	printList(allocator.in_use_bd_list);
	printf("\n\n>>>>>>free memory in allocator\n");
	printList(allocator.free_mem_bd_list);

	printf("\n\n-------------TEST FREE-------------\n");
	for (int i = 0; i < 5; i++) {
		size_t requested_size = rand() % 100 + 1;
		char *test_ptr = static_cast<char*> (allocator.alloc_mem(requested_size));
		allocator.free_mem(test_ptr);
	}
	printf("\n\n>>>>>>memory in use:\n");
	printList(allocator.in_use_bd_list);
	printf("\n\n>>>>>>free memory in allocator\n");
	printList(allocator.free_mem_bd_list);
	
	printf("\n\n-------------TEST COALESCE-------------\n");
	allocator.coalesce_mem();
	printf("\n\n>>>>>>memory in use:\n");
	printList(allocator.in_use_bd_list);
	printf("\n\n>>>>>>free memory in allocator\n");
	printList(allocator.free_mem_bd_list);

	//MemoryAllocatorTest allocator_test;
	//allocator_test.test_mem_alloc(50);
	//allocator_test.test_free_alloc(50);
	_CrtDumpMemoryLeaks();
	return 0;
}

void printList(BlockDescriptorList list) {
	if (list.head == NULL) {
		return;
	}
	else {
		BlockDescriptor *curr = list.head;
		while (curr != NULL) {
			printf("\nsize of block descriptor is %zu and the memory pointer is %p\n", 
				curr->block_size, curr->block_base_ptr);
			curr = curr->next_bd;
		}
	}
}