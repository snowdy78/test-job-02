#pragma once
#include <string>
#include "size_t_from_string.hpp"
#include "type_traits.hpp"


namespace sale_doc
{
	class size_t_from_string;

	using document_accepted_types = std::tuple<size_t_from_string, std::string>;
	template<class... Types>
		requires is_all_types_any_of_v<std::tuple<Types...>, document_accepted_types>
	class document;
	struct products_document;
	struct sale_document;
} // namespace sale_doc
