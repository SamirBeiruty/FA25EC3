//
// Created by Manju Muralidharan on 11/22/25.
//

//
// Created by Manju Muralidharan on 11/22/25.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "tree.h"
using namespace std;

/*
   Students:
   You will complete the Tree template class.
   main.cpp already:
   1. Runs curl to fetch a story from OpenAI.
   2. Saves output to story.txt.
   3. Parses story.txt into structured nodes.
   4. Calls your Tree methods to build a dynamic tree.

   You must NOT modify this file.
*/

// Structure for raw parsed nodes
struct StoryNodeRaw {
    string id;
    string text;
    vector<string> children;
};

// Step 1. Call OpenAI with curl
string runCurlToOpenAI(const string &apiKey) {
    string command =
        "curl https://api.openai.com/v1/responses "
        "-H \"Content-Type: application/json\" "
        "-H \"Authorization: Bearer " + apiKey + "\" "
        "-d '{"
        "\"model\": \"gpt-4.1-mini\","
        "\"input\": \"Generate a choose-your-own-adventure story as a structured list of nodes. "
        "Each node must have: NODE_ID, NODE_TEXT, CHILD_IDS as a comma-separated list. "
        "Limit to 2 nodes. The format must be strictly: "
        "[NODE_ID] TEXT: ... NEXT: child1, child2, ... "
        "No extra commentary.\""
        "}' "
        " > story.txt";

    cout << "Fetching story from OpenAI..." << endl;
    system(command.c_str());
    return "story.txt";
}

// Step 2. Parse the story file
vector<StoryNodeRaw> parseStoryFile(const string &filename) {
    ifstream fin(filename);
    vector<StoryNodeRaw> nodes;

    if (!fin.is_open()) {
        cerr << "Could not open story file." << endl;
        return nodes;
    }

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        StoryNodeRaw node;

        size_t idStart = line.find('[');
        size_t idEnd = line.find(']');
        if (idStart == string::npos || idEnd == string::npos) continue;

        node.id = line.substr(idStart + 1, idEnd - idStart - 1);

        size_t textPos = line.find("TEXT:");
        size_t nextPos = line.find("NEXT:");
        if (textPos == string::npos || nextPos == string::npos) continue;

        string textPart = line.substr(textPos + 5, nextPos - (textPos + 5));
        node.text = textPart;

        string nextPart = line.substr(nextPos + 5);
        stringstream ss(nextPart);
        string temp;
        while (getline(ss, temp, ',')) {
            while (!temp.empty() && temp.front() == ' ') temp.erase(0, 1);
            if (!temp.empty()) node.children.push_back(temp);
        }

        nodes.push_back(node);
    }

    return nodes;
}

// Main Program
int main() {
    cout << "Enter your OpenAI API key: ";
    string apiKey;
    getline(cin, apiKey);

    string filename = runCurlToOpenAI(apiKey);

    vector<StoryNodeRaw> rawNodes = parseStoryFile(filename);
    if (rawNodes.empty()) {
        cerr << "Story was empty or invalid." << endl;
        return 1;
    }

    Tree<string> adventureTree;

    adventureTree.createRoot(rawNodes[0].id, rawNodes[0].text);

    for (const StoryNodeRaw &node : rawNodes) {
        for (const string &childID : node.children) {
            string childText;
            for (const StoryNodeRaw &n : rawNodes) {
                if (n.id == childID) {
                    childText = n.text;
                    break;
                }
            }
            adventureTree.addNode(node.id, childID, childText);
        }
    }

    cout << "Story loaded into your dynamic tree structure." << endl;

    adventureTree.printAll();
    adventureTree.playGame();
    return 0;
}