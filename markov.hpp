/*

    This is pretty suboptimal! Dictionary keys point to vectors of strings that are often redundant,
    and the probability of choosing a subsequent word given a key is based entirely on *how*
    redundant the string is in its list. For instance: given key: "walk" and list: {"dog", "home, "home"},
    "home" has a 66.7% chance of selection in the Markov chain while "dog" has 1 - P("home").
    This is a really dumb way to store this but it's very intuitive. The next most intuitive solution
    seems to be storing a dictionary in each dicitonary with word frequency by index key, then determining
    next word through relative frequency.

*/


#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

class MarkovChain {

    private:

        std::string wordA, wordB;

        std::vector<std::string> * v;    //tmp

        std::unordered_map<std::string, std::vector<std::string>*> dict;

    public:

        MarkovChain(const unsigned int sr) {

            wordA = "";
            wordB = "";
            srand(sr);

        }

        ~MarkovChain(void) {

            for (auto x : dict) {

                delete x.second;

            }

            return;

        }

        void feed(std::string input) {

            std::stringstream line(input);

            getline(line, wordA, ' ');

            while (getline(line, wordB, ' ')) {

                // word already exists as a root
                if (dict.find(wordA) != dict.end()) {

                    dict[wordA]->push_back(wordB);

                } else {

                    v = new std::vector<std::string>;

                    v->push_back(wordB);

                    dict[wordA] = v;

                }

                wordA = wordB;

            }

        }

        void printDict(void) {

            int i;

            for (auto x : dict) {

                std::cout << x.first << " -> ";

                for (i = 0; i < x.second->size(); i++) {

                    std::cout << x.second->at(i) << ", ";

                    if (x.second->at(i).back() == '.') std::cout << "<! END TOKEN! >";

                }

                std::cout << std::endl;

            }

        }

        void generate(void) {

            auto itr = dict.begin();
            
            std::advance(itr, rand() % dict.size());

            generate(itr->first);

        }

        void generate(const std::string seed) {

            if (dict.find(seed) == dict.end()) {

                std::cout << "-- failed to find root instance of '" << seed << "' in chain." << std::endl;

                return;

            }

            std::string word = seed;

            unsigned int choice;

            while (word.back() != '.') {

                std::cout << word << " ";

                choice = rand() % dict[word]->size();

                word = dict[word]->at(choice);

            }

            std::cout << word << " <~ [END TOKEN]" << std::endl;

        }

};