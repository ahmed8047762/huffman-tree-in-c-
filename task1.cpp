#include<iostream>
#include<fstream>			//Library for file handling
#include<string>			//Library of strings
using namespace std;

//#define MAX_TREE_HT 100;
int divider = 0;
int count_size = 0;
int* counter_arr = new int[count_size];
char* respective_char = new char[count_size];
int* respective_freq = new int[count_size];

struct Node					//LinkedList's node
{
	int freq;
	char data;
	Node* next;
	Node()						//Default Constructor
	{
		freq = 1;
		data = 0;
		next = NULL;
	}
};

class LinkedList					//Class of Linked List
{
public:
	Node* first;
	LinkedList()					//Default Constructor
	{
		first = NULL;
	}
	LinkedList(int d, Node* temp)	//Parameterized Constructor
	{
		first->data = d;
		first->next = temp;
	}

	void Insert(char d)		//Insertion function
	{

		if (first == NULL)
		{
			Node* temp = new Node;
			temp->data = d;
			temp->next = NULL;
			first = temp;

		}
		else
		{
			Node* temp = new Node;
			temp->data = d;
			temp->next = first;
			first = temp;
		}
	}
	void Delete()				//Deletion function
	{
		if (first == NULL)
		{
			return;
		}

		Node* temp = first;
		first = first->next;
		delete temp;

	}
	void Check_Character(char d)	//Character checking function
	{
		bool chk = false;
		Node* ptr = first;
		while (ptr != NULL)
		{
			if (ptr->data == d)
			{
				ptr->freq++;
				chk = true;
			}
			ptr = ptr->next;
		}
		if (chk == false && d != ' ') // ' ' is for space
		{
			Insert(d);
		}
	}
	void sort()
	{
		Node* current = first, * index = NULL;
		int ftemp;
		char ctemp;

		if (first == NULL)
		{
			return;
		}
		else
		{
			while (current != NULL)
			{
				index = current->next;
				while (index != NULL)
				{
					if (current->freq >= index->freq)
					{
						ctemp = current->data;
						ftemp = current->freq;
						current->data = index->data;
						current->freq = index->freq;
						index->data = ctemp;
						index->freq = ftemp;
					}
					index = index->next;
				}
				current = current->next;
			}
		}
	}
	void Display()			//Display function
	{
		Node* ptr = first;
		while (ptr != NULL)
		{
			cout << "The Character " << ptr->data << " repeated " << ptr->freq << " times." << endl;
			ptr = ptr->next;
		}
	}
	int sizereturn()
	{
		Node* ptr = first;
		int i = 0;
		while (ptr != NULL)
		{
			i++;
			ptr = ptr->next;
		}
		return i;
	}
};

struct node_of_minheap //structure of a node for minheap
{
	char data;
	int freq;
	node_of_minheap* left, * right;
};

struct min_heap //structure for declares array of (node_of_minheap) type
{
	int size;
	int capacity;

	node_of_minheap** Arra;
};

node_of_minheap* new_node(char data, int freq) //this function creates a new node of (node_of_minheap) type
{
	node_of_minheap* temp = new node_of_minheap;

	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;

	return temp; //address of node s returned here
}

min_heap* creating_minheap(int capa) //this functions an array of minheap type and allocates memory to it
{
	min_heap* mh = new min_heap;

	mh->size = 0;
	mh->capacity = capa;
	mh->Arra = (node_of_minheap**)malloc(mh->capacity * sizeof(node_of_minheap*));

	return mh;
}

void swaping_minheapnode(node_of_minheap** a, node_of_minheap** b) //standard swapping function for swapping two nodes of (node_of_minheap) type 
{
	node_of_minheap* t = *a;
	*a = *b;
	*b = t;
}

void std_minheapify_fnc(min_heap* mh, int indx) //this is a standard minheapify function
{
	int smallest = indx;
	int left = 2 * indx + 1;
	int right = 2 * indx + 2;

	if (left < mh->size && mh->Arra[left]->freq < mh->Arra[smallest]->freq)
	{
		smallest = left;
	}
	if (right < mh->size && mh->Arra[right]->freq < mh->Arra[smallest]->freq)
	{
		smallest = right;
	}
	if (smallest != indx)
	{
		swaping_minheapnode(&mh->Arra[smallest], &mh->Arra[indx]);
		std_minheapify_fnc(mh, smallest);
	}
}

void building_minheap(min_heap* mh) //after a minheap has been created, it minheapifies it
{
	int n = mh->size - 1;
	int i;

	for (i = (n - 1) / 2; i >= 0; --i)
		std_minheapify_fnc(mh, i);
}

int if_size_is_one(min_heap* mh)
{
	return (mh->size == 1);
}

node_of_minheap* extracting_min(min_heap* mh) //extracts the smallest i.e., the node at 0th index of min heap and then heapifies the minheap
{
	node_of_minheap* temp = mh->Arra[0];

	mh->Arra[0] = mh->Arra[mh->size - 1];
	--mh->size;
	std_minheapify_fnc(mh, 0); //here it heapifies the minheap

	return temp;
}

