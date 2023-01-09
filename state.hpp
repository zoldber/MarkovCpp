#pragma once

namespace markov {
    template <typename stateType>
    class State {

        public:

            stateType value;

            std::unordered_map<stateType, State *> nextStates;

            // Note: frequency is not a property of an instance of a State class.
            // States might become large, and are allocated once before being stored
            // in this->stateSet to prevent redundant allocation. Instead, it's a figure
            // that varies depending on the state that is pointing to it.
            // E.g. for an input state sequence A-B-A-A-C-A-B-A : 
            // B->nextStates[A].freq() = 2 != C->nextStates[A].freq() = 1
            //
            // It's viable to do it the other way, and at first glance might seem
            // desirable, but in practice this is the least convoluted approach.
            std::unordered_map<stateType, size_t> nextStateFrequencies;

            // These constructors should only be called within checkInSet(), hence, any
            // instance of "new State()" outside of this method is unprotected.
            State(void) {

                this->nextStates = {};

                this->nextStateFrequencies = {};

            }

            State(stateType value) {

                this->value = value;

                this->nextStates = {};

                this->nextStateFrequencies = {};

            }

            /*
            ~State(void) {

                // Each instance of a State is allocated once and stored in the 'stateSet' member of the MarkovChain class.
                // Deleting each State pointer via MarkovChain.stateSet is sufficient for the current implementation.

            }
            */

            bool hasNextState(stateType value) {

                return (nextStates.find(value) != nextStates.end());

            }

    };
}