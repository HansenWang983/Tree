#include <iostream>
#include <fstream>
#include <stack>
using namespace std;


// 二叉查找树
struct Node{
	int entry;
	Node* left;
	Node* right;
	Node(int e=0){
		entry=e;
		left=nullptr;
		right=nullptr;
	}
};

void bst_print_dot_null(int e, int nullcount, ofstream &out)
{
    out<<"    null"<<nullcount<<" [shape=point];\n";
    out<<"    "<<e<<" -> null"<<nullcount<<";\n";
}

void bst_print_dot_aux(Node* p, ofstream &out)
{
    static int nullcount = 0;

    if (p->left)
    {
        out<<"    "<<p->entry<<" -> "<<p->left->entry<<";\n";
        bst_print_dot_aux(p->left, out);
    }
    else
        bst_print_dot_null(p->entry, nullcount++, out);

    if (p->right)
    {
        out<<"    "<<p->entry<<" -> "<<p->right->entry<<";\n";
        bst_print_dot_aux(p->right, out);
    }
    else
        bst_print_dot_null(p->entry, nullcount++, out);
}

void bst_print_dot(Node* p, ofstream &out)
{
    out<<"digraph BST {\n";
    out<<"    node [fontname=\"Arial\"];\n";

    if (!p)
        out<<"\n";
    else if (!p->right && !p->left)
        out<<"    "<<p->entry<<";\n";
    else
        bst_print_dot_aux(p, out);

    out<<"}\n";
}
// void print_offset(ofstream &out, int offset)
// {
//     int i;
//     for (i = 0; i < offset; ++i)
//     {
//         out<<" ";
//     }
// }


// /* Prints the BST horizontally as ASCII
// */
// void bst_print_ascii(Node* p, ofstream &out)
// {
//     static int offset = 0;

//     print_offset(out, offset);

//     if (p == nullptr)
//     {
//         // fprintf(stream, "-\n");
//         out<<"-\n";
//         return;
//     }
//     // fprintf(stream, "%d\n", p->key);
//     out<<p->entry<<endl;

//     offset += 3;
//     bst_print_ascii(p->left, out);
//     bst_print_ascii(p->right, out);
//     offset -= 3;
// }

class Tree{
public:
	Tree(){
		root=nullptr;
		count=0;
	}

	Tree(int e):count(0){
		root=new Node(e);
		count++;
	}

	~Tree(){
		MemoryDelete(root);
		root=nullptr;
	}

	void MemoryDelete(Node* p){
		Node* node;
		if(p!=nullptr)
		{
			node=p->right;
			MemoryDelete(p->left);
			delete p;	
			MemoryDelete(node);
		}

	}

	void remove_root(Node* &r){
		Node* to_delete=r;
		if(!r->right)
			r=r->left;
		else if(!r->left)
			r=r->right;
		else{
			to_delete=r->left;
			Node* parent=r;
			while(to_delete->right){
				parent=to_delete;
				to_delete=to_delete->right;
			}
			r->entry=to_delete->entry;
			if(parent==r)
				r->left=to_delete->left;
			else
				parent->right=to_delete->left;	
		}
		delete to_delete;
		count--;
		return;
	}

	void insert_node(Node* &p,int e){
		if(p==nullptr){
			p=new Node(e);
			count++;
		}
		else if(p->entry<e){
			insert_node(p->right,e);
		}
		else 
			insert_node(p->left,e);
		return;
	}
	

	void insert(int e){
		insert_node(root,e);
	}

	void remove(int e){
		if(root){
			if(root->entry==e)
				remove_root(root);
			else
				remove_node(root,e);
		}
	}

	void remove_node(Node* p,int e){
		if(e<p->entry&&p->left){
			if(e==p->left->entry)
				remove_root(p->left);
			else
				remove_node(p->left,e);
		}
		else if(e>p->entry&&p->right){
			if(e==p->right->entry)
				remove_root(p->right);
			else	
				remove_node(p->right,e);
		}
	}