void inserting_in_minheap(min_heap* mh, node_of_minheap* mhn) //this function inserts a node of (node_of_minheap) type into array of (min_heap) type
{
	++mh->size;
	int i = mh->size - 1;

	while (i && mhn->freq < mh->Arra[(i - 1) / 2]->freq)
	{
		mh->Arra[i] = mh->Arra[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	mh->Arra[i] = mhn;
}

void printing_array(int arr[], int n, char ca, int fr) //this function prints the huffman codes for a specific array
{
	int i;
	for (i = 0; i < n; ++i)
		cout << arr[i];

	count_size++;
	counter_arr[count_size - 1] = n;
	respective_char[count_size - 1] = ca;
	respective_freq[count_size - 1] = fr;

	cout << endl;
}

int is_leaf_node(node_of_minheap* root) //function checks if the node is leaf node or not
{
	return !(root->left) && !(root->right);
}

min_heap* creating_and_building_minheap(char data[], int freq[], int size) //this function calls creating_minheap() and building_minheap() 
{
	min_heap* mh = creating_minheap(size);

	for (int i = 0; i < size; ++i)
	{
		mh->Arra[i] = new_node(data[i], freq[i]);
	}

	mh->size = size;
	building_minheap(mh);

	for (int i = 0; i < size; ++i)
		cout << mh->Arra[i]->data << " , " << mh->Arra[i]->freq << endl; //here minheap is being displayed

	return mh;
}

node_of_minheap* building_huffmantree(char data[], int freq[], int size) //this function builds the huffman tree
{
	node_of_minheap* left, * right, * top;

	min_heap* mh = creating_and_building_minheap(data, freq, size);

	while (!if_size_is_one(mh))
	{
		left = extracting_min(mh);
		right = extracting_min(mh);

		top = new_node('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		inserting_in_minheap(mh, top);
	}

	return extracting_min(mh);
}

void printing_codes(node_of_minheap* root, int arr[], int top) //this recursive function calls printing_array() function only if it reaches a leaf node else it first goes to left subtree and then to right one
{
	if (root->left)
	{
		if (root->freq > divider)
			divider = root->freq;
		arr[top] = 0;
		printing_codes(root->left, arr, top + 1);
	}
	if (root->right)
	{
		if (root->freq > divider)
			divider = root->freq;
		arr[top] = 1;
		printing_codes(root->right, arr, top + 1);
	}
	if (is_leaf_node(root))
	{
		if (root->freq > divider)
			divider = root->freq;
		cout << root->data << "= ";
		printing_array(arr, top, root->data, root->freq);
	}
}

void binary_display(node_of_minheap* root, string binary)
{
	if (root == NULL)
		return;
	if (root->data != '$')
		cout << root->data << " , " << binary << endl;
	binary_display(root->left, binary + "0");
	binary_display(root->right, binary + "1");
}

void huffman_BT_codes(char data[], int freq[], int size) //this function calls building_huffmantree() and then calls printing_codes() function
{
	//string binary = "";

	node_of_minheap* root = building_huffmantree(data, freq, size);

	int arr[20], * temp = new int[count_size];
	int top = 0;

	cout << "\nHUFFMAN CODES:\n";
	printing_codes(root, arr, top);

	delete root;

	//binary_display(root, binary);

}

int main()
{
	float comp_ratio = 0;
	LinkedList L;
	string words;
	ifstream file;
	file.open("Characters.txt");				//Opening file
	for (int i = 0; !file.eof(); i++)			//Outer loop will run until end of file not occurs.
	{
		int j = 0;
		getline(file, words);					//Getting full line from file and saving into words variable

		while (words[j] != '\0')				//Inner loop for character checking
		{
			L.Check_Character(words[j]);		//Calling function for characters checking in linked list
			j++;
		}

	}
	file.close();		//Closing file
	//L.sort();
	L.Display(); //Calling display function

	cout << endl << endl;

	const int size = L.sizereturn();

	char* carr = new char[size]; //creating two dynamic arrays characters and their respective frequency
	int* farr = new int[size];
	Node* ptr = L.first;

	for (int i = 0; i < size; i++)
	{
		carr[i] = ptr->data; //initializing those arrays from linked list 
		farr[i] = ptr->freq;
		ptr = ptr->next;
	}

	cout << "BEFORE MIN HEAP:\n";
	for (int i = 0; i < size; i++)
	{
		cout << carr[i] << " , " << farr[i] << endl;
	}

	cout << "\nAFTER MIN HEAP:\n";

	huffman_BT_codes(carr, farr, size);

	cout << "\nDIGIT CODE COUNTER:\n";
	cout << "CHAR,N,FREQ\n";

	for (int i = 0; i < count_size; i++)
	{
		cout << " " << respective_char[i] << "   " << counter_arr[i] << "  " << respective_freq[i] << endl;
	}

	cout << "\nCOMPRESSION RATIO:\n";

	for (int i = 0; i < count_size; i++)
		comp_ratio = comp_ratio + (counter_arr[i] * respective_freq[i]); //here compression ratio is being calculated

	comp_ratio = comp_ratio / divider;

	comp_ratio = 8 / comp_ratio;


	cout << comp_ratio;

	cout << endl;

	while (1)
	{
	}




	/*for (int i = 0; i < count_size; i++)
		delete carr[i];*/
	delete[]carr;
	delete[]farr;
	delete[]counter_arr;
	delete[]respective_char;
	delete[]respective_freq;


	return 0;
}