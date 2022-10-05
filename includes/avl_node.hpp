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
			static node_ptr	left_rotate(node_ptr root);
			static node_ptr	right_rotate(node_ptr root);
			static node_ptr	insert(node_ptr root, pair_type value, node_allocator &alloc);
			static node_ptr	createNode(pair_type value, node_allocator &alloc);
			static node_ptr	erase(node_ptr root, Key key, node_allocator &alloc);
			static node_ptr	next(node_ptr node, node_ptr root);
			static node_ptr	prev(node_ptr node, node_ptr root);
			static node_ptr	min(node_ptr node);
			static node_ptr	max(node_ptr node);
			static node_ptr	upper(node_ptr node, key_type key);
			static node_ptr	lower(node_ptr node, key_type key);
			static node_ptr	find(node_ptr node, key_type key);
			static node_ptr	balanceTree(node_ptr &node, pair_type data);

			const key_type& key() const{return this->_data.first;}

		private:

			pair<Key, T>	_data;
			int				_height;
			struct avl_node	*_left;
			struct avl_node	*_right;
			Compare			_key_compare;
	};

	template<class Key, class T, class Compare,
		class Allocator >
	struct avl_tree_const_iterator;

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
			bool				operator==(const avl_tree_const_iterator<Key,
					T, Compare, Allocator>& other) const;
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
			const node_ptr				base() const;
			const node_ptr				root() const;
			avl_tree_const_iterator		operator+(difference_type n) const;
			

		private:
			node_ptr	_root;
			node_ptr	_current;
	};
}

#include "avl_node.tpp"

#endif
