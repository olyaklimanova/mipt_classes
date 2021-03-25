#include <algorithm>
#include <future>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <vector>
#include "thread_guard.hpp"
#include "Timer.hpp"


template < typename Iterator, typename T >
struct accumulate_block
{
	T operator()(Iterator first, Iterator last)
	{
		return std::accumulate(first, last, T());
	}
};

template < typename Iterator, typename T >
T parallel_accumulate(Iterator first, Iterator last, T init, const std::size_t user_advice_for_threads)
{
	const std::size_t length = std::distance(first, last);

	if (!length)
		return init;

	const std::size_t min_per_thread = 10000;
	const std::size_t max_threads =
		(length + min_per_thread - 1) / min_per_thread;

	const std::size_t num_threads =
		std::min(user_advice_for_threads, max_threads);

	const std::size_t block_size = length / num_threads;

	std::vector < std::future < T > > futures(num_threads - 1);
	std::vector < std::thread >		  threads(num_threads - 1);

	Threads_Guard guard(threads);



	Iterator block_start = first;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size);

		std::packaged_task < T(Iterator, Iterator) > task{
			accumulate_block < Iterator, T >() };

		futures[i] = task.get_future();
		threads[i] = std::thread(std::move(task), block_start, block_end);

		block_start = block_end;
	}

	T last_result = accumulate_block < Iterator, T >()(block_start, last);

	T result = init;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		result += futures[i].get();
	}

	result += last_result;

	return result;
}

int main(int argc, const char* argv[])
{
	std::stringstream convert(argv[1]); // создаем переменную stringstream с именем convert, инициализируя её значением argv[1]

	int number_of_threads = static_cast<int>(*argv[1]);
	if (!(convert >> number_of_threads)) // выполняем конвертацию
		number_of_threads = 0;

	std::fstream file_out("data.csv", std::ios::app | std::ios::out);
	std::fstream file_in("data.csv", std::ios::in);

	file_in.seekg(0);
	if (file_in.peek() != 'A')
		file_out << "A,B" << std::endl;


	std::vector < int > v(1000000);

	std::iota(v.begin(), v.end(), 1);

	//std::cout << parallel_accumulate(v.begin(), v.end(), 0, number_of_threads) << std::endl;
	std::size_t duration;

	{
		Timer_with_return<std::chrono::microseconds> dur(duration);
		parallel_accumulate(v.begin(), v.end(), 0, number_of_threads);
	}

	file_out << number_of_threads << "," << duration << std::endl;

	return EXIT_SUCCESS;
}