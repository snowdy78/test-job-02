#include "sale_rules_document.hpp"
#include <algorithm>
namespace sale_doc
{

	std::vector<products_document::const_iterator> sale_rules_document::search(const products_document &products) const
	{
		std::vector<products_document::const_iterator> result;
		// проходимся по всем каталогам и считаем, какие подходят под условия скидки
		for (auto it_prod = products.begin(); it_prod != products.end(); ++it_prod)
		{
			auto &item		  = std::get<products_document::item_index>(*it_prod);
			auto &item_amount = std::get<products_document::amount_index>(*it_prod);
			auto it			  = std::find_if(begin(), end(), [&](const auto &i) {
				  // под условия скидки подходят те каталоги, что находятся в наборе и соответствуют или превосходят по
				  // количеству за одну позицию
				  return item.find(std::get<item_index>(i)) != std::string::npos
						 && item_amount.get() >= std::get<amount_index>(i).get();
			  });
			if (it != end())
			{
				result.push_back(it_prod);
			}
		}
		return result;
	}
} // namespace sale_doc
