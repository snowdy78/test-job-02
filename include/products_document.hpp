#pragma once
#include "document.hpp"


namespace sale_doc
{
	struct products_document : document<size_t_from_string, size_t_from_string, std::string>
	{};
} // namespace sale_doc
