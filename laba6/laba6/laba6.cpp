#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <Windows.h>

using namespace std;

struct Node
{
    string symbols;
    int freq;
    Node* left;
    Node* right;

    Node(string symbols, int freq) {
        left = right = NULL;
        this->freq = freq;
        this->symbols = symbols;
    }

    Node(int freq, Node* left, Node* right) {
        this->freq = freq;
        this->left = left;
        this->right = right;
        this->symbols = left->symbols + right->symbols;
    }
};

struct Compare
{
    bool operator()(Node* l, Node* r) {
        if (l->freq == r->freq) {
            return l->symbols < r->symbols;
        }
        return l->freq > r->freq;
    }
};

void generateCodes(Node* root, string code, map<char, string>& huffmanCode)
{
    if (!root)
        return;
    if (!root->left && !root->right)
    {
        huffmanCode[root->symbols[0]] = code;
    }
    generateCodes(root->left, code + "1", huffmanCode);
    generateCodes(root->right, code + "0", huffmanCode);
}

map<char, string> createHuffmanCodes(map<char, int>& freqTable, Node*& root)
{
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& pair : freqTable)
    {
        pq.push(new Node(string(1, pair.first), pair.second));
    }
    while (pq.size() != 1)
    {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        int sum = left->freq + right->freq;
        pq.push(new Node(sum, left, right));
    }
    root = pq.top();
    map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);
    return huffmanCode;
}

string decodeString(Node* root, const string& encodedString)
{
    string decodedString = "";
    Node* current = root;
    for (char bit : encodedString) {
        if (bit == '1') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        if (!current->left && !current->right) {
            decodedString += current->symbols;
            current = root;
        }
    }
    return decodedString;
}

void printFrequencyTable(const map<char, int>& freqTable)
{
    cout << "Таблица встречаемости символов:" << endl;
    for (auto& pair : freqTable) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

void printHuffmanCodes(const map<char, string>& huffmanCodes)
{
    cout << endl << "Таблица кодов Хаффмана:" << endl;
    for (auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

void huffmanEncodingDecoding(string& str)
{
    map<char, int> freqTable;
    for (char ch : str) {
        freqTable[ch]++;
    }
    Node* root = NULL;
    map<char, string> huffmanCodes = createHuffmanCodes(freqTable, root);
    printFrequencyTable(freqTable);
    printHuffmanCodes(huffmanCodes);
    string encodedString;
    for (char ch : str) {
        encodedString += huffmanCodes[ch];
    }
    cout << endl << "Закодированная строка: " << encodedString << endl;
    string decodedString = decodeString(root, encodedString);
    cout << "Декодированная строка: " << decodedString << endl;
}

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string str;
    cout << "Введите строку: ";
    getline(cin, str);
    huffmanEncodingDecoding(str); 
    return 0;
}
