#include "saledocuments.hpp"

#ifdef _WIN32
// на Windows Русский текст в терминале работает на C версии библиотеки
#include <clocale>
#elif __linux__
// на Linux Русский текст в терминале работает на STL версии библиотеки
#include <locale>
#endif
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
#ifdef _WIN32
	setlocale(LC_ALL, "Russian");
#elif __linux__
	std::locale::global(std::locale(""));
	std::wcout.imbue(std::locale());
#endif
	sale_doc::products_document products;
	sale_doc::sale_rules_document sale_rules;
	sale_rules.parse("kit.txt");
	products.parse("document.txt");
	std::wcout << L"Содержимое документа продуктов:\n";
	std::wcout << products << std::endl;
	std::wcout << L"Содержимое набора скидок:\n";
	std::wcout << sale_rules << std::endl;
	auto sales_result = sale_rules.search(products);
	std::cout << "Позиции подходящие под условия скидки:\n";
	for (auto &i: sales_result)
	{
		std::wcout << *i << std::endl;
	}
	return 0;
}
