#include <iostream>

using namespace std;

struct node {
	int x;
	node* left, * right;
	node(int key) {
		x = key; 
	    left = nullptr;
		right = nullptr;
	}
	~node() {
		if (left)
			delete left;
		if (right)
			delete right;
	}
};

bool exists(node* root, int val) {
	if (root == nullptr)
	{
		return false;
	}		
	if (root->x == val)
	{
		return true;
	}
	if (val < root->x) {
		return exists(root->left, val);
	}
	return exists(root->right, val);
}

node* insert(node* root, int val) {
	if (exists(root, val)) {
		return root;
	}
	if (root == nullptr) {
		return new node(val);
	}
	if (val < root->x) {
		root->left = insert(root->left, val);
	}
	if (val > root->x) {
		root->right = insert(root->right, val);
	}
	return root;
}

void inorder( node* root) {
	if (root != NULL) {
		// Обходим лево
		inorder(root->left);

		// Обходим корень
		cout << root->x << " -> ";

		// Обходим право
		inorder(root->right);
	}
}

struct node* minValueNode( node* node) {
	struct node* current = node;

	// Ищем крайний левый лист — он и будет inorder-преемником
	while (current && current->left != NULL)
		current = current->left;

	return current;
}

struct node* deleteNode( node* root, int key) {
	// Возвращаем, если дерево пустое
	if (root == NULL) return root;

	// Ищем узел, который хотим удалить
	if (key < root->x)
		root->left = deleteNode(root->left, key);
	else if (key > root->x)
		root->right = deleteNode(root->right, key);
	else {
		// Если у узла один дочерний элемент или их нет
		if (root->left == NULL) {
			struct node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			struct node* temp = root->left;
			free(root);
			return temp;
		}

		// Если у узла два дочерних элемента
		struct node* temp = minValueNode(root->right);

		// Помещаем inorder-преемника на место узла, который хотим удалить
		root->x = temp->x;

		// Удаляем inorder-преемника
		root->right = deleteNode(root->right, temp->x);
	}
	return root;
}

int menu() {
	int res;
	cout << "\n --Choose option--" << endl;
	cout << "1 - Insert into tree" << endl;
	cout << "2 - Search in tree" << endl;
	cout << "3 - Delete from tree" << endl;
	cout << "Other key - exit" << endl;
	cin >> res;
	return res;
}

int main(){
	node* root = NULL;
	/*root = insert(root, 8);
	root = insert(root, 6);
	root = insert(root, 7);
	root = insert(root, 10);
	root = insert(root, 14);
	root = insert(root, 4);

	root = deleteNode(root, 7);
	bool ex = exists(root, 7);
	inorder(root);

	if (ex == true) {
		cout << "true" << endl;
	}
	else {
		cout << "false" << endl;
	}*/
	
	while (true) {
		int result = menu();
		switch (result) {
		case 1:
		{
			system("cls");
			int val;
			cout << "Put value: ";
			cin >> val;
			root = insert(root, val);
			inorder(root);
		}
			break;
		case 2:
		{
			system("cls");
			int ser;
			cout << "Put value to search: ";
			cin >> ser;
			bool ex = exists(root, ser);
			if (ex == true) {
				cout << "Exists" << endl;
			}
			else {
				cout << "Do not exist" << endl;
			}
		}
			break;
		case 3:
		{
			system("cls");
			int del;
			cout << "Put value to delete: ";
			cin >> del;
			bool ex = exists(root, del);
			if (ex) {
				root = deleteNode(root, del);
				inorder(root);
			}
			else {
				cout << "There is no element with a such value"<<endl;
			}
		}		
			break;
		default:
		{
			exit(0);
		}

		}
	}

	return 0;
}