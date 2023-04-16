/*
    Demonstration with a multi-line, plaintext input.
*/
#include <unistd.h> // Supports optarg()

#include "markov.hpp"

int main(int argc, char * argv[])
{

    //
    std::string inputFileName { "" }, outputFileName { "" }, startToken { "" };

    int opt;

    while ((opt = getopt(argc, argv, "hi:o:t:")) != -1)
    {

        switch (opt)
        {
            case 'i':
                if (optarg == NULL)
                {
                    std::cerr << argv[0] << " flag: -i expected arg.\n" << std::endl;
                    return 1;
                }
                inputFileName = std::string(optarg);
                break;

            case 'o':
                if (optarg == NULL)
                {
                    std::cerr << argv[0] << " flag: -o expected arg.\n" << std::endl;
                    return 1;
                }
                outputFileName = std::string(optarg);
                break;

            case 't':
                if (optarg == NULL)
                {
                    std::cerr << argv[0] << " flag: -t expected arg.\n" << std::endl;
                    return 1;
                }
                startToken = std::string(optarg);
                break;

            default:
                std::cerr << argv[0] << " flag: -" << ( isalnum(opt) ? static_cast<char>(opt) : '?' ) << " undefined\n" << std::endl;
                
            case 'h':
                std::cout << argv[0] << " usage:\n";
                std::cout << "\t\t-h\t\thelp\n";
                std::cout << "\t\t-i \"inp.file\"\tinput file, source, corpus, etc.\n";
                std::cout << "\t\t-o \"out.file\"\tgenerated chain output file\n";
                std::cout << "\t\t-t \"token\tstart token for generated chain\n";
                std::cout << std::endl;
                return 1;
        }

    }

    if (inputFileName.empty())
    {
        if (outputFileName.empty() == false)
        {
            std::cerr << argv[0] << " specified output: " << outputFileName << " but no input arg.\n" << std::endl;
            return 1;
        }

        if (argc != 2)
        {
            std::cerr << argv[0] << " expects an input file arg. (run with -h)\n" << std::endl;
            return 1;
        }

        inputFileName = std::string(argv[1]);
    }

    std::fstream f;
    
    f.open(inputFileName.c_str(), std::ios::in);

    if (f.is_open() == false)
    {
        std::cout << argv[0] << " input error:\tfailed to open \"" << inputFileName << "\"\n" << std::endl;
        return 1;
    }

    std::string line;

    auto generator = new markov::ChainGenerator<std::string>();

    while (f.peek() != EOF)
    {
        getline(f, line);

        generator->feed(line);
    }

    // Returns a chain starting from set member that matches input (case A).
    // Passing a seed state that is not present in the set (case B) will 
    // return a singleton state chain that contains only the seed value as
    // a terminal state (no branch states or recurrence). Passing no argument
    // returns a Markov Chain from a random state guarenteed to exist within
    // the state set, or an empty chain for an empty set (case C).
    
    /*(A)*/ //auto chain = gen->generate("the");
    /*(B)*/ //auto chain = gen->generate("_not_in_set_");
    /*(C)*/ //auto chain = generator->generate();

    std::vector<markov::State<std::string> *> chain;

    if (startToken.empty())
    {
        chain = generator->generate();
    }
    else 
    {
        chain = generator->generate(startToken);
    }

    std::cout << "----\n";

    for (auto &state : chain)
    {
        std::cout << state->value << " ";
    }

    std::cout << "\n----" << std::endl;

    return 0;

}