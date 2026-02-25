#pragma once
#include "document.hpp"


namespace sale_doc
{
	class products_document : public document<size_t_from_string, size_t_from_string, std::string>
	{
	public:
		products_document() = default;
	};
} // namespace sale_doc
