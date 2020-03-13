#ifndef src_smart_ptr_tree_cpp_
#define src_smart_ptr_tree_cpp_

#include "smart_ptr_tree.hpp"

namespace binary_search_tree{

template<typename Type_arithmetic>
bool BSTree<Type_arithmetic>::insert_rcv(node_ptr& node, const Type_arithmetic& data)
{
// Insert new data by finding recursively the correct pace applying the law of the binary search Tree.
// allocate a new node by using std smart pointers make_unique.

	if(node == nullptr) {

		// std::cout << "Try data: " << data << std::endl;
		node = std::make_unique<Node>(data);
		return true;
	} else {

		if(data <= node->data) {

			return insert_rcv(node->left, data);
		} else {

			return insert_rcv(node->right, data);
	   }
   }
}

template<typename Type_arithmetic>
int BSTree<Type_arithmetic>::height(const node_ptr& root) const
{
	// Calculate recursively the height of the Tree under root.
  if ( root == nullptr ){

	  return 0;
  }
  else{

	  int leftsubtree = height(root->left);
	  int rightsubtree = height(root->right);

	  if ( leftsubtree > rightsubtree ){
		  return leftsubtree+1;
	  }
	  else{
		  return rightsubtree+1;
	  }
  }
}

template<typename Type_arithmetic>
bool BSTree<Type_arithmetic>::checkBST_deep_left_first(const node_ptr& node, Type_arithmetic& last_value) const
{
   // Public function CheckBST calls to this Private-recursive function from the node root.
   // Check and Return True if the tree is binary Tree.

	if( node == nullptr ) return true;
	if( !checkBST_deep_left_first(node->left, last_value ) ) return false;

	// This condition is checked for first time when the deepest last node to he left is reached (null on the left side).
	if ( !( last_value < node->data ) ) return false; // First time will work because last_value was initiated with -1.
	last_value = node->data; // Update last_value and All the elements at the right subtree must be bigger:
	return checkBST_deep_left_first(node->right, last_value);
}


template<typename Type_arithmetic>
bool BSTree<Type_arithmetic>::insert(const Type_arithmetic& data)
{
	if ( !( data > type_minimum_number) ) {
		std::cout<< "The minimum number " << type_minimum_number << " is restricted due to algorithm definition." << std::endl;
		return false;
	}

	if ( insert_rcv(root, data) ){

		real_counter++;
		return true;
	}
	else {

		return false;
	}
}

template<typename Type_arithmetic>
bool BSTree<Type_arithmetic>::checkBST() const
{
   // Return True if Tree is a binary Tree.
   // Trees with repeated data-nodes are not considered a binary Tree
   if( root != nullptr ) {

	Type_arithmetic last_value = type_minimum_number;
	return checkBST_deep_left_first(root,last_value);
   }else return true;
}


template<typename Type_arithmetic>
void measure_ticks( BSTree<Type_arithmetic>& myTree){
	// Measure the time in ticks of the function( in BSTree ) given as a parameter. Good for comparing 2 different definitions.
	using namespace std::chrono;

	std::cout << "Measuring height..." << std::endl;
	auto start = system_clock::now();
	int height = std::invoke(&BSTree<Type_arithmetic>::obtain_height, myTree);
	auto end = system_clock::now();

	// Calculating total ticks taken by the program:
	int ticks_taken = (end - start).count();
	std::cout << "Ticks taken by function is : " << std::fixed
		<< ticks_taken;
	std::cout << " ticks " << std::endl;
	std::cout << "height " << height << std::endl;
}

} // end of namespace binary_search_tree


#endif

int main() {

using namespace binary_search_tree;
using namespace std;

/* To check Type errors at compile time:
BSTree<std::string> myTreeChar;
myTreeChar.real_counter = 1;
std::cout << myTreeChar.real_counter << std::endl;

*/

BSTree<int> myTree;

int t;
int data;


std::cin >> t;
for (int var = 0; var < t; ++var) {
    std::cin >> data;
    if( !myTree.insert(data) ) std::cout << "Node data- " << data << " could'nt be inserted!" << endl;
}

std::cout << "real_counter nodes " << myTree.real_counter << std::endl;

if(myTree.checkBST()){

	std::cout << "Binary tree!"<< std::endl;

}else{
	std::cout << "Not binary tree!"<< std::endl;

}


measure_ticks(myTree);

return 0;
}
