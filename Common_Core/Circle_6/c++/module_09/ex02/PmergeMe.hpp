/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:17:35 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/28 11:49:01 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream> // std::boolalpha
using std::cout;
using std::endl;
using std::cerr;

# include <string>
using std::string;

# include <cmath> // std::ceil, std::log2

# include <cstdlib> // std::atoi

# include <ctime> //std::time

#include <iterator> //std::advance

#include <algorithm> //std::iter_swap

/*		CPP file usefull functions		*/
size_t	Jacobsthal(size_t n);
size_t	uintPow(size_t n, size_t x);
bool	valid_unsigned_number(const char *str);



/*		The Class						*/

template <typename Container>
class PmergeMe {
	
public:
																		
/*~~~~~~~~~~~~~~~~~~~~PUBLIC~~~~~~~~~~~~~~~~~~~~~~~~*/
	
/*______________Cannonical Form____________________*/

	~PmergeMe(void) {};
	
	PmergeMe(int argc, char **argv) : _total_comparaisons(0), _time_taken(0), _len(argc - 1)
	{	
		std::clock_t start, end;
		
		start = std::clock();
		
		fill_check_inputs(argc, argv);	
	
		end = std::clock();
		this->_time_taken += static_cast<double>(end - start) / CLOCKS_PER_SEC;
		
	}

/*______________Accesors____________________*/	

	Container getArray() const 
	{	return this->_array;	}
	
	double getTime_Taken() const
	{	return this->_time_taken;	}

	size_t getComparaison() const 
	{	return this->_total_comparaisons;	}
	
/*______________Sort____________________*/	

	void	sort()
	{
		std::clock_t start, end;

		start = std::clock();
		
		MergeInsert_sort(1);
		
		end = std::clock();
		this->_time_taken += static_cast<double>(end - start) / CLOCKS_PER_SEC;
		
		if (is_sorted() == false)
			cerr << "error not sorted" << endl;
	}


private:
/*~~~~~~~~~~~~~~~~~~~~PRIVATE~~~~~~~~~~~~~~~~~~~~~~~~*/

/*______________Cannonical Form____________________*/

	PmergeMe(PmergeMe const & cpy) { (void)cpy; }
	PmergeMe & operator=(PmergeMe const & rhs) { (void)rhs; return *this; }

/*______________Exception____________________*/

	class WrongInputs : public std::exception
	{
	public:
		const char *what() const throw () {return "wrong inputs for Pmerge me, only posiive integers";}
	};

/*______________Data____________________*/

	size_t				_total_comparaisons;
	double				_time_taken;
	const size_t		_len;
	Container 			_array;
	
/*______________Iterators____________________*/

	typename Container::value_type getElement(Container & arr, const size_t index)
	{
		typename Container::iterator it = getIterator(arr, index);
		return *it;
	}

	typename Container::iterator getIterator(Container & arr, const size_t index)
	{
		typename Container::iterator it = arr.begin();
		std::advance(it, index);
		return it;
	}
	
/*______________Utility____________________*/

	bool is_sorted() //DEBUG USE ONLY
	{
		for (size_t i = 0; i < _len - 1; i++)
		{
			if (getElement(this->_array, i) > getElement(this->_array, i))
				return false;	
		}
		return true;
	}

	size_t	shift_index_bottom_tier(size_t i, size_t move_nbr)
	{
		size_t out = 0;
		int const size = std::log2(move_nbr);
		
		std::bitset<32> bits(i);

		for (int i = 0; i < size; ++i)
		{
			out += bits[i] * (this->_len / uintPow(2, size - i));
		}
		return out;		
	}


	void add_end(Container & v, int i)
	{
		v.insert(v.end(), i);
	}

	void swapElements(size_t first, size_t second, size_t move_nbr)
	{
		size_t i = 0;
		while(i < move_nbr)
		{
			size_t shift = shift_index_bottom_tier(i, move_nbr); 
			std::iter_swap(getIterator(this->_array, first + shift), getIterator(this->_array, second + shift));
			i++;
		}		
	}
	
	void	copy_elements_definded_sequence(Container & from, Container & to, size_t index_0, Container & sequence)
	{
		for (size_t i = 0; i < sequence.size(); i++)
		{
			add_end(to, getElement(from, index_0 + getElement(sequence, i) - 1)); // -1 because squence start a 1 not 0
		}
	}


/*______________Initialize____________________*/
	void	fill_check_inputs(int argc, char **argv)
	{
		for (int i = 0; i < argc - 1; ++i)
		{
			if (!valid_unsigned_number(argv[i + 1]))
				throw WrongInputs();
			add_end(this->_array, std::atoi(argv[i + 1]));
		}
	}
	

/*______________MERGE____________________*/

