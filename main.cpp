/*
    Demonstration with a multi-line, plaintext input.
*/

#include "markov.hpp"

using namespace std;

int main(int argc, char * argv[]) {

    if (argc != 2) {

        cout << "-- usage: ./markov plain_text_file" << endl;

        return 1;

    }

    fstream f;
    
    f.open(argv[1], ios::in);

    if (f.is_open() == false) {

        cout << "-- error opening \"" << argv[1] << "\"" << endl;

        return 1;

    }

    string line;

    auto generator = new markov::ChainGenerator<string>();

    while (getline(f, line)) generator->feed(line);

    // Returns a chain starting from set member that matches input (case A).
    // Passing a seed state that is not present in the set (case B) will 
    // return a singleton state chain that contains only the seed value as
    // a terminal state (no branch states or recurrence). Passing no argument
    // returns a Markov Chain from a random state guarenteed to exist within
    // the state set, or an empty chain for an empty set (case C).
    
    /*(A)*/ //auto chain = gen->generate("the");
    /*(B)*/ //auto chain = gen->generate("_not_in_set_");
    /*(C)*/ auto chain = generator->generate();

    for (auto state : chain) {

        std::cout << state->value << " ";

    }

    std::cout << std::endl;

    return 0;

}