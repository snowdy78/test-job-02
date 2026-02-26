#pragma once
#include "products_document.hpp"
#include "size_t_from_string.hpp"
namespace sale_doc
{
	struct sale_rules_document : document<string_type, size_t_from_string>
	{
		/**
		 * @brief индекс "каталог" в документе
		 *
		 */
		constexpr static size_t item_index = 0;
		/**
		 * @brief индекс "кол-ва" в документе
		 *
		 */
		constexpr static size_t amount_index = 1;
		/**
		 * @brief осуществляет поиск скидок в документе продуктов
		 *
		 * @param products - документ "продуктов"
		 * @return std::vector<products_document::const_iterator>
		 */
		std::vector<products_document::const_iterator> search(const products_document &products) const;
	};
} // namespace sale_doc
