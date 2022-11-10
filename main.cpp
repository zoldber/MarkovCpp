/*

    Demonstration

*/

#include "markov.hpp"

using namespace std;

int main(int argc, char * argv[]) {

    if (argc != 2) {

        cout << "-- usage: ./markov <filename.txt>" << endl;

        return 1;

    }

    fstream f;
    
    f.open(argv[1], ios::in);

    string line;

    auto chain = new MarkovChain(time(0));

    while (getline(f, line)) chain->feed(line);

    chain->generate("predictions"); //seed phrase not strictly necessary; one will be chosen at random if passed no arg

    delete chain;

    return 0;

}