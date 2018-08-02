#include "list.h"

namespace sc {

template<typename T>
list<T>::list( void ) : m_size(0), m_head( new Node() ), m_tail( new Node() )
{
    m_head->prev = nullptr;
    m_tail->next = nullptr;
    m_head->next = m_tail;
    m_tail->prev = m_head;

    // Por ser duplamente encadeada, é ligado o head ao tail cumutativamente  de tal forma 
    // que o head é anterior ao tail
}



template<typename T>
list<T>::list(size_t count ) : m_size( count ),
 m_head( new Node() ), m_tail( new Node() )
{
	// aqui vou criar a lista novamente pra depois ir adicionando com o laço
	m_head->prev = nullptr;
    m_tail->next = nullptr;
    m_head->next = m_tail;
    m_tail->prev = m_head;

    auto current = m_head;

	for(auto i = (0u); i != count; i++){
			Node *new_node = new Node();

			new_node->data = 0;

			new_node->next = m_tail;
			new_node->prev = current;

			current->next->prev = new_node;
			current->next = new_node;

			current = current->next;
		
		}

	/* vi alguns casos de adições de instâncias em listas , e preferi utilizar o
	 push back para adicionar novas instância do tipo T de acordo com o template por ser mais simplório.
	Porém, vi que posso fazer na forma de adição de Nós no laço do for, sendo que o novo nó aplicado deve estar conectado ao tail e o head, assim:
		for(i = 0; i < count; i++)
	{
		push_back( *new_element );
	}
		posicionando os "new_node's" proximo ao next e lá no começo desta função já definido q o tail vai ser o m_head->next
		logo já vai ta "automaticamente" proximo às instâncias
	*/

}


template<typename T>
template< typename InputIt >
list<T>::list( InputIt first, InputIt last ) 
:  m_head( new Node ()), m_tail(new Node())
{
	m_head->prev = nullptr;
    m_tail->next = nullptr;
    m_head->next = m_tail;
    m_tail->prev = m_head;

    auto distance =  std::distance(first,last);

    m_size = distance;
   
    auto current = m_head;

	for(auto i = (0u); i != distance; i++){

		Node *new_node = new Node();

		new_node->data = *first;

		new_node->next = m_tail;
		new_node->prev = current;

		current->next->prev = new_node;
		current->next = new_node;

		current = current->next;

		first++;
	}

}


template<typename T>
list<T>::list( const list& other ):
 m_size(0), m_head( new Node ()), m_tail(new Node())
{
	m_head->prev = nullptr;
    m_tail->next = nullptr;
    m_head->next = m_tail;
    m_tail->prev = m_head;

	m_size = 0;

	for(const_iterator iter = other.cbegin(); iter != other.cend(); iter++){
            push_back( *iter );
	}
	// Neste código assim como os construtores anteriores, refiz de forma semelhante e mais simplório,pois não entendi 
	// o que a minha dupla fez nesta função.Assim, refiz da conforme o meu entendimento de lista.	
	

}
// construtor de lista inicializadora , bem parecido com as outras,porém utilizo a lista inicializadora 
// para usar meu iteradores para criarem a minha lista duplamente encadeada

template<typename T>
list<T>::list( std::initializer_list<T> ilist ): 
 m_head( new Node ()), m_tail(new Node())
{
	m_head->prev = nullptr;
    m_tail->next = nullptr;
    m_head->next = m_tail;
    m_tail->prev = m_head;

    auto first = ilist.begin();
	auto distance = ilist.size();
	m_size = distance;

	auto current = m_head;

	for(auto i(0u) ; i != distance ; i++){
		Node *new_node = new Node();

		new_node->data = *first;

		new_node->next = m_tail;
		new_node->prev = current;

		current->next->prev = new_node;
		current->next = new_node;

		current = current->next;

		first++;
		
		}
}


template<typename T>
list<T>::~list()
{
	// limpando a lista 
	clear();

	// agora só precisa-se deletar o head e o tail
	delete this->m_head;
	delete this->m_tail;
}

// operator de atribuição em que vou pegar todos os valores da lista a direita do operator para a lista da esquerda
template<typename T>
list<T> & list<T>::operator=( const list& other )
{
	// fiz este if para quando tiverem o mesmo tamanho,apenas aplicar uma a outra
	// ja para o else faço isso pois coloco em tamanho de acordo para n ter espaço para lixo
	if( m_size == other.m_size)
	{
		Node* current; 
		Node* prev;

		current = m_head->next;
		prev = other.m_head->next;

		while(prev->next != nullptr)
		{
			current->data = prev->data;
			current = current->next;
			prev = prev->next;
		}

		current->data = prev->data;
		m_tail->prev = current;
	}
	else
	{
		clear();

		m_size = other.m_size;

		Node* origin; 
		Node* copy;
		Node* prev;
		origin = other.m_head->next;

		//EXPERIMENTAL.
		Node* node_principal = new Node;
		copy = node_principal;
		m_head->next = copy;

		while(origin->next != nullptr)
		{

			Node* new_node = new Node;
			prev = copy;

			copy->data = origin->data;
			copy->next = new_node;


			if(copy == m_head->next)
			{
				copy->prev = nullptr;
				copy = copy->next;
				origin = origin->next;
			}
			else
			{
				copy = copy->next;
				origin = origin->next;
				copy->prev = prev;
			}
		}
	
		copy->data = origin->data;
		copy->prev = prev;
		m_tail->prev = copy;
	}

	return *this;
	
}

template<typename T>
list<T> & list<T>::operator=( std::initializer_list<T> ilist )
{
	// Nas duas linhas seguintes, temos a limpeza dos elemento da lista "velha" e a outra a atribuição do tamanho
	clear();
	m_size = ilist.size();
	
	for(size_t i = 0; i < ilist.size(); i++){
		{
			Node *new_node = new Node();

			new_node->data = *( ilist.begin()+i);

			new_node->next = m_head->next;
			m_head->next->prev = new_node;
			m_head->next = new_node;
		
		}
	}
	// Aqui eu tive o entendimento de que é semelhante à copia de lista inicializadora,porém
	// nesta função se atribuída e não copiada,por isso se é utilizado o clear mas não precisa deletar o heada nem o tail,
	// pois os valores dessa lista inicializadora seram jogada nessa lista "vazia"
	return *this;
}

template <typename T>
typename list<T>::iterator list<T>::begin(){
	return iterator(m_head->next);
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const{
	return const_iterator(m_head->next);
}

template <typename T>
typename list<T>::iterator list<T>::end(){
	return iterator(m_tail);
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() const{
	return const_iterator(m_tail);
}

template<typename T>
size_t list<T>::size() const
{
	return m_size;
}

// limpeza de toda lista
template<typename T>
void list<T>::clear()
{
	while( m_head->next != m_tail){
		pop_front();
	}


}

// checa se está vazia
template<typename T>
bool list<T>::empty() const
{
	if( m_size == 0){
		return true;
	}
	return false;
}

// mostra o último elemento da lista
template<typename T>
const T & list<T>::back() const
{
	return (m_tail->prev->data);
}

// mostra o primeiro elemento da lista
template<typename T>
const T & list<T>::front() const
{
	return (m_head->next->data);
}


template<typename T>
bool list<T>::operator==(const list& rhs )
{
	// operator de checagem de duas lista se são iguais ou não baseado no tamanho e no conteúdo de cada node
	if(this->m_size != rhs.m_size)
	{
		return false;
	}
	else
	{
		Node* current;
		Node* rhs_current;

		rhs_current = rhs.m_head->next;
		current = m_head->next;
		
		while(current != nullptr)
		{
			if(current->data != rhs_current->data)
			{
				return false;
			}

			current = current->next;
			rhs_current = rhs_current->next;
		}

		return true;
	}
}

template<typename T>
bool list<T>::operator!=(const list& rhs )
{
	// analogamente ao operator ==,porém para diferença
	if(this->m_size != rhs.m_size)
	{
		return true;
	}
	else
	{
		Node* current;
		Node* rhs_current;

		rhs_current = rhs.m_head->next;
		current = m_head->next;
		
		while(current != nullptr)
		{
			if(current->data != rhs_current->data)
			{
				return true;
			}

			current = current->next;
			rhs_current = rhs_current->next;
		}

		return false;
	}
}

template <typename T>
void list<T>::push_front(const T & value){
	Node * current = new Node();

	// Aqui foi ratificado a tratação do prev.A maneira é análoga à adição de nós
	//que fiz nos construtores e em outras funções que necessitavam dessas adições
	current->data = value;
	current->next = m_head->next;
	(m_head->next)->prev = current;
	m_head->next = current;
	current->prev = m_head;

	//incrementa o tamanho da lista
	this->m_size++;

}

template <typename T>
void list<T>::push_back(const T & value){
	Node * current = new Node;

	current->data = value;
	current->prev = m_tail->prev;
	(m_tail->prev)->next = current;
	m_tail->prev = current;
	current->next = m_tail;

	this->m_size++;
// Quase igual ao push front,porém é tudo de trás para frente por ser duplamente encadeada
}

template <typename T>
void list<T>::pop_back(){
	
	if( empty() == false ){
		Node * current;
		//É criado um novo nó que servirar para "iterar" e deletar o nó no fim da lista	
		current = m_tail->prev;
		m_tail->prev = current->prev;
		(current->prev)->next = m_tail;

		delete current;
		//reduz o tamanho
		m_size--;
	}
}

template <typename T>
void list<T>::pop_front(){
	if( empty() == false ){
		Node * current;
		//É criado um novo nó que servirar para "iterar" e deletar o nó no fim da lista	
		current = m_head->next;
		m_head->next = current->next;
		(current->next)->prev = m_head;

		delete current;
		//reduz o tamanho
		this->m_size--;
	}
	// Bem semelhante ao pop_back,com a diferença de ser de trás para frente por ser também duplmaente encadeada
}

template <typename T>
void list<T>::assign( const T & value){
	// função que sobrescreve os valores de uma lista

	auto current(m_head->next);
	// checagem de se está vazia
	if(m_head->next == m_tail){
		std::cout << " It's empty";
	// node que servirá para receber esses valores
	}else{
		while ( current != m_tail ){
			current->data = value;
			current = current-> next;
		}
	}
	

}



template <typename T>
template <class InItr>
void list<T>::assign (InItr first, InItr last){
	// precorrendo a lista e sobrescrevendo utilizando dois iteradores
	// sendo o it para o contéudo em si , e o aux para os compartimentos
	clear();

	Node * new_node = new Node();
	m_size = std::distance(first,last);
	auto current = m_head;

	for(auto i(0u); i < m_size ; i++){
		new_node = new Node(*first, current);
		current->next = new_node;
		current = new_node;
		first++;
	}

	current->next = m_tail;
	m_tail->prev = current;

}

template <typename T>
void list<T>::assign( std::initializer_list<T> ilist){
 	// bem semelhante as funções anteriores com alteração no laço de acordo com o que se necessita
	typename list<T>::iterator aux = begin();

	for( auto it = ilist.begin(); it != ilist.end() ; it++){
		(*aux)->data = *(it);
		aux++;
	}
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator itr, const T & value){
	// setando um "nó iterador" para manipular de acordo com a lista duplamente encadeada
	Node *new_itr = itr.current;
	// inserido caso seja em uma posição "fácil"
	if( itr == end() ){
		push_back(value);
		return iterator(new_itr->next);
	
	}else if( itr == begin() ){
		push_front(value);
		return iterator(new_itr->prev);
	}
	// caso esteja entre o begin e end,então é inserido de maneira adequada a duplamente encadeada:

	Node *new_node = new Node();
	new_node->data = value;
	new_node->next = (new_itr->prev)->next;
	new_node->prev = new_itr->prev;
	(new_itr->prev)->next = new_node;
	new_itr->prev = new_node;
	//aumenta a lista
	m_size++;

	return iterator(new_node->next);

}

template <typename T>
template < typename InItr>
typename list<T>::iterator list<T>::insert( iterator pos, InItr first, InItr last ){

	// criando o tamanho do size pra utilizar no laço
	auto size = std::distance(first,last);
	// setando os nos de tal forma que posso manipular o inserimento no meio da lista
	auto save_pos = iterator(pos.current->prev);
	save_pos.current->next = pos.current->next;
	Node * new_node;
	// o dummy é necessário para contrução dos nós na iteração
	auto dummy = pos.current->prev;

	for( auto i(0u); i < size; i++){
	
		new_node = new Node( *first, dummy);
		dummy->next = new_node;
		dummy = new_node;

		first++;
	}
	
	pos.current->prev = dummy;
	dummy->next = pos.current;

	return iterator(save_pos.current->next);

	
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,std::initializer_list<T> ilist){
	auto save_pos = iterator(pos.current->prev);
	save_pos.current->next = pos.current->next;
	
	Node * new_node;
	auto first = ilist.begin();

	auto distance = std::distance(first,ilist.end());

	auto current_node = pos.current->prev;
// semelhante aos outros insert,com a diferença de adaptar o ranger 
	for( auto i = 0 ; i < distance; i++){
		new_node = new Node(*first,current_node);
		current_node->next = new_node;
		current_node = new_node;
		first++;
	}

	current_node->next = pos.current;
	pos.current->prev = current_node;

	m_size += distance;

	return iterator(save_pos.current->next);

}

template <typename T>
typename list<T>::iterator list<T>::erase(iterator itr){
	auto new_itr_before = itr.current->prev;
	auto new_itr_after = itr.current->next;
	
	itr.current->next = nullptr;
	itr.current->prev = nullptr;
	// foi criado um iterador que fica após ao elemento que irá ser apagado
	// e a seguir será "retirado" o slot da lista
	new_itr_before->next = new_itr_after;
	new_itr_after->prev = new_itr_before;
	// deleta-se o ponteiro que aponta para o local que foi retirado
	delete itr.current;
	m_size--;

	return iterator(new_itr_after);
	
}


// erase que deleta os elementos no intervalo [first ; end)
template <typename T>
typename list<T>::iterator list<T>::erase(iterator first, iterator last){
	auto current_first = first.current;
	auto itr = current_first->prev;
// utilizei um node que pega o node do priemiro iterator afim de usá-lo para percorrer a lista
	auto current_last = last.current;
// e esse também para o último
	while( current_first != current_last ){
		auto itr_next = current_first->next;
// atribuí para o current_first e o current_last para manipular eles e deletar o first
// avançando de acordo com a lisa duplamente encadeada
		current_first->prev->next = current_first->next;
        current_first->next->prev = current_first->prev;

        current_first->next = nullptr;
		current_first->prev = nullptr;

		delete current_first;

		m_size--;

		current_first = itr_next;

	} 

	return iterator(itr->next);
	/* ou poderia ter feito assim também,mas também dá falha de segmentação
	while( first!= last){
		this->erase(first);
	}
	return last;
	*/
}

// função find que procura value utilizando const_iterator
template <typename T>
typename list<T>::const_iterator list<T>::find(const T & value) const{
	typename list<T>::const_iterator it = cbegin();
	// é utilizado um const iterator pois é passado como parâmetro
	while( it != cend()){
		if((*it)->data == value){
			return (*it);
		}
		it++;
	}

	return nullptr;
}	



//======================== CONST ITERATOR ===============================================
template <typename T>
list<T>::const_iterator::const_iterator() : current(nullptr){}

template <typename T>
const T& list<T>::const_iterator::operator*() const{
	
	return current->data;
}


template <typename T>
typename list<T>::const_iterator & list<T>::const_iterator::operator++(){
	
	current = current->next;

	return *this;
}

template <typename T>
typename list<T>::const_iterator list<T>::const_iterator::operator++(int){
	// por ser um inteiro como parâmetro, é necessário uma "conversão"
	auto stand = *this;
	// o ++ é o proprio next que está próximo do nó
	current = current->next;
	
	return stand;
}

template <typename T>
typename list<T>::const_iterator & list<T>::const_iterator::operator--(){
	// o -- é o proprio prev que está antes do nó	
	current = current->prev;
		
	return *this;
}

template <typename T>
typename list<T>::const_iterator list<T>::const_iterator::operator--(int){
		
	auto stand = *this ;
	
	current = current->prev;
	
	return stand;
}

template <typename T>
bool list<T>::const_iterator::operator==(const const_iterator & rhs ) const {
		
	return current == rhs.current;

}

template <typename T>
bool list<T>::const_iterator::operator!=(const const_iterator & rhs ) const {
	
	return current != rhs.current;

}

// =============================== ITERATOR ===================================
	
template <typename T>
T& list<T>::iterator::operator*() const{
	
	return this->current->data;

}

template <typename T>
T& list<T>::iterator::operator*(){
	
	return this->current->data;
}

template <typename T>
typename list<T>::iterator & list<T>::iterator::operator++(){
		
	this->current = this->current->next;

	return *this;
	
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator++(int){
	
	auto stand = *this;
	this->current = this->current->next;

	return stand;
}

template <typename T>
typename list<T>::iterator & list<T>::iterator::operator--(){

	this->current = this->current->prev;

	return *this;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator--(int){
		
	auto stand = *this ;
	this->current = this->current->prev;

	return stand;
}

// ====== sobrecarregar o operator << ==============

template<typename T>
std::ostream & operator<<(std::ostream & out, const list<T>& lst ){
	// operator que apenas leio o que está após << e faço o operator capaz de ler mesmo sendo uma lista
	// o que ,por padrão, não ocorreria sem uma biblioteca que habilitasse isso
	auto current = lst.m_head->next;
	std::cout << "[";

	if( current == lst.m_tail){
		std::cout << "empty";
	}else{
		while( current != lst.m_tail ){
			std::cout << current->data << " ";
			current = current->next;
		}
	}

	std::cout << "]\n";
	return out;
}

}
