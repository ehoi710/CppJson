#ifndef __DFA__
#define __DFA__

namespace dfa {
	class dfa {
	public:
		dfa(std::vector<int> final_state) {
			for(int j = 0; j < 128; j++) {
				for(int i = 0; i < 32; i++) {
					this->transTable[j][i] = -1;
				}
			}

			this->final_state = final_state;
		}

		void addTransit(int state, char in, int res) {
			transTable[in][state] = res;
		}

		int trans(int state, char in) {
			return transTable[in][state];
		}

		int isFinal(int state) {
			return std::find(final_state.begin(), final_state.end(), state) != 
				final_state.end();
		}

	private:
		int transTable[128][32];
		std::vector<int> final_state;
	};
	
	
	dfa buildDFA();
}

#endif
