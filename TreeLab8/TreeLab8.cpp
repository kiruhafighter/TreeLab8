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
		// ������� ����
		inorder(root->left);

		// ������� ������
		cout << root->x << " -> ";

		// ������� �����
		inorder(root->right);
	}
}

struct node* minValueNode( node* node) {
	struct node* current = node;

	// ���� ������� ����� ���� � �� � ����� inorder-����������
	while (current && current->left != NULL)
		current = current->left;

	return current;
}

struct node* deleteNode( node* root, int key) {
	// ����������, ���� ������ ������
	if (root == NULL) return root;

	// ���� ����, ������� ����� �������
	if (key < root->x)
		root->left = deleteNode(root->left, key);
	else if (key > root->x)
		root->right = deleteNode(root->right, key);
	else {
		// ���� � ���� ���� �������� ������� ��� �� ���
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

		// ���� � ���� ��� �������� ��������
		struct node* temp = minValueNode(root->right);

		// �������� inorder-��������� �� ����� ����, ������� ����� �������
		root->x = temp->x;

		// ������� inorder-���������
		root->right = deleteNode(root->right, temp->x);
	}
	return root;
}

int main(){
	node* root = NULL;
	root = insert(root, 8);
	root = insert(root, 3);
	root = insert(root, 1);
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
	}

	return 0;
}