	void print(){
		preorder(root);
	}

	void preorder(const Node* p){
		if(p){
			cout<<p->entry<<" ";
			preorder(p->left);
			preorder(p->right);
		}
		return;
	}

	void change(){
		interchange(root);
	}


	// recursive

	void interchange(Node* &p){
		// Node* pre=p;
		if(p){
			Node* tem=p->left;
			p->left=p->right;
			p->right=tem;
			interchange(p->left);
			interchange(p->right);
		}
	}

	//non-recursive
// 	void interchange(Node* &p){
// 		stack<Node*> sta;
// 		sta.push(p);
// 		while(!sta.empty()){
// 			p=sta.top();
// 			sta.pop();
// 			Node* tem=p->left;
// 			p->left=p->right;
// 			p->right=tem;
// 			if(p->left)
// 				sta.push(p->left);
// 			if(p->right)
// 				sta.push(p->right);
// 			cout<<sta.size()<<endl;
// 		}
// 	}

	int size(){
		return count;
	}

	void treePrint(bool flag){
		ofstream out;
		if(!flag)
			out.open("before.dot");
		// bst_print_ascii(root,out);
		else
			out.open("after.dot");
		bst_print_dot(root,out);
	}


private:
	Node *root;
	int count;
};


int main(int argc, char const *argv[])
{
	cout<<"Input the choice you want to do\n\n";
	char c;
	Tree tree;
	int e;
	int num;
	bool flag=false;
	cout<<"i           insert a node in linked binary tree\n";
	cout<<"d           delete a node in linked binary tree\n";
	cout<<"c           interchange all left and right subtrees\n";
	cout<<"p           !!!output the binary tree to the file:binaryTree.dot\n";
	cout<<"q           quit\n";
	cin>>c;
	while(c!='q'){
		switch(c){
			case 'i':
				cout<<"Input the number of entry you want to insert\n";
				cin>>num;
				while(num--){
					cout<<"Input the node entry\n";
					cin>>e;
					tree.insert(e);
				}
				break;
			case 'd':
				cout<<"Input the number of entry you want to delete\n";
				cin>>num;
				while(num>tree.size()){
					cout<<"There has only "<<tree.size()<<" node(s),input again\n";
					cin>>num;
				}
				while(num--){
					cout<<"Input the node entry\n";
					cin>>e;
					tree.remove(e);
				}
				break;
			case 'c':
				tree.change();
				flag=true;
				break;
			case 'p':
				tree.treePrint(flag);
				cout<<endl;
				break;
			default:
				cout<<"Input the correct choice\n\n";
				break;
		}
		cout<<"i           insert a node in linked binary tree\n";
		cout<<"d           delete a node in linked binary tree\n";
		cout<<"c           interchange all left and right subtrees\n";
		cout<<"p           !!!output the binary tree to the file:binaryTree.dot\n";
		cout<<"q           quit\n";
		cin>>c;
	}
	return 0;
}





// 按层次输出
// void LevelPrint(BiTree T)  
// {  
//     BiTree queue[MaxSize];  //定义一个队列，用于存放结点的指针  
//     BitNode *p;  
//     int front=-1,rear=-1;  
//     rear++;  
//     queue[rear]=T;  
//     while(front!=rear)  
//     {  
//         front=(front+1)%MaxSize;  
//         p=queue[front];     //取出队头元素  
//         printf("%c ",p->data);   //输出根结点  
//         if (p->lchild!=NULL) //如果左孩子不为空，将左孩子结点指针入队  
//         {  
//             rear=(rear+1)%MaxSize;  
//             queue[rear]=p->lchild;  
//         }  
//         if (p->rchild!=NULL) //如果右孩子不为空，将右孩子结点指针入队  
//         {  
//             rear=(rear+1)%MaxSize;  
//             queue[rear]=p->rchild;  
//         }  
//     }  
// } 