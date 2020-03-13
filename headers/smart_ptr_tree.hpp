#ifndef header_smart_ptr_tree_hpp_
#define header_smart_ptr_tree_hpp_


#include <bits/stdc++.h>
#include <functional>
#include <vector>
#include <chrono>
#include <type_traits>

namespace binary_search_tree{

/*
template<
    typename Type_arithmetic_node,
    typename = typename std::enable_if<std::is_arithmetic<Type_arithmetic_node>::value, Type_arithmetic_node>::type
>
*/

template<typename Type_arithmetic>
class BSTree {
	// Insert arithmetic data-nodes into a binary tree. Any arithmetic type is supported, but the minimum negative number is restricted.
	// Check if tree is a binary tree, or calculate the height. Trees with repeated data-nodes are not considered a binary Tree

private:
	struct Node;
	typedef std::unique_ptr<Node> node_ptr;
	struct Node {

		Type_arithmetic data;
		node_ptr left;
		node_ptr right;
		Node(const Type_arithmetic& data_value ): data (data_value), left( nullptr), right( nullptr ){}
	};

	const Type_arithmetic type_minimum_number = type_minimum_number_f();

	node_ptr root;
	bool insert_rcv(node_ptr& node, const Type_arithmetic& data);
	int height(const node_ptr& root) const;
	bool checkBST_deep_left_first(const node_ptr& node, Type_arithmetic& last_value) const;

	inline Type_arithmetic type_minimum_number_f() const
	{
	   // Return the minimum number of the type using numeric_limits.
		// Only in the case of float type (numeric_limits will return the minimum positive near 0),
		// then this function will return the minimum negative number: -max.

		if constexpr( std::is_same<Type_arithmetic,float>::value ) return (-1)*std::numeric_limits<Type_arithmetic>::max();
		else return std::numeric_limits<Type_arithmetic>::min();
	}

public:

	int real_counter;
	BSTree():root(nullptr), real_counter(0){
		static_assert( std::is_arithmetic< Type_arithmetic >::value , "Type parameter of this class must be an arithmetic type" );
		// Otherwise check BST will not work. Since member function CheckBST make use of numeric_limits.

	}

	bool insert(const Type_arithmetic& data);
	bool checkBST() const;
	inline int obtain_height() const{ return height(root); }

}; //End of BSTree class

}
#endif
