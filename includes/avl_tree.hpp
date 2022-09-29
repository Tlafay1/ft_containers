#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP

# include "avl_node.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
		class Allocator = std::allocator< ft::pair<const Key, T> > >
	class AvlTree
	{
		public:
			typedef avl_node<Key, T, Compare, Allocator>					node;
			typedef node*													node_ptr;
			typedef avl_tree_iterator<Key, T, Compare, Allocator>			iterator;
			typedef avl_tree_const_iterator<Key, T, Compare, Allocator>		const_iterator;
			typedef Key														key_type;
			typedef T														value_type;
			typedef ft::pair<Key, T>										pair_type;
			typedef ft::pair<const Key, T>									const_pair_type;
			typedef std::size_t												size_type;
			typedef ptrdiff_t												difference_type;
			typedef Allocator												allocator_type;
			typedef typename allocator_type::template rebind<node>::other	node_allocator;

			AvlTree();
			~AvlTree();
			AvlTree(avl_node<Key, T, Compare, Allocator> *root);
			
			int				height();
			int				diff();
			void			erase(const key_type& key);
			iterator		begin();
			const_iterator	begin() const;
			iterator		end();
			const_iterator	end() const;
			node_ptr		min();
			node_ptr		max();
			size_type		size() const;
			bool			insert(pair_type data);
			void			swap(AvlTree &other);
			void			clear();
			const_pair_type	&find(const key_type &key);
			node_ptr		upper(const key_type &key) const;
			node_ptr		find_node(const key_type &key) const;
			allocator_type	get_allocator() const;

		private:
			node_ptr		_root;
			allocator_type	_alloc;
			size_type		_size;
	};
}

# include "avl_tree.tpp"

#endif