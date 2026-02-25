#pragma once
#include "products_document.hpp"

namespace sale_doc
{
	struct sale_rules_document : document<std::string, size_t_from_string>
	{
		constexpr static size_t item_index	 = 0;
		constexpr static size_t amount_index = 1;
		std::vector<products_document::const_iterator> search(const products_document &products) const;
	};
} // namespace sale_doc
