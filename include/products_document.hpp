#pragma once
#include "document.hpp"


namespace sale_doc
{
	struct products_document : document<size_t_from_string, size_t_from_string, string_type>
	{
		/**
		 * @brief индекс "позиции" в документе
		 *
		 */
		constexpr static size_t key_index = 0;
		/**
		 * @brief индекс "кол-ва" в документе
		 *
		 */
		constexpr static size_t amount_index = 1;
		/**
		 * @brief индекс "каталог" в документе
		 *
		 */
		constexpr static size_t item_index = 2;
	};
} // namespace sale_doc
