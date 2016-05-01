import string


start_symbol = ''


def get_grammar_info():
    productions_alternatives = {}
    productions = []
    with open('input.txt', 'r') as grammar_input:
        line_nr = 0
        for line in grammar_input:
            if line_nr == 0:
                global start_symbol
                start_symbol = line[0]
            line = line.replace('\n', '')
            prod = line.split('->')
            left = prod[0].strip(" " + string.punctuation)
            alternatives = prod[1].split('|')
            for alter in alternatives:
                alter = alter.replace(' ', '')
                productions += [(left, alter)]
                if left not in productions_alternatives:
                    productions_alternatives[left] = [alter]
                else:
                    productions_alternatives[left] += [alter]
            line_nr += 1
    grammar_input.close()
    nonterminals = productions_alternatives.keys()
    terminals = ""
    for prod in productions:
        right_side = prod[1]
        right_side = right_side.translate(None, string.uppercase)
        right_side = right_side.replace(' ', '')
        terminals += right_side
    terminals = list(set(terminals))
    terminals += ['$']
    info = {'terminals': terminals,
            'nonterminals': nonterminals,
            'productions': productions,
            'productions_alternatives': productions_alternatives
           }
    return info

def apply_rules(grammar, config, word, word_length):
    print config
    if config[0] == 'q':
        if config[1] != word_length or config[3] != '$':
            sentential_form = config[3]
            if sentential_form[0] in grammar['nonterminals']: #regula 1
                print '>>>>>>> Regula 1'
                nonterminal = sentential_form[0]
                second = config[2] + nonterminal + '0'
                gamma = grammar['productions_alternatives'][nonterminal][0]
                third = gamma + config[3][1:]
                config = (config[0], config[1], second, third)
            elif sentential_form[0] in grammar['terminals']:
                terminal = sentential_form[0]
                if (config[1] < len(word) and terminal != word[config[1]]): #regula 3
                    config = ('r', config[1], config[2], config[3])
                    print '>>>>>>> Regula 3'
                elif config[1] < word_length and terminal == word[config[1]]: #regula 2
                    print '>>>>>>> Regula 2'
                    first = config[1] + 1
                    second = config[2] + terminal
                    third = config[3][1:]
                    config = (config[0], first, second, third)
        else:
            print '>>>>>>> Regula 4'
            config = ('t', config[1], config[2], config[3])
    elif config[0] == 'r':
        alternative = config[2]
        if alternative[-1] in grammar['terminals']: #regula 5
            print '>>>>>>> Regula 5'
            first = config[1] - 1
            second = config[2][:len(config[2]) - 1]
            third = alternative[-1] + config[3]
            config = (config[0], first, second, third)
        elif alternative[-1] in string.digits:
            pos = 0
            nonterminal = ""
            for ch in alternative[::-1]:
                if ch.isupper():
                    nonterminal = ch
                    break
            pos = alternative.rindex(nonterminal)
            number = int(alternative[pos + 1:])
            prod = grammar['productions_alternatives'][nonterminal][number]
            if number + 1 < len(grammar['productions_alternatives'][nonterminal]): #regula 6a
                print '>>>>>>> Regula 6a'
                second = config[2][:pos] + nonterminal + str(number + 1)
                new_prod = grammar['productions_alternatives'][nonterminal][number + 1]
                third = new_prod + config[3][len(prod):]
                config = ('q', config[1], second, third)
            elif (config[1] == 0 and nonterminal == start_symbol and
                    number == len(grammar['productions_alternatives'][start_symbol]) - 1): #regula 6b
                print '>>>>>>> Regula 6b'
                print "\nA aparut o eroare."
                print "Cuvantul nu apartine limbajului generat de gramatica!"
                print "Configuratia in care s-a oprit algoritmul este:", config
                first = len(word)
                third = ""
                config = ('e', first, config[2], third)
            else: #regula 6c
                print '>>>>>>> Regula 6c'
                second = config[2][:pos]
                third = config[3][len(prod):]
                third = nonterminal + third
                config = (config[0], config[1], second, third)
    return config

def get_left_analysis(grammar, config):
    analysis = config[2]
    productions_applied = ""
    while analysis:
        if analysis[0].isupper():
            nonterminal = analysis[0]
            analysis = analysis[1:]
            index = ""
            while analysis and analysis[0] in string.digits:
                index += analysis[0]
                analysis = analysis[1:]
            index = int(index)
            production = grammar['productions_alternatives'][nonterminal][index]
            pair = (nonterminal, production)
            productions_applied += str(grammar['productions'].index(pair)) + ' '
        else:
            analysis = analysis[1:]
    return productions_applied

def get_derivation(grammar, left_analysis):
    left_analysis = left_analysis.strip(" " + string.punctuation)
    productions_applied = left_analysis.split(' ')
    derivation = deriv1 = deriv2 = ""
    for prod in productions_applied:
        prod = int(prod)
        pair = grammar['productions'][prod]
        if derivation:
            index = deriv2.index(pair[0])
            deriv1 = deriv2[:index] + pair[1] + deriv2[index + 1:]
            deriv2 = deriv1
            deriv1 += ' -> '
            derivation += deriv1
        else:
            derivation = pair[1]
            deriv2 = derivation
            derivation += ' -> '
    derivation = derivation.strip(" " + string.punctuation)
    return derivation

def top_down_algorithm(word):
    grammar = get_grammar_info()
    word_length = len(word)
    word += "$"
    word = word.replace(' ', '')
    config = ('q', 0, '', start_symbol + '$')
    config2 = ""
    while config[0] != 't':
        config2 = config
        config = apply_rules(grammar, config, word, word_length)
        if config[0] == 'e' or config == config2:
            print "Configuratia in care s-a ajuns este:", config
            break
    if config[0] == 't': #and config[1] == len(word) and config[3] == '$':
        print config
        print "\nCuvantul a fost acceptat de gramatica"

        left_analysis = get_left_analysis(grammar, config)
        print "\nAnaliza stanga a cuvantului este: \n" + left_analysis
        print "\nDerivarea cuvantului este:"
        print start_symbol + ' -> ' + get_derivation(grammar, left_analysis)

if __name__ == '__main__':
    word = raw_input("Enter your word here: ")
    top_down_algorithm(word)
