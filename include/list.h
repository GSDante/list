#ifndef List_H
#define List_H


#include<iostream>
#include<initializer_list> 
#include <stdexcept>

namespace sc{
template <typename T>
	
	class list {
	public:
	
		struct Node{
			T data;
			Node *prev;
			Node *next;
			
			Node(const T & d = T(), Node * p = nullptr,Node * n = nullptr)
				:data(d),prev(p),next(n){}

		};

		size_t m_size;
		Node *m_head;
		Node *m_tail;

	
		


	
		class const_iterator {
		public:
			public:
			
			using value_type = T; //!< The type of the value stored in the list.
			using pointer = T *; //!< Pointer to the value.
			using reference = T&; //!< reference to the value.

			using difference_type = std::ptrdiff_t;
			using iterator_category = std::bidirectional_iterator_tag;

			const_iterator();
		
			const T& operator* () const;
		
			const_iterator & operator++();
			
			const_iterator operator++(int);
			 
			const_iterator & operator--();
			
			const_iterator operator--(int);

			bool operator==(const const_iterator & rhs) const;
		
			bool operator!=(const const_iterator & rhs) const;

 		protected:
			Node *current;
			const_iterator( Node * p ) : current( p ){}
			friend class list<T>;
		};
	
		class iterator : public const_iterator{
		public:

			iterator(): const_iterator(){}
		
			T& operator*() const;
			
			T& operator*();
		
			iterator & operator++();
		
			iterator operator++(int);
			
			iterator & operator--();
			
			iterator operator-- (int);


		protected:

			iterator( Node * p ) : const_iterator( p ){}
			friend class list<T>;
		};
	
		list();

		explicit list( size_t count );
		
		template <typename InputItr>
		list(InputItr first, InputItr last);

		
		list( const std::initializer_list<T> ilist );
		
		~list();
	
		list(const list &);
	
		list & operator=(const list &);
		
		list & operator=(std::initializer_list<T> ilist);
		
		iterator begin();
	
		const_iterator cbegin() const;
		
		iterator end();
		
		const_iterator cend() const;
		
		size_t size() const;
		
		bool empty() const;
		
		void clear();
		
		T & front();
	
		const T & front() const;
	
		T & back() ;
	
		const T & back() const;
	
		void push_front(const T & value);
		
		void push_back(const T & value);
		
		void pop_front();
		
		void pop_back();
		
		void assign(const T& value);
		void assign( size_t count, const T& value );
		
		template <class InItr>
		void assign (InItr first, InItr last);
		
		void assign (std::initializer_list<T> ilist);
		
		iterator insert(iterator itr, const T & value);
		
		template < typename InItr>
		iterator insert( iterator pos, InItr first, InItr last );
		

		iterator insert(iterator pos,std::initializer_list<T> ilist);
	


		iterator erase(iterator itr);
	
		iterator erase(iterator first, iterator last);
		
		const_iterator find(const T & value) const;
		
		bool operator==(const list & rhs);
		
		bool operator!=(const list & rhs);
		
		template<typename U>
		friend std::ostream & operator<< ( std::ostream & out, const list<T>& lst);


	};


}
	#include "list.inl"



#endif
