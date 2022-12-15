# MarkovCpp
## C++ implementation of a Markov Chain generator

## Summary:
This library procedurally generates text given a sample document and (optionally) a seed. 
It's more of a fun experiment in maps and probability distributions than anything.

- - -

A basic Python prototype was written to serve as the simplest possible implementation of a Markov chain generator possible. A dictionary of words is created and for each word therein, a list is created. A subsequent word appearing more times in a list means a higher probability of it being selected when, in the chain-building loop, the following is called with an even probability distribution:

word = dictionary[word].randomFromList()

As an example, for the following corpus, the dictionary below is built, where lower-case letting in all dictionary keys is intentional:

## corpus.txt
```txt
  I have a dog.
  They have a boat.
  Have two pencils.
```

## Chain-Building Dictionary
|Dict. Key | Dict. Pointer  |
|:--------:|:--------------:|
|"i"       | "have"         |
|"have"    | "a", "a", "two"|
|"a"       | "dog", "boat"  |
|"dog"     | "."            |
|"."       | /TERMINATE     |
|"they"    | "have"         |
|"boat"    | "."            |
|"two"     | "pencils"      | 
|"pencils" | "."            |


Using the example above, the following chain might be generated:

they ➔ have ➔ a ➔ dog ➔ /TERMINATE

Note that for key "have", there's a 2/3 chance of selecting "a" as the subsequent word, and a 1/3 chance of selecting "two". In this example, the probability of subsequent word selection is represented with word frequency in the list that's pointed to. This is intuitive but suboptimal for a few obvious reasons.

Word chains (that, ideally, emulate sentences) get more interesting for longer sentences and larger sets of sentences. They also tend to get incoherent unless the sentences are sourced similarly (e.g. each corpus should be a set of quotes, or poems, or bicycle advertisements, etc.).
