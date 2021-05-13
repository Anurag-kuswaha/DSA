//___________________________________Anurag Kushwaha NIT PATNA_____________________________
//                       
//         BST implementation;
//         1- insertion;
//         2- find
//         3- next grater elemeent;
//         4- delete element;

// NOTE- implemented "DELETE operation " using node swapping not by value swapping hence root value is not allowed to delete;



#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#define ll long long
#define NP 1e9+7
using namespace std;
struct node {
	int val;
	node* l,* r,*parent;
	node() {
		val = NULL;
		l = r =parent= nullptr;
	}
};
////////////////////// INSERT element operation ////////////////////////////////////////////////////

node* insert(node* root,int  val) {
	if (root == nullptr) {
		root = new node(); root->val = val;return root;
	}
	if (root->val > val) {
		  //go left ;
		root->l =insert(root->l, val);
		root->l->parent = root;
	}
	else {
		//go left ;
		root->r = insert(root->r, val);
		root->r->parent = root;
	}
	return root;
}
////////////////////// FIND element operation ////////////////////////////////////////////////////

node* find(node* root,int val) {
	node* temp = root;
	if (temp == nullptr) return nullptr;
	if (temp->val == val) return temp;
	if (temp->val > val) {
		return find(temp->l, val);
	}
	else {
		return find(temp->r, val);
	}
	
}

node* left_descendant(node* root) {
	if (root->l == nullptr) return root;
	return left_descendant(root->l);
}
node* right_ancestor(node* root, int val) {
	if (root == nullptr) return nullptr; //might be the value we are seraching is the largest
	if (root->val > val) return root;
	else right_ancestor(root->parent, val);
}
////////////////////// NEXT element operation ////////////////////////////////////////////////////
node* next(node* root, int val) {
	    node* temp = find(root, val);
		 //elemet is exist in the tree;
        if(temp != nullptr)     {
	    
			if (temp->r != nullptr) {  // if right child is there;
				temp = left_descendant(temp->r); //going over the leftmost child of the right side
			}
			else {
				temp = right_ancestor(temp->parent, val); //roam until the parent is found to be greater than our value 
			}
			return temp;
        }
		return nullptr; //elemnt is doesn't exist in our BST;
}
////////////////////// DELETE operation ////////////////////////////////////////////////////
node*  delete_(node* root,int  val) {
	node* curr_node = root;
	     while (true) {
		                 if (curr_node == nullptr) {
			                    cout << "element doesn't exist \n"; return root;
		                 }
		                 if (curr_node->val == val) break;
		                 if (curr_node->val < val) curr_node = curr_node->r;
		                 else if(curr_node->val > val) curr_node = curr_node->l;
	     }
		 if (curr_node->r == nullptr && curr_node->l == nullptr) { 
			            //no left and right child
			            // break this from their parent;
			           // cout << "all null\n";
			            node* curr_parent = curr_node->parent;
			            //cout << "curr parent value is : " << curr_parent->val << "\n";
			            if (curr_parent->l == curr_node) {
			        	        curr_parent->l = nullptr;
			            }
			            else if(curr_parent->r == curr_node) {
				               curr_parent->r = nullptr;
			            }
		 } 
	     else if (curr_node->l == nullptr) {
		             //we go in the right;
		             //cout << "only right present \n";
		             node* curr_right = curr_node->r;
		             node* curr_parent = curr_node->parent;
		             if (curr_parent->l == curr_node) {
			                curr_right->parent = curr_parent;  curr_parent->l = curr_right;
		             }
		             else {
		                	curr_right->parent = curr_parent;  curr_parent->r = curr_right;
		             }
		            // make right as left child and delete the curr_node;

	
	     }
	     else if (curr_node->r == nullptr) {
		            //cout << "only left present \n";
		            node* curr_left = curr_node->l;
		            node* curr_parent = curr_node->parent;
		            if (curr_parent->l == curr_node) {
			                  curr_left->parent = curr_parent;  curr_parent->l = curr_left;
		            }
		            else {
			                  curr_left->parent = curr_parent;  curr_parent->r = curr_left;
		            }
		                // make left as left child and delete the curr_node;
	     }
	     else if (curr_node->r == next(root, val)) {
		             // current node right child is the most eligile candidate for the gap filling hence we can replace this with 
		             // our curr node and add current right child right node and fix this;
			        //cout << "exception of right as next node \n";
		             node* next_node = curr_node->r;  //as right child of current is the next node;
		             node* curr_parent = curr_node->parent;
		             if (curr_parent->l == curr_node) {
			                  next_node->parent = curr_parent;  curr_parent->l = next_node;
		             }
		             else {
		                 	  next_node->parent = curr_parent;  curr_parent->r = next_node;
		             }
		              // now add the left child of the current node to the left child of the next node;
					 node* curr_left = curr_node->l;
					 next_node->l = curr_left;
					 curr_left->parent = next_node;
					 
	     }
	     else if (curr_node->r != nullptr && curr_node != nullptr) {
		                //go to the find the next lowest value in the right;
		             //cout << "left and right present \n";
		             node* curr_right = curr_node->r;
		             node* next_node = curr_node->r;
		             while (next_node->l != nullptr) {
		            	        next_node = next_node->l;  //most eligible bachelor for replacing the curr value;
		             }

					 node* next_node_parent = next_node->parent;
		             if (next_node->r != nullptr) {
			                   //right child of next_node is there so fixed this first;
			                   node* next_node_right = next_node->r;
			                   next_node_parent->l = next_node_right;
			                   next_node_right->parent = next_node_parent;
		             }
					 else {
						     //most eligible don't have right child;
						    //next node right don't have right child hence make its parent null;
						     next_node_parent->l = nullptr; // 
					 }
			          //now the fixing the area across the current node;

			         node* curr_parent = curr_node->parent;
			         if (curr_parent->r == curr_node) {
				                // root is right child of its parents;
			  	                curr_parent->r = next_node; next_node->parent = curr_parent;
		     	     }
		             else if(curr_parent->l== curr_node) {
				                //root is left child;
			     	            curr_parent->l = next_node; next_node->parent = curr_parent;
			         }
				     node* root_left = curr_node->l;
				     node* root_right = curr_node->r;
					 next_node->l = root_left;  root_left->parent = next_node;
					 next_node->r = root_right; root_right->parent = next_node;

					 //////////////////dry run/////////////////////////////
					/* cout << " parent value is : " << curr_parent->val << "\n";
					 cout << "     parent left value is : " << curr_parent->l->val << "\n";
					 cout << "     parent right value is : " << curr_parent->r->val << "\n";
					 cout << "new swapped  value is   : " << next_node->val << "\n";
					 //cout << "    new swapped  left value is   : " << next_node->l->val << "\n";
					 //cout << "    new swapped  right value is   : " << next_node->r->val << "\n";
					 cout << "root right : " << root_right->val << "\n";
					 cout << "next node parent value : " << next_node->parent->val << "\n";
				   */
	     }
	     curr_node->l = curr_node->parent = curr_node->r = nullptr; //null  the deleted element;
	     return root;
 }
