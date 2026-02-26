#pragma once

#include <vector>
#include "saledocumentsfwd.hpp"

namespace sale_doc
{
	/**
	 * @brief класс, который создает вектор из строки
	 *
	 */
	template<class T, char_type Sep>
	class vector_from_string : public std::vector<T>
	{
	public:
		using std::vector<T>::vector;
		/**
		 * @brief создает вектор из объектов
		 *
		 * @param str
		 */
		vector_from_string(const string_type &str)
		{
			istringstream_type ss(str);
			T t;
			string_type word;
			char_type delimiter = Sep;
			while (std::getline(ss, word, delimiter))
			{
				this->push_back(word);
			}
		}
	};
	template<class T>
	inline ostream_type &operator<<(ostream_type &os, const vector_from_string<T> &value)
	{
		auto last = --value.end();
		for (auto i = value.begin(); i != value.end(); ++i)
			os << *i << (i == last ? ' ' : ',');
		return os;
	}
} // namespace sale_doc
