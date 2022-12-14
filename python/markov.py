import random


class ChainGenerator:

    corpus = []

    dictionary = {}

    terminal_list = ['.', '!']

    drop_list = ['\n', ';', ',']

    def __init__(self, file_name):

        # Fetch words from sentences in a text file, where '.' denotes EOL
        # (preferably sentences with similar structure and subject-matter)
        with open(file_name, 'r') as textFile:
            for line in textFile:

                token = ''.join(char for char in line if char not in self.drop_list)

                self.corpus.append(token)

        for line in self.corpus:

            line = line.lower().split(' ')

            for (i, word) in enumerate(line[:-1]):

                nxt = line[i + 1]

                if word not in self.dictionary.keys():
                    self.dictionary[word] = []

                self.dictionary[word].append(nxt)

    def generate(self, seed=None, forced_features=[]):

        seed = seed.lower()

        word = seed if seed in self.dictionary else random.choice(list(self.dictionary.keys()))

        chain = []

        while '.' not in word:

            chain.append(word)

            # Choose subsequent word based on remaining members of forced_features,
            # or probabilistically (i.e. normally) if no overlap between list + choices

            common = None

            for keyword in forced_features:
                if keyword in list(self.dictionary[word]):
                    common = keyword
                    forced_features.remove(keyword)
                    break

            word = common if common else random.choice(list(self.dictionary[word]))

        # Append final word (containing terminal char)
        chain.append(word)

        return chain