void inorder(node* root) {
	if (root == NULL) return;
	inorder(root->l);
	cout << root->val<<" ";
	inorder(root->r);

}
int main() {
	node* head = nullptr;
	
	while (true) {
		cout << "input the option \n 1- insert \n 2- find\n 3- next\n 4- delete\n";
		int input; cin >> input;
		cout << "enter the value\n";
		int val; //= rand() % 1000; //for random geneation of node value;
		cin >> val;
		    if (input == 1) {
			        //insert;
				bool f = 0;
				if (head == nullptr) {
					f = 1;
				   }
			         head = insert(head, val);
					 if (f == 1) {
						 cout << "root of the tree is : " << head->val << "\n";
					 }
		    }
		    else if (input == 2) {
			         //find next;
			         node* temp = find(head, val);
					 if (temp != nullptr) {
						 cout << temp->val << "\n";
					 }
					 else cout << "not exist \n";
		    }
		    else if (input == 3) {
				     //next
				     node* temp = next(head, val);
				     if (temp != nullptr)
					      cout << temp->val << "\n";
					 else cout << "not exist \n";
		    }
			else if (input == 4) {
				     if (val == head->val) {
					    cout << "sorry head value is not allowed to delete (as implemeted using node swap)\n";
			     	 }
				     else delete_(head, val);
			}
			else    cout << "wrong input \n";
			
			cout << "inorder traversal of current value is \n";
			inorder(head);
			cout << "\n\n";
		}
	}
