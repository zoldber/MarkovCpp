#include <random>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

#include "state.hpp"
#include "state_classifier.hpp"

// The distribution index type should be signed for the new chooseNext() routine, but
// integer width is non-critical so long as it's fixed globally (avoid int_fastxx_t). 
typedef int32_t dist_idx_t;

// C++11 STL documentation outlines trade-offs in speed and uniformity of distribution
// for various generators and seed sources. This is fairly a generic implementation that
// doesn't favor any specific qualities. 
using engine = std::mt19937;
using distribution = std::uniform_int_distribution<int32_t>;



namespace markov {

    template <typename stateType>
    class ChainGenerator {

        private:

            // Implemented as a distinct class to support more robust classificaiton methods. Currently,
            // a state is said to be unique (and thus allocated in stateSet) on the basis of its value 
            // (i.e. its tag by which its parent map is queried) alone. This might (and likely will) change.
            // Likewise, the finality of a state is not solely dependant upon the emptiness of nextStates. 
            StateClassifier<stateType> * classifier;

            // States are allocated once and passed by refrence to support larger collections of attributes.
            // One central collection of unique* states, i.e. the 'set', exists to avoid redundant allocation,
            // and is implemented as a dummy State below (no value, all nextState choices are root states).
            State<stateType> * stateSet;

            engine rng;

        public:

            ChainGenerator(void) {

                // Consider fetching this default seed via os call.
                seedPRNG(time(0));

                this->stateSet = new State<stateType>();

                this->classifier = new StateClassifier<stateType>();

            }

            ~ChainGenerator(void) {

                delete this->stateSet;

                return;

            }

            void seedPRNG(size_t seed) {

                this->rng = engine(seed);

                return;

            }

            bool contains(stateType value) {

                return this->stateSet->hasNextState(value);

            }

            // Old method: stack probabilities by summing frequencies.
            //      given states A, B, C, D and the following frequencies:
            //      1) (A, 1) (B, 3) (C, 2) (D, 7)
            //      2) cumulatively sum by previous from A to D
            //      3) (A, 1) (B, 4) (C, 6) (D, 13)
            //      4) calculate a random value, x between 0 and last state freq (sum of all)
            //      5) find corresponding state for x
            //      6) revert frequency counts by subtracting in same fashion as step 2
            //
            // Current method: no modification of frequency maps needed.
            //      given sum of all frequencies, sum: x = random | { 0 <= random < sum }
            //
            //      for each state in nextStates {
            //          x -= nextStateFrequencies[state];
            //          if (x < 0) return state;
            //      }
            //      
            //      return default
            //
            State<stateType> * chooseNext(State<stateType> * current) {

                if (classifier->isTerminal(current)) {
                
                    return nullptr;
                
                }

                // Calculate this immediately after verifying state is non-terminal and choices
                // exist, then use as default return value when a nullptr is not stricty required.
                auto firstState = std::begin(current->nextStates);

                // Skip computation for singleton state choice.
                if (current->nextStates.size() == 1) {

                    return firstState->second;

                }

                // Don't use size_t or any unsigned integer variant for this implementation.
                int32_t x = 0;

                for (auto state : current->nextStates) {

                    x += current->nextStateFrequencies[state.first];

                }

                // Not really possible here, but included to be safe.
                if (x == 0) return nullptr;

                distribution dist(0, x);        

                x = dist(this->rng);

                for (auto state : current->nextStates) {

                    x -= current->nextStateFrequencies[state.first];

                    if (x <= 0) return state.second;

                }

                return firstState->second;
                
            }

            // New states will only be allocated for insertion in macro state set, which exists as a
            // member of this class to avoid redundant allocation. This streamlines checks in feed()
            State<stateType> * checkInSet(stateType value) {

                if (!this->stateSet->hasNextState(value)) {
                    this->stateSet->nextStates[value] = new State<stateType>(value);
                }

                return this->stateSet->nextStates[value];

            }

            void feed(std::string input) {

                std::stringstream line(input);

                std::string token;

                State<std::string> * currentState;

                getline(line, token, ' ');

                currentState = checkInSet(token);
                this->stateSet->nextStateFrequencies[token] += 1;

                while (getline(line, token, ' ')) {

                    if (!currentState->hasNextState(token)) {
                        currentState->nextStates[token] = checkInSet(token);
                        currentState->nextStateFrequencies[token] = 0;
                    }

                    currentState->nextStateFrequencies[token] += 1;

                    // Assign current state rover to next token, and so on.
                    currentState = currentState->nextStates[token];
                    
                }

                return;

            }

            std::vector<State<stateType> *> generateLen(const uint32_t maxLength) {

                auto startingState = chooseNext(this->stateSet);

                return generateLen(startingState->value, maxLength);

            }

            std::vector<State<stateType> *> generateLen(const stateType seed, const uint32_t maxLength) {

                std::vector<State<stateType> *> chain;

                State<stateType> * state = checkInSet(seed);

                for (uint32_t i = 0; (i < maxLength) && (state != nullptr); i++) {

                    chain.push_back(state);

                    state = chooseNext(state);

                }

                return chain;

            }

            std::vector<State<stateType> *> generate(void) {

                auto startingState = chooseNext(this->stateSet);

                return generate(startingState->value);

            }

            std::vector<State<stateType> *> generate(const stateType seed) {

                std::vector<State<stateType> *> chain;

                State<stateType> * state = checkInSet(seed);

                while (state != nullptr) {

                    chain.push_back(state);

                    state = chooseNext(state);

                }

                return chain;

            }

    };

}