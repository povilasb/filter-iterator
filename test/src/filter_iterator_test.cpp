#include <vector>
#include <string>
#include <functional>

#include <gmock/gmock.h>

#include <filter-iterator/filter_iterator.hpp>


using namespace ::testing;


// Predicates for testing.


struct odd_number {
	bool
	operator()(int num)
	{
		return (num % 2) != 0;
	}
};


bool
positive_number(int num)
{
	return num >= 0;
}


struct not_empty_string {
	bool
	operator()(const std::string& str)
	{
		return !str.empty();
	}
};


namespace nonstd
{
namespace iterator
{


TEST(filter_iterator_operator_ptr, returns_element_pointed_by_iterator)
{
	std::vector<int> numbers;
	for (unsigned int i = 1; i < 7; ++i) {
		numbers.push_back(i);
	}

	odd_number predicate;
	filter_iterator<std::vector<int>::iterator, odd_number>
		it(numbers.begin(), numbers.end(), predicate);

	ASSERT_THAT(*it, Eq(1));
}


TEST(filter_iterator_create,
	returns_end_iterator_when_provided_begin_iterator_is_end)
{
	std::vector<int> numbers;

	odd_number dummy_predicate;
	filter_iterator<std::vector<int>::iterator, odd_number>
		it(numbers.begin(), numbers.end(), dummy_predicate);

	ASSERT_THAT(it, Eq(numbers.end()));
}


TEST(filter_iterator_create,
	returns_iterator_pointing_to_first_element_satisfying_predicate)
{
	std::vector<int> numbers;
	numbers.push_back(2);
	numbers.push_back(4);
	numbers.push_back(5);

	odd_number predicate;
	filter_iterator<std::vector<int>::iterator, odd_number>
		it(numbers.begin(), numbers.end(), predicate);

	ASSERT_THAT(*it, Eq(5));
}


TEST(filter_iterator_incremenet,
	returns_iterator_pointing_to_first_element_satisfying_predicate)
{
	std::vector<int> numbers;
	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_back(4);
	numbers.push_back(5);

	odd_number predicate;
	filter_iterator<std::vector<int>::iterator, odd_number>
		it(numbers.begin(), numbers.end(), predicate);

	++it;

	ASSERT_THAT(*it, Eq(5));
}


TEST(filter_iterator_dereference, returns_pointer_to_original_iterator_item)
{
	std::vector<std::string> lines;
	lines.push_back("line1");

	not_empty_string predicate;
	filter_iterator<std::vector<std::string>::iterator,
		not_empty_string> it(lines.begin(), lines.end(), predicate);

	ASSERT_THAT(it->c_str(), StrEq("line1"));
}


TEST(filter_iterator_dereference,
	returns_pointer_to_original_iterator_item_with_method_predicate)
{
	std::vector<std::string> lines;
	lines.push_back("line1");

	typedef std::unary_negate<
			std::const_mem_fun_ref_t<bool, std::string>
		> predicate_type;
	predicate_type predicate = std::not1(std::mem_fun_ref(&std::string::empty));

	filter_iterator<std::vector<std::string>::iterator,
		predicate_type> it(lines.begin(), lines.end(), predicate);

	ASSERT_THAT(it->c_str(), StrEq("line1"));
}


TEST(filter_iterator_incremenet,
	advances_iterator_with_function_pointer_as_predicate)
{
	std::vector<int> numbers;
	numbers.push_back(1);
	numbers.push_back(-1);
	numbers.push_back(2);

	filter_iterator<std::vector<int>::iterator, bool(*)(int)>
		it(numbers.begin(), numbers.end(), positive_number);

	++it;

	ASSERT_THAT(*it, Eq(2));
}


TEST(filter_iterator_not_equals_iterator,
	returns_true_when_iterators_do_not_point_to_the_same_item)
{
	std::vector<int> numbers;
	numbers.push_back(1);

	filter_iterator<std::vector<int>::iterator, bool(*)(int)>
		it(numbers.begin(), numbers.end(), positive_number);

	ASSERT_THAT(it != numbers.end(), Eq(true));
}


TEST(filter_iterator_with_default_predicate,
	advances_iterator_in_the_same_fashion_as_original_iterator)
{
	std::vector<int> numbers;
	numbers.push_back(1);
	numbers.push_back(2);

	filter_iterator<std::vector<int>::iterator> it(numbers.begin(),
		numbers.end());

	++it;

	ASSERT_THAT(*it, Eq(2));
}


} // namespace iterator.
} // namespace nonstd.
