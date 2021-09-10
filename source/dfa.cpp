#include <vector>
#include <algorithm>

#include "dfa.h"

namespace dfa {
	dfa buildDFA() {
		dfa json_dfa({
			5, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 26
		});
		
		json_dfa.addTransit(0, '\"', 1);
		json_dfa.addTransit(0, '-', 2);
		json_dfa.addTransit(0, 't', 3);
		json_dfa.addTransit(0, 'f', 4);
		json_dfa.addTransit(0, '0', 12);
		for(int i = 0; i < 10; i++) json_dfa.addTransit(0, '0'+i, 5);
		json_dfa.addTransit(0, '{', 15);
		json_dfa.addTransit(0, '}', 16);
		json_dfa.addTransit(0, '[', 17);
		json_dfa.addTransit(0, ']', 18);
		json_dfa.addTransit(0, ':', 19);
		json_dfa.addTransit(0, ',', 20);
		json_dfa.addTransit(0, ' ', 21);
		json_dfa.addTransit(0, '\n', 21);
		json_dfa.addTransit(0, '\t', 21);
		json_dfa.addTransit(0, 'n', 23);
		
		for(int i = 0; i < 128; i++) json_dfa.addTransit(1, i, 1);
		json_dfa.addTransit(1, '\"', 11);
		json_dfa.addTransit(1, '\\', 27);
		
		for(int i = 0; i < 10;  i++) json_dfa.addTransit(2, '0'+i, 5);
		
		json_dfa.addTransit(3, 'r', 6);
		
		json_dfa.addTransit(4, 'a', 7);
		
		for(int i = 0; i < 10; i++) json_dfa.addTransit(5, '0'+i, 5);
		json_dfa.addTransit(5, '.', 22);
		
		json_dfa.addTransit(6, 'u', 8);
		
		json_dfa.addTransit(7, 'l', 9);
		
		json_dfa.addTransit(8, 'e', 13);
		
		json_dfa.addTransit(9, 's', 10);
		
		json_dfa.addTransit(10, 'e', 14);
		
		for(int i = 0; i < 10; i++) json_dfa.addTransit(22, '0'+i, 5);
		
		json_dfa.addTransit(23, 'u', 24);
		
		json_dfa.addTransit(24, 'l', 25);
		
		json_dfa.addTransit(25, 'l', 26);
		
		for(int i = 0; i < 128; i++) json_dfa.addTransit(27, i, 1);
		
		return json_dfa;
	}
}
