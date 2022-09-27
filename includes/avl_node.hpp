#ifndef AVL_NODE_HPP
# define AVL_NODE_HPP

// #include "avl_tree.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
		class Alloc = std::allocator< std::pair<const Key, T> > >
	struct avl_node
	{
		public:
			typedef avl_node<Key, T, Compare, Alloc>	node;
			typedef node*								node_ptr;
			typedef Alloc								allocator_type;
			typedef Key									key_type;
			typedef T									value_type;
			typedef pair<Key, T>						pair_type;


			avl_node(const Alloc &alloc);
			
			avl_node	*rr_rotation(avl_node *root);
			avl_node	*ll_rotation(avl_node *root);
			avl_node	*lr_rotation(avl_node *root);
			avl_node	*rl_rotation(avl_node *root);
			avl_node	*balance(avl_node *root);
			avl_node	*balanceTree(avl_node *root);
			avl_node	*insert(avl_node *root, pair<Key, T> value);
			avl_node	*createNode(pair<Key, T> value);

		private:
			typedef typename allocator_type::template rebind<node>::other node_allocator;

			pair<Key, T>	_data;
			int				_height;
			struct avl_node	*_left;
			struct avl_node	*_right;
			allocator_type	_alloc;
			Compare			_key_compare;
	};

	template<class Key, class _Tp, class Compare = std::less<Key>,
		class Allocator = std::allocator< ft::pair<const Key, _Tp> > >
	struct avl_tree_iterator
	{
		public:
			typedef ft::pair<const Key, _Tp>				value_type;
			typedef ptrdiff_t								difference_type;
			typedef std::bidirectional_iterator_tag			iterator_category;
			typedef value_type*								pointer;
			typedef const value_type*						const_pointer;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef avl_node<Key, _Tp, Compare, Allocator>	node;
			typedef node*									node_ptr;
			typedef ft::pair<const Key, _Tp>				const_pair_type;

			avl_tree_iterator(const avl_tree_iterator& src);
			~avl_tree_iterator();
			avl_tree_iterator& operator=(const avl_tree_iterator& src);
			avl_tree_iterator& operator++();
			avl_tree_iterator operator++(int);

			bool operator==(const avl_tree_iterator& other);
			bool operator!=(const avl_tree_iterator& other);
			reference operator*() const;
			pointer operator->() const;
			avl_tree_iterator();
			avl_tree_iterator& operator--();
			avl_tree_iterator operator--(int);
			avl_tree_iterator(node_ptr root, node_ptr current);
			bool operator==(const avl_tree_const_iterator<Key,
					_Tp, Compare, Allocator>& other);
			node_ptr base();
			avl_tree_iterator operator+(difference_type n) const;
			

		private:
			node_ptr	_root;
			node_ptr	_current;
	};
}

#include "avl_node.tpp"

#endif
