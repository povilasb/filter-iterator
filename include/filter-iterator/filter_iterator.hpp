#ifndef FILTER_ITERATOR_HPP
#define FILTER_ITERATOR_HPP

#include <iterator>


namespace nonstd
{
namespace iterator
{

namespace impl
{

	/**
	 * Default predicate that always returns true.
	 */
	template <typename TIterator>
	struct default_unary_predicate {
		bool
		operator()(const typename std::iterator_traits<TIterator>
			::value_type&)
		{
			return true;
		}
	};
} // namespace impl.


/**
 * Filter iterator template that allows to iterate forward skipping
 * items that do not satisfy the specified predicate.
 */
template <typename ForwardIterator, typename UnaryPredicate
	= impl::default_unary_predicate<ForwardIterator> >
class filter_iterator
	: public std::iterator<
		typename std::iterator_traits<ForwardIterator>::iterator_category,
		typename std::iterator_traits<ForwardIterator>::value_type
		> {
public:
	filter_iterator(ForwardIterator begin, ForwardIterator end,
		UnaryPredicate predicate
			= impl::default_unary_predicate<ForwardIterator>())
		: begin_(begin), end_(end), iter_(begin), predicate_(predicate)
	{
		if ((this->iter_ != this->end_)
			&& !this->predicate_(*this->iter_)) {
			this->increment();
		}
	}


	/**
	 * This constructor is meant for end iterator construction.
	 */
	filter_iterator(ForwardIterator end) : begin_(end), end_(end),
		iter_(end), predicate_(UnaryPredicate())
	{
	}


	typename std::iterator_traits<ForwardIterator>::reference
	operator*() const
	{
		return *this->iter_;
	}


	/**
	 * Converts filter iterator to it's original iterator.
	 */
	operator ForwardIterator() const
	{
		return this->iter_;
	}


	/**
	 * Compares filter iterator with it's original forward iterator.
	 */
	bool
	operator==(const ForwardIterator& it) const
	{
		return this->iter_ == it;
	}


	/**
	 * Compares if filter iterator does not point to the same element
	 * as the specified iterator does.
	 */
	bool
	operator!=(const ForwardIterator& it) const
	{
		return !this->operator==(it);
	}


	/**
	 * Advances iterator until the predicate is true.
	 *
	 * @return reference to advanced iterator.
	 */
	filter_iterator<ForwardIterator, UnaryPredicate>&
	operator++()
	{
		this->increment();
		return *this;
	}


	/**
	 * @return pointer to item pointed by the iterator.
	 */
	typename std::iterator_traits<ForwardIterator>::pointer
	operator->() const
	{
		return this->iter_.operator->();
	}


private:
	ForwardIterator begin_;
	ForwardIterator end_;
	ForwardIterator iter_;
	UnaryPredicate predicate_;


	/**
	 * Increments iterator until it satisfies the predicate.
	 */
	void increment()
	{
		while ((this->iter_ != this->end_)
			&& !this->predicate_(*(++this->iter_))) {
		}
	}
};

} // namespace iterator.
} // namespace nonstd.

#endif /* FILTER_ITERATOR_HPP */
