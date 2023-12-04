from queue import PriorityQueue
from collections import defaultdict

class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

def generate_huffman_codes(characters, frequencies):
    def build_tree(characters, frequencies):
        nodes = [Node(char, freq) for char, freq in zip(characters, frequencies)]
        q = PriorityQueue()
        for node in nodes:
            q.put((node.freq, id(node), node))

        while q.qsize() > 1:
            _, _, left = q.get()
            _, _, right = q.get()
            new_node = Node('$', left.freq + right.freq)
            new_node.left = left
            new_node.right = right
            q.put((new_node.freq, id(new_node), new_node))

        return q.get()[2]

    def generate_codes(node, code, huffman_codes):
        if node:
            if node.char != '$':
                huffman_codes[node.char] = code
            generate_codes(node.left, code + '0', huffman_codes)
            generate_codes(node.right, code + '1', huffman_codes)

    root = build_tree(characters, frequencies)
    huffman_codes = {}
    generate_codes(root, '', huffman_codes)
    return huffman_codes

def main():
    characters = ['a', 'b', 'c', 'd', 'e', 'f']
    frequencies = [5, 9, 12, 13, 16, 45]
    codes = generate_huffman_codes(characters, frequencies)
    print("\nHuffman Codes:")
    for char, code in codes.items():
        print(f"{char}: {code}")

if __name__ == "__main__":
    main()