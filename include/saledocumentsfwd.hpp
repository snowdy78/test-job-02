#pragma once
#include <sstream>
#include <string>
#include "type_traits.hpp"


namespace sale_doc
{
	using char_type			 = wchar_t;
	using string_type		 = std::basic_string<char_type>;
	using stringstream_type	 = std::basic_stringstream<char_type>;
	using istringstream_type = std::basic_istringstream<char_type>;
	using ifstream_type		 = std::basic_ifstream<char_type>;
	using ostream_type		 = std::basic_ostream<char_type>;
	class size_t_from_string;
	template<class T, char_type Sep = ','>
	class vector_from_string;
	using document_accepted_types = std::tuple<size_t_from_string, string_type, vector_from_string<string_type>>;
	template<class... Types>
		requires is_all_types_any_of_v<std::tuple<Types...>, document_accepted_types>
	class document;
	struct products_document;
	struct sale_rules_document;
} // namespace sale_doc
