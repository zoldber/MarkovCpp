# MarkovCpp
## C++ implementation of a Markov Chain generator

## Summary:
This library procedurally generates text given a sample document and (optionally) a seed. 
It's more of a fun experiment in maps and probability distributions than anything.

- - -

A basic implementation of a Markov Chain generator is outlined below with string as the state type (hence, "word" and "state" are interchangeable in the following description). A set of initial states is created based on input data, and for each state therein, a list of subsequent states is created. A subsequent state appearing more times in a list means a higher probability of it being selected when, in the chain-building loop, the following is called with a normal p distribution:

```c++

//... init. and choose starting state

while (!classifier->isTerminal(currentState)) {

  currentState = chooseNextState(stateSet[currentState.value].nextStates);
  
  chain.push_back(currentState);
  
}

```

As an example, for the following corpus, the dictionary below is built (lower-case lettering and spaced punctuation are intentional):

## corpus.txt
```txt
  i have a dog .
  they have a boat .
  have two pencils .
```

## Chain-Building Dictionary
|State Value | State->nextStates    |
|:----------:|:--------------------:|
|"i"         | "have"(x1)           |
|"have"      | "a"(x2), "two"(x1)   |
|"a"         | "dog"(x1), "boat"(x1)|
|"dog"       | "."(x1)              |
|"."         | <end>                |
|"they"      | "have"(x1)           |
|"boat"      | "."(x1)              |
|"two"       | "pencils"(x1)        | 
|"pencils"   | "."(x1)              |


Using the example above, the following chain might be generated:

    they ➔ have ➔ a ➔ dog ➔ . ➔ <end>

though terminal states (states with a value of "." in this example) need not have an empty state->nextStates list.

Word chains (that, ideally, emulate sentences) get more interesting for longer state sequences and . They also tend to get incoherent unless the sentences are sourced similarly (e.g. each corpus should be a set of quotes, or poems, or advertisements, etc.).