	void	MergeInsert_sort(size_t move_nbr)  
	{
		/*	Recursivity check	*/
		size_t size = this->_len / move_nbr;
		if (size == 1)
			return;
		if (size == 2)
		{
			if (getElement(this->_array, 0) > getElement(this->_array, 1))
				swapElements(0, 1, move_nbr);
			this->_total_comparaisons++;
			return;
		}

		/*	Swap Pairs to see that the biggest element is in front*/
		for (size_t i = 0; i < size / 2; i++)
		{
			if (getElement(this->_array, i) < getElement(this->_array, i + size / 2))
				swapElements(i, i + size / 2, move_nbr);
			this->_total_comparaisons++;
		}
		MergeInsert_sort(move_nbr * 2); // MAGIC <3
		
		insert_algo(move_nbr);
	}

/*______________INSERT____________________*/

	void make_insertionSeq(Container & destination, size_t move_nbr)
	{
		size_t size = std::ceil((this->_len / move_nbr) / 2.0);
		size_t Jacob_iteration = 0;
		size_t last_jacob = 0;
		
		while (size > static_cast<size_t>(Jacobsthal(Jacob_iteration)))
		{
			for (size_t j = Jacobsthal(Jacob_iteration); j > last_jacob; --j)
			{
				add_end(destination, j);
			}
			last_jacob = Jacobsthal(Jacob_iteration);
			++Jacob_iteration;
		}
		while (size > last_jacob)
		{
			add_end(destination, size);
			size--;
		}
	
	}
	
	size_t binairy_search_leftmost(Container Arr, size_t const size, int const number)  // need to check for identical values (but i think it still works)
	{
		size_t left = 0;
		size_t right = size;
		size_t middle;

		while (left < right)
		{
			middle = (left + right) / 2;
			this->_total_comparaisons++;
			if (getElement(Arr, middle) < number)
				left = middle + 1;
			else
				right = middle;
		}
		return left;
	}

	Container *fill_lowerhalf(size_t move_nbr)
	{
		size_t size = this->_len / move_nbr;
		Container insertion_seq;
		make_insertionSeq(insertion_seq, move_nbr);


		Container* lower_half = new Container[move_nbr];

		for (size_t i = 0; i < move_nbr; ++i) // copy all the elements
		{
			copy_elements_definded_sequence(this->_array, lower_half[i], shift_index_bottom_tier(i, move_nbr) + (size / 2), insertion_seq);
		}
		for (int i = move_nbr - 1; i >= 0; --i) // remove them all
		{
			this->_array.erase(
				getIterator(this->_array, shift_index_bottom_tier(i, move_nbr) + (size / 2)),
				getIterator(this->_array, shift_index_bottom_tier(i, move_nbr) + size));
		}

		return lower_half;
	}

	void	insert_first_part(size_t size, Container *lower_half, Container & insertion_index)
	{
		size_t 	Jacob_iteration = 2;
		size_t 	last_jacob = 0;
		size_t	low_size = std::ceil(size / 2.0);
		
		while (low_size >= Jacobsthal(Jacob_iteration))
		{
			size_t rsize = uintPow(2, Jacob_iteration - 1) - 1;
				for (size_t j = Jacobsthal(Jacob_iteration);j > last_jacob; --j)
				{
					size_t insert_index = binairy_search_leftmost(this->_array, rsize, getElement(lower_half[0], 0));
					add_end(insertion_index, insert_index);
					this->_array.insert(getIterator(this->_array, insert_index), getElement(lower_half[0], 0));
					lower_half[0].erase(lower_half[0].begin());
				}
			last_jacob = Jacobsthal(Jacob_iteration);;
			++Jacob_iteration;
		}
		if (low_size != last_jacob)
		{
			size_t rsize = last_jacob + std::ceil(size / 2.0) - 1;
			while (low_size > last_jacob)
			{
				size_t insert_index = binairy_search_leftmost(this->_array, rsize, getElement(lower_half[0], 0));
				add_end(insertion_index, insert_index);
				this->_array.insert(getIterator(this->_array, insert_index), getElement(lower_half[0], 0));
				lower_half[0].erase(lower_half[0].begin());
				low_size--;
			}
		}		
	}

	void	insert_algo(size_t move_nbr)
	{
		size_t size = this->_len / move_nbr;
		
		Container *lower_half = fill_lowerhalf(move_nbr);
		Container insertion_index; 
		
		insert_first_part(size, lower_half, insertion_index);

		for (size_t i = 1; i < move_nbr; i++)
		{
			for (size_t j = 0; j < lower_half[i].size(); j++)
			{
				this->_array.insert(getIterator(this->_array, shift_index_bottom_tier(i, move_nbr) + getElement(insertion_index, j)),
					getElement(lower_half[i], j));
			}
		}
		delete [] lower_half;
		return ;
	}
};


#endif
