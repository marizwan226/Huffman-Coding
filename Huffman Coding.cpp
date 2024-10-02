#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

// Structure to represent a node in the Huffman tree
struct Node {
    char character;
    int frequency;
    Node* left;
    Node* right;
};

// Comparison function for the priority queue
struct Compare {
    bool operator()(const Node* a, const Node* b) {
        return a->frequency > b->frequency;
    }
};

// Function to build the Huffman tree
Node* buildHuffmanTree(int frequencies[], char characters[], int size) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // Create a leaf node for each character and add it to the min heap
    for (int i = 0; i < size; i++) {
        Node* newNode = new Node();
        newNode->character = characters[i];
        newNode->frequency = frequencies[i];
        newNode->left = newNode->right = nullptr;
        minHeap.push(newNode);
    }

    // Build the Huffman tree
    while (minHeap.size() != 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        Node* internalNode = new Node();
        internalNode->frequency = left->frequency + right->frequency;
        internalNode->left = left;
        internalNode->right = right;

        minHeap.push(internalNode);
    }

    return minHeap.top();
}

// Function to print the Huffman codes
void printHuffmanCodes(Node* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (root == nullptr) {
        return;
    }

    if (root->left == nullptr && root->right == nullptr) {
        huffmanCodes[root->character] = code;
    }

    printHuffmanCodes(root->left, code + "0", huffmanCodes);
    printHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Function to print the Huffman codes in preorder traversal
void printHuffmanCodesPreorder(Node* root, string code) {
    if (root == nullptr) {
        return;
    }

    if (root->left == nullptr && root->right == nullptr) {
        cout << code << " ";
    }

    printHuffmanCodesPreorder(root->left, code + "0");
    printHuffmanCodesPreorder(root->right, code + "1");
}

int main() {
    char characters[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int frequencies[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(frequencies) / sizeof(frequencies[0]);

    Node* root = buildHuffmanTree(frequencies, characters, size);

    cout << "Huffman codes in preorder traversal: ";
    printHuffmanCodesPreorder(root, "");

    unordered_map<char, string> huffmanCodes;
    printHuffmanCodes(root, "", huffmanCodes);

    cout << "\nHuffman codes:" << endl;
    for (auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}