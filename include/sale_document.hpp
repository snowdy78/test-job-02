#pragma once
#include "document.hpp"

namespace sale_doc
{
	struct sale_document : document<std::string, size_t_from_string>
	{};
} // namespace sale_doc
