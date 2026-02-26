#pragma once
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "saledocumentsfwd.hpp"

namespace sale_doc
{
	/**
	 * @brief класс, который умеет парсить текстовый файл, содержащий определенную таблицу с данными
	 *
	 * @tparam Types - типы данных колонок таблицы
	 */
	template<class... Types>
		requires is_all_types_any_of_v<std::tuple<Types...>, document_accepted_types>
	class document
	{
	public:
		using string_type		= sale_doc::string_type;
		using ifstream_type		= sale_doc::ifstream_type;
		using stringstream_type = sale_doc::stringstream_type;
		template<class T>
		using container_type		 = std::vector<T>;
		using value_type			 = std::tuple<Types...>;
		using document_data_type	 = container_type<value_type>;
		using iterator				 = document_data_type::iterator;
		using const_iterator		 = document_data_type::const_iterator;
		using reverse_iterator		 = document_data_type::reverse_iterator;
		using const_reverse_iterator = document_data_type::const_reverse_iterator;

	private:
		/**
		 * @brief количество типов в одной строке таблицы
		 *
		 */
		constexpr static size_t s_types_count = sizeof...(Types);

	private:
		/**
		 * @brief данные документа
		 *
		 */
		document_data_type m_data;

	public:
		document() = default;
		/**
		 * @brief парсит текстовый файл
		 *
		 * @param path_to_document - путь к текстовому документу
		 */
		void parse(const std::string &path_to_document)
		{
			ifstream_type file(path_to_document);
			if (!file.is_open())
				throw std::runtime_error("File not found");
			string_type line;
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
		}
		/**
		 * @brief возвращает количество колонок таблицы
		 *
		 * @return constexpr size_t
		 */
		constexpr static size_t row_size()
		{
			return s_types_count;
		}
		/**
		 * @brief возвращает количество строк таблицы
		 *
		 * @return size_t
		 */
		size_t size() const
		{
			return m_data.size();
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
		 * @brief получает слово по соответствующему номеру в строке
		 * @param word_number - номер слова, которое нужно получить
		 * @param line - строка в которой происходит поиск слова
		 */
		static string_type get_word_from_line(size_t word_number, const string_type &line)
		{
			stringstream_type ss(line);
			string_type word;
			size_t i = 0;
			while (ss >> word)
			{
				if (i == word_number)
					return word;
				i++;
			}
			return {};
		}
		/**
		 * @brief преобразует текстовые данные строки таблицы в соответствующие типы документа
		 *
		 * @param line - строка таблицы
		 * @return value_type
		 */
		static value_type get_data_from_line(const string_type &line)
		{
			value_type row;
			string_type word;
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
