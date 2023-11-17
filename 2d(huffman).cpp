#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// Structure to represent a node in the Huffman tree
struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char d, int freq) : data(d), frequency(freq), left(nullptr), right(nullptr) {}
};

// Comparison function for the priority queue
struct CompareNodes {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->frequency > right->frequency;
    }
};

// Function to build the Huffman tree and return the root
HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& frequencies) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> minHeap;

    // Create nodes for each character and add them to the priority queue
    for (const auto& entry : frequencies) {
        minHeap.push(new HuffmanNode(entry.first, entry.second));
    }

    // Build the Huffman tree
    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();

        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* internalNode = new HuffmanNode('$', left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        minHeap.push(internalNode);
    }

    // Return the root of the Huffman tree
    return minHeap.top();
}

// Function to perform a depth-first traversal of the Huffman tree and generate Huffman codes
void generateHuffmanCodes(HuffmanNode* root, const string& currentCode, unordered_map<char, string>& codes) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '$') {
        codes[root->data] = currentCode;
    }

    generateHuffmanCodes(root->left, currentCode + "0", codes);
    generateHuffmanCodes(root->right, currentCode + "1", codes);
}

// Function to encode a message using Huffman codes
string huffmanEncode(const string& message, const unordered_map<char, string>& codes) {
    string encodedMessage = "";
    for (char c : message) {
        encodedMessage += codes.at(c);
    }
    return encodedMessage;
}

int main() {
    string message;
    cout << "Enter a message to encode using Huffman encoding: ";
    getline(cin, message);

    unordered_map<char, int> frequencies;

    // Count the frequency of each character in the input message
    for (char c : message) {
        frequencies[c]++;
    }

    // Build the Huffman tree
    HuffmanNode* root = buildHuffmanTree(frequencies);

    // Generate Huffman codes for each character
    unordered_map<char, string> codes;
    generateHuffmanCodes(root, "", codes);

    // Display Huffman codes
    cout << "\nHuffman Codes:\n";
    for (const auto& entry : codes) {
        cout << entry.first << ": " << entry.second << endl;
    }

    // Encode the message using Huffman codes
    string encodedMessage = huffmanEncode(message, codes);
    cout << "\nEncoded Message: " << encodedMessage << endl;

    return 0;
}