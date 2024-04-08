#include <iostream>
#include<fstream>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;
struct node {
	int freq;
	char c;
	node* l;
	node* r;
};
class compare {
public:
	int operator()(node* f, node* s) {
		return f->freq > s->freq;
}
};
void encode(node* t,string str, unordered_map<char, string>& cs) {
	
	if (t == NULL)
		return;
	else {
		if (t->l == NULL && t->r == NULL) {
			cs[t->c] = str;
		}
		encode(t->l, str + "0", cs);
		encode(t->r, str + "1", cs);
	
	}
	
}
void Huffman(string& text, unordered_map<char, string>& cs, unordered_map<char, int>& cf,priority_queue<node*,vector<node*>,compare>&pq) {
	for (auto it:cf) {
		node* t = new node;
		t->c = it.first;
		t->freq = it.second;
		t->l = NULL;
		t->r = NULL;
		pq.push(t);
	}
	while (pq.size() > 1) {
		node* temp1 = pq.top();
		pq.pop();
		node* temp2 = pq.top();
		pq.pop();
		node* t = new node;
		t->c = '\0';
	t->freq = temp1->freq + temp2->freq;
		t->l = temp1;
		t->r = temp2;
		pq.push(t);
	}
	node* root = pq.top();
	encode(root,"", cs);
}
int main()
{ 
	priority_queue<node*, vector<node*>, compare> pq; //minheap
	string text = "";
	string encdoded;
	unordered_map<char, string>cs; //bit pattern
	unordered_map<char, int>cf; // freq
	ifstream File("data.txt");
	if (File.is_open()) {
		char c;
		while (File.get(c)) {
			text += c;
			cf[c]++;
		}
		/*	for (auto it : cf) {
				cout << it.first << "   " << it.second << endl;
			}
		*/
		cout << "Text was: \n"<<text << endl<<endl;
		int l = text.size();
		Huffman(text, cs, cf,pq);
		string str = "";
		for (int i = 0; i < l; i++) {
			str += cs[text[i]];
		}
		cout << "Encoded String: \n" << str << endl << endl;
		cout << "Decoded String: \n";
		node* temp = pq.top();
		int i = 0;
		while (i<str.size()) {
			if (str[i] == '0') {
				temp = temp->l;
			}
			else {
				temp = temp->r;
			}
			if (temp->c != '\0') {
				cout << temp->c;
				temp = pq.top();
			}
			i++;
		}
		cout << endl;
		File.close();
	}
	else {
		cout << "Couldn't open file!" << endl;
	}

	return 0;
	/*
	priority_queue<node*,vector<node*>,compare> pp;
	node* t = new node;
	t->c = 'a';
	t->freq = 23;
	t->l = NULL;
	t->r = NULL;
	pp.push(t);
	node* o = new node;
	o->c = 'd';
	o->freq = 2;
	o->l = NULL;
	o->r = NULL;
	pp.push(o);
	while (!pp.empty()) {
		node* temp = pp.top();
		cout << temp->c << "  " << temp->freq << endl;
		pp.pop();
	}
	*/
}