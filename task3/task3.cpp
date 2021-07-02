//the solution uses prefix tree
struct Node
{
	Node* next[26];
	string key;
	bool terminal;
	bool unambiguous;

	Node()
	{
		terminal = false;
		unambiguous = true;
		for (int i = 0; i < 26; i++)
			next[i] = nullptr;
	}
};

string checkWord(string word, int& sum, int& readLength, Node* root);
Node* searchKey(string key, Node *node);
void addKey(string key, Node* node);

int main()
{
	int n, sum = 0, readLength = 0;
	string checkRes;
	cin >> n;

	Node* root = new Node();

	string* words = new string[n];
	for (int i = 0; i < n; i++)
		cin >> words[i];

	for (int i = 0; i < n; i++) {
		readLength = 0;
		checkRes = checkWord(words[i], sum, readLength, root);
		if (!checkRes.empty()) {
			if (checkRes == words[i])
				continue;
			else {
				sum += (words[i].size() - readLength);
				addKey(words[i], root);
			}
		}
		else {
			addKey(words[i], root);
		}
	}
	cout << sum;
	delete Node;
	return 0;
}

string checkWord(string word, int& sum, int& readLength, Node* root)
{
	string key;
	Node* searchRes = nullptr;
	for (unsigned int i = 0; i < word.size(); i++)
	{
		key.push_back(word[i]);
		readLength++;
		sum++;
		searchRes = searchKey(key, root);
		if (searchRes == nullptr) {
			continue;
		}
		else if (searchRes->unambiguous){
			return searchRes->key;
		}
	}
	return "";
}

Node* searchKey(string key, Node* node)
{
	unsigned int end = key.size();
	Node* curNode = node;

	for (unsigned int i = 0; i <= end; i++)
	{
		if (i == end) {
			if (curNode->unambiguous) return curNode;
			else return nullptr;
		}

		if (curNode->next[key[i] - 'a'] != nullptr) {
			curNode = curNode->next[key[i] - 'a'];
		}
		else return nullptr;
	}
	return nullptr;
}

void addKey(string key, Node* node)
{
	unsigned int end = key.size();
	Node* curNode = node;

	for (unsigned int i = 0; i <= end; i++)
	{
		if (i == end) {
			curNode->key = key;
			curNode->terminal = true;
			return;
		}

		if (curNode->next[key[i] - 'a'] != nullptr) {
			curNode = curNode->next[key[i] - 'a'];
			//curNode->terminal = false;
			curNode->unambiguous = false;
			curNode->key.clear();
		}
		else {
			Node* newNode = new Node();
			curNode->next[key[i] - 'a'] = newNode;
			newNode->key = key;
			curNode = newNode;
		}
	}
}
