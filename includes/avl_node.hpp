#ifndef AVL_NODE_HPP
# define AVL_NODE_HPP

#include <cstddef>
#include "avl_tree.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
		class Alloc = std::allocator< pair<const Key, T> > >
	struct avl_node
	{
		public:
			typedef avl_node<Key, T, Compare, Alloc>						node;
			typedef node*													node_ptr;
			typedef Alloc													allocator_type;
			typedef Key														key_type;
			typedef T														value_type;
			typedef pair<Key, T>											pair_type;
			typedef typename allocator_type::template rebind<node>::other	node_allocator;

			avl_node(pair_type data);

			pair_type&		key_value_pair();
			static int		height(node_ptr node);
			static int		diff(node_ptr node);
			static node_ptr	rr_rotation(node_ptr root);
			static node_ptr	ll_rotation(node_ptr root);
			static node_ptr	lr_rotation(node_ptr root);
			static node_ptr	rl_rotation(node_ptr root);
			// static node_ptr	balance(node_ptr root);
			// static node_ptr	balanceTree(node_ptr root);
			// static node_ptr	insert(node_ptr root, pair_type value, node_allocator &alloc);
			static node_ptr	createNode(pair_type value, node_allocator &alloc);
			// static node_ptr	erase(node_ptr root, Key key, node_allocator &alloc);
			static node_ptr	next(node_ptr node, node_ptr root);
			static node_ptr	prev(node_ptr node, node_ptr root);
			static node_ptr	min(node_ptr node);
			static node_ptr	max(node_ptr node);
			static node_ptr	upper(node_ptr node, key_type key);
			static node_ptr	lower(node_ptr node, key_type key);
			static node_ptr	find(node_ptr node, key_type key);

			static node_ptr	balanceTree(node_ptr &node, pair_type data)
			{
				node->_height = 1 + std::max(depth(node->_left), depth(node->_right));

				int bal = balance(node);

				//Make balanced
				if (bal > 1 && data.first < node->_left->_data.first)// Left Left case
					return right_rotate(node);
				else if (bal < -1 && data.first > node->_right->_data.first)// Right Right case
					return left_rotate(node);
				else if (bal > 1 && data.first > node->_left->_data.first){// Left Right case
					node->_left = left_rotate(node->_left);
					return right_rotate(node);
				}
				else if (bal < -1 && data.first < node->_right->_data.first){// Right Left case
					node->_right = right_rotate(node->_right);
					return left_rotate(node);
				}
				return (node);
			}

			static node_ptr insert(node_ptr node, pair_type data, node_allocator& alloc){
				if (node == NULL)
					return(createNode(data, alloc));
				
				if (data.first < node->_data.first)
					node->_left = insert(node->_left, data, alloc);
				else if (data.first > node->_data.first)
					node->_right = insert(node->_right, data, alloc);
				else
					return node;

				return (balanceTree(node, data));
			}

			static node_ptr erase(node_ptr root, key_type key, node_allocator& alloc){// returns root of modified subtree
				if (root == NULL)
					return root;

				if (key < root->_data.first)//search which node to del
					root->_left = erase(root->_left, key, alloc);
				else if (key > root->_data.first)
					root->_right = erase(root->_right, key, alloc);
				else {//found it
					if ((root->_left == NULL) || (root->_right == NULL)) {
						node_ptr temp = root->_left ? root->_left : root->_right;
						if (temp == NULL){// node has no child
							temp = root;
							root = NULL;
						} else// node has one child
							*root = *temp; // Copy the contents of
						alloc.destroy(temp);
						alloc.deallocate(temp, 1);
					}
					else{// node has 2 children
						node_ptr temp = min(root->_right);
						root->_data = temp->_data;

						// delete inorder successor
						root->_right = erase(root->_right, temp->_data.first, alloc);
					}
				}

				if (root == NULL)// if the tree had only one node then return
					return root;
				root->_height =	std::max(depth(root->_left),	depth(root->_right)) + 1;

				int bal = balance(root);

				//Make Balanced
				if (bal > 1 && balance(root->_left) >= 0)//Left Left case
					return right_rotate(root);
				else if (bal > 1 && balance(root->_left) < 0){//Left Right case
					root->_left = left_rotate(root->_left);
					return right_rotate(root);
				}
				else if (bal < -1 && balance(root->_right) <= 0)//Right Right case
					return left_rotate(root);
				else if (bal < -1 && balance(root->_right) > 0){//Right Left case
					root->_right = right_rotate(root->_right);
					return left_rotate(root);
				}

				return root;
			}

			static size_t depth(node *n){//gere le cas ou la node n'existe pas
				if (n == NULL)
					return 0;
				return n->_height;
			}

			static ssize_t balance(node_ptr n){
				if (n == NULL)
					return 0;
				return depth(n->_left) - depth(n->_right);
			}

			static node_ptr new_node(pair_type data, node_allocator& alloc){
				node_ptr node = alloc.allocate(1);
				alloc.construct(node, data);
				return node;
			}

			static node_ptr right_rotate(node_ptr y){
				node_ptr	x = y->_left;
				node_ptr	t2 = x->_right;

				// perform rotation
				x->_right = y;
				y->_left = t2;

				//adapt depth
				y->_height =	std::max(depth(y->_left), depth(y->_right)) + 1;
				x->_height =	std::max(depth(x->_left), depth(x->_right)) + 1;

				return x;
			}

			static node_ptr left_rotate(node_ptr x){
				node_ptr	y = x->_right;
				avl_node	*t2 = y->_left;

				// perform rotation
				y->_left = x;
				x->_right = t2;

				//adapt depth
				x->_height =	std::max(depth(x->_left), depth(x->_right)) + 1;
				y->_height =	std::max(depth(y->_left), depth(y->_right)) + 1;

				return y;
			}

		private:

			pair<Key, T>	_data;
			int				_height;
			struct avl_node	*_left;
			struct avl_node	*_right;
			Compare			_key_compare;
	};

	template<class Key, class T, class Compare = std::less<Key>,
		class Allocator = std::allocator< ft::pair<const Key, T> > >
	struct avl_tree_iterator
	{
		public:
			typedef ft::pair<const Key, T>					value_type;
			typedef ptrdiff_t								difference_type;
			typedef std::bidirectional_iterator_tag			iterator_category;
			typedef value_type*								pointer;
			typedef const value_type*						const_pointer;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef avl_node<Key, T, Compare, Allocator>	node;
			typedef node*									node_ptr;
			typedef ft::pair<const Key, T>					const_pair_type;

			avl_tree_iterator();
			avl_tree_iterator(const avl_tree_iterator& src);
			avl_tree_iterator(node_ptr root, node_ptr current);
			~avl_tree_iterator();

			avl_tree_iterator&	operator=(const avl_tree_iterator& src);
			avl_tree_iterator&	operator++();
			avl_tree_iterator	operator++(int);
			bool				operator==(const avl_tree_iterator& other);
			bool				operator!=(const avl_tree_iterator& other);
			reference			operator*() const;
			pointer				operator->() const;
			avl_tree_iterator&	operator--();
			avl_tree_iterator	operator--(int);
			// bool operator==(const avl_tree_const_iterator<Key,
			// 		T, Compare, Allocator>& other);
			const node_ptr		base() const;
			const node_ptr		root() const;
			avl_tree_iterator	operator+(difference_type n) const;
			

		private:
			node_ptr	_root;
			node_ptr	_current;
	};

	template<class Key, class T, class Compare = std::less<Key>,
		class Allocator = std::allocator< ft::pair<const Key, T> > >
	struct avl_tree_const_iterator
	{
		public:
			typedef ft::pair<const Key, T>					value_type;
			typedef ptrdiff_t								difference_type;
			typedef std::bidirectional_iterator_tag			iterator_category;
			typedef value_type*								pointer;
			typedef const value_type*						const_pointer;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef avl_node<Key, T, Compare, Allocator>	node;
			typedef node*									node_ptr;
			typedef ft::pair<const Key, T>					const_pair_type;

			avl_tree_const_iterator();
			avl_tree_const_iterator(const avl_tree_const_iterator& src);
			avl_tree_const_iterator(const avl_tree_iterator<Key, T, Compare, Allocator>& non_const);
			avl_tree_const_iterator(node_ptr root, node_ptr current);
			~avl_tree_const_iterator();

			avl_tree_const_iterator&	operator=(const avl_tree_const_iterator& src);
			avl_tree_const_iterator&	operator++();
			avl_tree_const_iterator		operator++(int);
			bool						operator==(const avl_tree_const_iterator& other);
			bool						operator!=(const avl_tree_const_iterator& other);
			reference					operator*() const;
			pointer						operator->() const;
			avl_tree_const_iterator&	operator--();
			avl_tree_const_iterator		operator--(int);
			// bool operator==(const avl_tree_iterator<Key,
			// 		T, Compare, Allocator>& other);
			node_ptr					base();
			node_ptr					root();
			avl_tree_const_iterator		operator+(difference_type n) const;
			

		private:
			node_ptr	_root;
			node_ptr	_current;
	};
}

#include "avl_node.tpp"

#endif
