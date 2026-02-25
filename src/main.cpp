#include "saledocuments.hpp"
#include <clocale>
/*
 * Нейминг приложения выбрал такой из-за примера со скидкой на товары
 */

template<class... Types>
std::wostream &operator<<(std::wostream &outstream, const std::tuple<Types...> &t)
{
	std::apply(
		[&outstream](auto &&...args) {
			((outstream << args << " "), ...);
		},
		t
	);
	return outstream;
}

template<class... Types>
std::wostream &operator<<(std::wostream &outstream, const sale_doc::document<Types...> &doc)
{
	for (auto &t: doc)
		outstream << t << "\n";
	return outstream;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	sale_doc::products_document products;
	sale_doc::sale_rules_document sale_rules;
	sale_rules.parse("kit.txt");
	products.parse("document.txt");
	std::wcout << L"Содержимое документа продуктов:\n";
	std::wcout << products << std::endl;
	std::wcout << L"Содержимое набора скидок:\n";
	std::wcout << sale_rules << std::endl;
	auto sales_result = sale_rules.search(products);
	std::wcout << L"Позиции подходящие под условия скидки:\n";
	for (auto &i: sales_result)
	{
		std::wcout << *i << std::endl;
	}
	return 0;
}
