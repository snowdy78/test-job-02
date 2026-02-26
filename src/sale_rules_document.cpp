#include "sale_rules_document.hpp"
#include <algorithm>
#include "vector_from_string.hpp"
// (Особой надобности в существовании этого source файла нету, просто создал, чтобы хоть один раз он был в проекте)

namespace sale_doc
{
	sale_rules_document::search_result_type sale_rules_document::search(const products_document &products) const
	{
		search_result_type result;
		// проходимся по всему документу и считаем, какие каталоги подходят под условия скидки
		for (auto it_sale = begin(); it_sale != end(); ++it_sale)
		{
			auto &kit_catalogs = std::get<item_index>(*it_sale);
			auto &item_amount  = std::get<amount_index>(*it_sale);
			auto it			   = std::find_if(products.begin(), products.end(), [&](const auto &i) {
				   auto &catalog = std::get<products_document::item_index>(i);
				   // возвращаем true, если под текущей позицией все каталоги из набора есть каталоге документа
				   // и если каталоги в документе соответствуют или превосходят по количеству каталоги из набора
				   return std::all_of(
							  kit_catalogs.begin(), kit_catalogs.end(),
							  [&](const auto &j) {
								  return std::find(catalog.begin(), catalog.end(), j) != catalog.end();
							  }
						  )
						  && item_amount.get() >= std::get<amount_index>(i).get();
			   });
			if (it != products.end())
			{
				result.push_back({ item_amount, std::get<amount_index>(*it), kit_catalogs });
			}
		}
		return result;
	}
} // namespace sale_doc
