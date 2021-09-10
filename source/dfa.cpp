#include "dfa.h"

namespace cppjson {
	namespace dfa {
		dfa buildDFA() {
			dfa d({
				5, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 26
			});

			d.transTable['\"'][0] = 1;
			d.transTable['-'][0] = 2;
			d.transTable['t'][0] = 3;
			d.transTable['f'][0] = 4;
			for(int i = 0; i < 10; i++) d.transTable['0' + i][0] = 5;
			d.transTable['{'][0] = 15;
			d.transTable['}'][0] = 16;
			d.transTable['['][0] = 17;
			d.transTable[']'][0] = 18;
			d.transTable[':'][0] = 19;
			d.transTable[','][0] = 20;
			d.transTable[' '][0] = 21;
			d.transTable['\n'][0] = 21;
			d.transTable['\t'][0] = 21;
			d.transTable['n'][0] = 23;
			
			for(int i = 0; i < 128; i++) d.transTable[i][1] = 1;
			d.transTable['\"'][1] = 11;
			
			for(int i = 0; i < 10; i++) d.transTable['0' + i][2] = 5;
			
			d.transTable['r'][3] = 6;
			
			d.transTable['a'][4] = 7;
			
			for(int i = 0; i < 10; i++) d.transTable['0' + i][5] = 5;
			d.transTable['.'][5] = 22;
			
			d.transTable['u'][6] = 8;
			
			d.transTable['l'][7] = 9;
			
			d.transTable['e'][8] = 13;
			
			d.transTable['s'][9] = 10;
			
			d.transTable['e'][10] = 14;
			
			for(int i = 0; i < 10; i++) d.transTable['0' + i][22] = 22;
			
			d.transTable['u'][23] = 24;
			d.transTable['l'][24] = 25;
			d.transTable['l'][25] = 26;
			
			return d;
		}
	}
}
