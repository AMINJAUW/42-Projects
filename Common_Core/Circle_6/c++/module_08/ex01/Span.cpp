#include "Span.hpp"

Span::Span(void) : _size(0)
{
}

Span::~Span(void) 
{
}

Span::Span(Span const & cpy) : _size(cpy._size)
{
	for (std::size_t i = 0; i < cpy._v.size(); ++i)
	{
		this->addNumber(cpy._v[i]);
	}
}

Span & Span::operator=(Span const & rhs) {

	this->_v.clear();
	for (std::size_t i = 0; i < rhs._v.size(); ++i)
	{
		this->addNumber(rhs._v[i]);
	}
	return *this;
}

Span::Span(const unsigned int size) : _size(size)
{
}

int	Span::shortestSpan(void) const
{
	size_t size = this->_v.size();
	if (size < 2)
		throw Span::NotEnoughNumbersForSpanCalculation();
	std::vector<int> copy = this->_v;
	std::sort(copy.begin(), copy.end());
	int x = copy[1] - copy[0];
	for (size_t i = 1; i < size - 1; ++i)
	{
		if (x > copy[i + 1] - copy[i])
			x = copy[i + 1] - copy[i];
	}
	return (x);
}

int Span::longestSpan(void) const
{
	size_t size = this->_v.size();
	if (size < 2)
		throw Span::NotEnoughNumbersForSpanCalculation();
	std::vector<int> copy = this->_v;
	std::sort(copy.begin(), copy.end());
	return (copy[size - 1] - copy[0]);
}

const char *Span::FilledSpan::what() const throw()
{
	return "Your span is filled ! you cannot add more to it !";
}

const char *Span::NotEnoughNumbersForSpanCalculation::what() const throw()
{
	return "You dont have enough numbers to do a span calculation";
}

void	Span::addNumber(int i)
{
	if (this->_v.size() == this->_size)
		throw Span::FilledSpan();
	this->_v.push_back(i);
}

std::vector<int> Span::getArr() const
{
	return this->_v;
}

std::ostream & operator<<(std::ostream & o, const Span & rhs)
{
	o << "(";
	std::vector<int> v = rhs.getArr();
	for (size_t i = 0; i < v.size(); ++i)
	{
		o << v[i];
		if (i != v.size() - 1)
			o << ", ";
	}
	o << ")";
	return o;
}