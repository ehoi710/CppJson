#ifndef __DFA__
#define __DFA__

#include <vector>
#include <algorithm>

namespace cppjson {
	namespace dfa {
		class dfa {
			friend dfa buildDFA();

		public:
			dfa(std::vector<int> final_list) {
				for(int j = 0; j < 128; j++) {
					for(int i = 0; i < 32; i++) {
						this->transTable[j][i] = -1;
					}
				}
				this->final_list = final_list;
			}

			bool isAccepted(int state) {
				return std::find(final_list.begin(), final_list.end(), state) != final_list.end();
			}

			int transition(int state, char input) {
				return transTable[input][state];
			}

		private:
			int transTable[128][32];
			std::vector<int> final_list;
		};

		dfa buildDFA();
	}
}

#endif
