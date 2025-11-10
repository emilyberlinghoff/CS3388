def decode(message_file):
    # Read the contents of the file
    with open(message_file, 'r') as file:
        lines = file.readlines()

    # Extract the numbers from each line
    numbers = [int(line.split()[0]) for line in lines]

    # Filter the words based on the extracted numbers
    words = [line.split()[1] for i, line in enumerate(lines) if i + 1 in numbers]

    # Join the words into a string and return
    decoded_message = ' '.join(words)
    return decoded_message

# Example usage
message_file = 'coding_qual_input.txt'  # Replace with the actual file path
decoded_message = decode(message_file)
print(decoded_message)