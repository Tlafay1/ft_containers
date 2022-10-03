#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP

# include "avl_node.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
		class Alloc = std::allocator< ft::pair<const Key, T> > >
	class avl_tree
	{
		public:
			typedef avl_node<Key, T, Compare, Alloc>						node;
			typedef node*													node_ptr;
			typedef avl_tree_iterator<Key, T, Compare, Alloc>				iterator;
			typedef avl_tree_const_iterator<Key, T, Compare, Alloc>			const_iterator;
			typedef Key														key_type;
			typedef T														value_type;
			typedef ft::pair<Key, T>										pair_type;
			typedef ft::pair<const Key, T>									const_pair_type;
			typedef std::size_t												size_type;
			typedef ptrdiff_t												difference_type;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::template rebind<node>::other	node_allocator;

			avl_tree(const allocator_type &alloc = allocator_type());
			~avl_tree();
			avl_tree(avl_node<Key, T, Compare, Alloc> *root);
			
			int				erase(const key_type& key);
			iterator		begin();
			const_iterator	begin() const;
			iterator		end();
			const_iterator	end() const;
			const node_ptr	min() const;
			const node_ptr	max() const;
			size_type		size() const;
			bool			insert(pair_type data);
			void			swap(avl_tree &other);
			void			clear();
			const_pair_type	&find(const key_type &key) const;
			node_ptr		upper(const key_type &key) const;
			node_ptr		find_node(const key_type &key) const;
			allocator_type	get_allocator() const;
			node_ptr		root() const;

		private:
			node_ptr		_root;
			node_allocator	_alloc;
			size_type		_size;
	};
}

# include "avl_tree.tpp"

#endif
