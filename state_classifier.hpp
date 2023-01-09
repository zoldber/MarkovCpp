#include "state.hpp"

namespace markov {

    template <class stateType>
    class StateClassifier {

        public:

            StateClassifier(void);

            ~StateClassifier(void);

            // These can always be evaluated using Markov Chain decomposition and pointer value alone.
            bool isTransient(State<stateType> * state);
            bool isRecurrent(State<stateType> * state);

            // The same cannot be said for this.
            bool isTerminal(State<stateType> * state);


    };

    template <class stateType>
    StateClassifier<stateType>::StateClassifier(void) {

        return;

    }

    template <class stateType>
    StateClassifier<stateType>::~StateClassifier(void) {

        return;

    }

    // Method "isTerminal()" deliberates on specific state attributes that indicate finality.
    // As a simple example, given input: "I run . I sleep !", the token "." does not denote
    // the end of the input sequence, and instead becomes a state with nonempty nextStates.
    // In practice, attributes extend beyond the state's value, hence the template overloading.
    template < >
    bool StateClassifier<std::string>::isTerminal(State<std::string> * state) { 

        if (state->nextStates.size()) {
            // See example above.
            return (state->value.back() == '.' || state->value.back() == '!' || state->value.back() == '?');
        }

        return true;

    }

    template < >
    bool StateClassifier<long int>::isTerminal(State<long int> * state) {

        if (state->nextStates.size()) {
            // Arbitrary place-holder condition.
            return (state->value < 0);
        }

        return true;

    }
    
    template <typename stateType>
    bool StateClassifier<stateType>::isTransient(State<stateType> * state) {

        if (state->nextStates.size()) {

            // Can be transient, do expensive checks:
            // ...

            return true;

        }

        return false;

    }

    template <typename stateType>
    bool StateClassifier<stateType>::isRecurrent(State<stateType> * state) {

        if (state->nextStates.size()) {

            // Can be recurrent, do expensive checks:
            // ...

            return true;

        }

        return false;
    }

}