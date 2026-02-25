#pragma once
#include <string>
#include "type_traits.hpp"


namespace sale_doc
{
	using string_type		= std::wstring;
	using stringstream_type = std::wstringstream;
	using ifstream_type		= std::wifstream;
	class size_t_from_string;

	using document_accepted_types = std::tuple<size_t_from_string, string_type>;
	template<class... Types>
		requires is_all_types_any_of_v<std::tuple<Types...>, document_accepted_types>
	class document;
	struct products_document;
	struct sale_rules_document;
} // namespace sale_doc
#include "size_t_from_string.hpp"
