import sys

# Global variables
productions = []
first = {}
follow = {}
non_terminals = set()
terminals = set()

# Function to compute FIRST(X)
def compute_first(symbol):
    if symbol in terminals:
        return {symbol}
    
    if symbol in first:
        return first[symbol]
    
    result = set()
    for production in productions:
        head, body = production.split('->')
        head = head.strip()
        body = body.strip()
        
        if head == symbol:
            if body == '':
                result.add('')
            else:
                for char in body:
                    if char == symbol:
                        continue
                    
                    char_first = compute_first(char)
                    result.update(char_first - {''})
                    
                    if '' not in char_first:
                        break
                else:
                    result.add('')
    
    first[symbol] = result
    return result

# Function to compute FOLLOW(X)
def compute_follow(symbol):
    if symbol in follow:
        return follow[symbol]
    
    result = set()
    if symbol == start_symbol:
        result.add('$')
    
    for production in productions:
        head, body = production.split('->')
        head = head.strip()
        body = body.strip()
        
        if symbol in body:
            positions = [i for i, char in enumerate(body) if char == symbol]
            for pos in positions:
                if pos + 1 < len(body):
                    next_char = body[pos + 1]
                    next_first = compute_first(next_char)
                    result.update(next_first - {''})
                    
                    if '' in next_first:
                        result.update(compute_follow(head))
                else:
                    if head != symbol:
                        result.update(compute_follow(head))
    
    follow[symbol] = result
    return result

# Function to format sets for printing
def format_set(result_set):
    formatted = []
    for item in result_set:
        if item == '':
            formatted.append('ε')  # Represent empty string as ε
        elif item == ' ':
            formatted.append(' ')  # Explicitly represent space
        else:
            formatted.append(item)
    return '{ ' + ', '.join(formatted) + ' }'

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python ff_compute.py <grammar_file> <output_file>")
        sys.exit(1)

    grammar_file = sys.argv[1]
    output_file = sys.argv[2]

    with open(grammar_file, 'r') as file:
        productions = [line.strip() for line in file.readlines() if line.strip()]
    
    for production in productions:
        head, body = production.split('->')
        head = head.strip()
        body = body.strip()
        
        non_terminals.add(head)
        for char in body:
            if char.islower() or char == ' ' or char == '':
                terminals.add(char)
            else:
                non_terminals.add(char)
    
    start_symbol = list(non_terminals)[0]  # Assume the first non-terminal is the start symbol

    # Compute FIRST sets
    for non_terminal in non_terminals:
        compute_first(non_terminal)

    # Compute FOLLOW sets
    for non_terminal in non_terminals:
        compute_follow(non_terminal)

    # Output results
    with open(output_file, 'w') as file:
        file.write("FIRST sets:\n")
        for non_terminal, first_set in first.items():
            file.write(f"FIRST({non_terminal}) = {format_set(first_set)}\n")
        
        file.write("\nFOLLOW sets:\n")
        for non_terminal, follow_set in follow.items():
            file.write(f"FOLLOW({non_terminal}) = {format_set(follow_set)}\n")
