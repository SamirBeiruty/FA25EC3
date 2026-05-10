//
// Created by Manju Muralidharan on 11/22/25.
//

#ifndef FA25EC3_TREE_H
#define FA25EC3_TREE_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

template <typename U>
class Node {
public:
    string id;
    U data;
    vector<Node<U>*> children;

    Node(const string &nodeID, const U &value) : id(nodeID), data(value) {}
};

template <typename T>
class Tree {
private:
    Node<T>* root;
    unordered_map<string, Node<T>*> allNodes;

public:
    Tree() : root(nullptr) {}

    void createRoot(const string &id, const T &value) {
        Node<T>* node = new Node<T>(id, value);
        allNodes[id] = node;
        root = node;
    }

    void addNode(const string &parentID, const string &childID, const T &value) {
        Node<T>* parent = findNode(parentID);
        if (!parent) return;

        Node<T>* child;
        if (allNodes.count(childID)) {
            child = allNodes[childID];
        } else {
            child = new Node<T>(childID, value);
            allNodes[childID] = child;
        }
        parent->children.push_back(child);
    }

    Node<T>* findNode(const string &id) {
        auto it = allNodes.find(id);
        if (it != allNodes.end()) return it->second;
        return nullptr;
    }

    void printAll() {
        if (!root) return;
        cout << "\n===== Story Tree =====" << endl;
        for (auto &pair : allNodes) {
            Node<T>* node = pair.second;
            cout << "Node " << node->id << ": " << node->data << endl;
            if (node->children.empty()) {
                cout << "  Child -> (none)" << endl;
            } else {
                for (Node<T>* child : node->children) {
                    cout << "  Child -> " << child->id << endl;
                }
            }
            cout << endl;
        }
        cout << "======================" << endl;
    }

    void playGame() {
        if (!root) return;
        cout << "\n===== Begin Adventure =====" << endl << endl;
        Node<T>* current = root;
        while (true) {
            cout << current->data << endl;
            if (current->children.empty()) {
                cout << "There are no further paths." << endl;
                cout << "Your journey ends here." << endl;
                break;
            }
            cout << "Choose your next action:" << endl;
            for (int i = 0; i < (int)current->children.size(); i++) {
                cout << i + 1 << ". " << current->children[i]->data << endl;
            }
            cout << "Selection: ";
            int choice;
            cin >> choice;
            while (choice < 1 || choice > (int)current->children.size()) {
                cout << "Invalid selection. Try again: ";
                cin >> choice;
            }
            current = current->children[choice - 1];
        }
        cout << "\n===== Adventure Complete =====" << endl;
    }

    ~Tree() {
        for (auto &pair : allNodes) {
            delete pair.second;
        }
        allNodes.clear();
    }
};

#endif //FA25EC3_TREE_H
