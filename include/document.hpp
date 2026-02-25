#pragma once
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "saledocumentsfwd.hpp"


namespace sale_doc
{
	template<class... Types>
		requires is_all_types_any_of_v<std::tuple<Types...>, document_accepted_types>
	class document
	{
		using string_type = std::string;
		template<class T>
		using container_type		 = std::vector<T>;
		using value_type			 = std::tuple<Types...>;
		using document_data_type	 = container_type<value_type>;
		using iterator				 = document_data_type::iterator;
		using const_iterator		 = document_data_type::const_iterator;
		using reverse_iterator		 = document_data_type::reverse_iterator;
		using const_reverse_iterator = document_data_type::const_reverse_iterator;

	private:
		constexpr static size_t s_types_count		   = sizeof...(Types);
		constexpr static char s_cell_separators[]	   = " \t|";
		constexpr static size_t s_cell_separators_size = sizeof(s_cell_separators) - 1;

	private:
		document_data_type m_data;

	public:
		document() = default;

		bool parse(const std::string &path_to_document)
		{
			std::ifstream file(path_to_document);
			if (!file.is_open())
				throw std::runtime_error("File not found");
			std::string line;
			bool skip_first_line = true;
			while (!file.eof())
			{
				std::getline(file, line);
				// пропускаем первую строчку (там только текст)
				if (skip_first_line)
				{
					skip_first_line = false;
					continue;
				}
				if (line.empty())
					continue;
				m_data.push_back(std::move(get_data_from_line(line)));
			}
			file.close();
			return true;
		}
		constexpr static size_t row_size()
		{
			return s_types_count;
		}
		size_t size() const
		{
			return m_data.size();
		}
		void clear()
		{
			m_data.clear();
		}
		const_iterator begin() const
		{
			return m_data.begin();
		}
		const_iterator end() const
		{
			return m_data.end();
		}
		const_reverse_iterator rbegin() const
		{
			return m_data.rbegin();
		}
		const_reverse_iterator rend() const
		{
			return m_data.rend();
		}

	private:
		/**
		 * @brief
		 * @param word_number - номер слова, которое нужно получить
		 * @param line - строка в которой происходит поиск слова
		 */
		static string_type get_word_from_line(size_t word_number, const string_type &line)
		{
			std::stringstream ss(line);
			std::string word;
			size_t i = 0;
			while (ss >> word)
			{
				if (i == word_number)
					return word;
				i++;
			}
			return "";
		}
		static value_type get_data_from_line(const string_type &line)
		{
			value_type row;
			std::string word;
			std::apply(
				[&word, &line](auto &&...args) {
					size_t i = 0;
					((word = get_word_from_line(i++, line), args = word), ...);
				},
				row
			);
			return row;
		}
	};
} // namespace sale_doc
