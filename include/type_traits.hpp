#pragma once
#include <tuple>
namespace sale_doc
{
	/**
	 * @brief проверяет, соответствует ли хоть один тип из списка List условию Pred с переданными аргументами Args
	 *
	 * @tparam List - список типов для обработки
	 * @tparam Pred - предикат
	 * @tparam Args - аргументы
	 */
	template<class List, template<class... Args> class Pred, class... Args>
	struct is_any_of
	{
		constexpr static bool value = []<typename... Types>(std::tuple<Types...>) {
			return (Pred<Types, Args...>::value || ...);
		}(List());
	};

	/**
	 * @brief проверяет, все ли типы из списка List соответствуют условию Pred с переданными аргументами Args
	 *
	 * @tparam List - список типов для обработки
	 * @tparam Pred - предикат
	 * @tparam Args - аргументы
	 */
	template<class List, template<class... Args> class Pred, class... Args>
	struct is_all_of
	{
		constexpr static bool value = []<typename... Types>(std::tuple<Types...>) {
			return (Pred<Types, Args...>::value && ...);
		}(List());
	};
	/**
	 * @brief проверяет, все ли типы из списка AllOfList находятся в списке AnyOfList
	 *
	 * @tparam AllOfList
	 * @tparam AnyOfList
	 */
	template<class AllOfList, class AnyOfList>
	struct is_all_types_any_of
	{
		constexpr static bool value = []<class... AllOfTypes>(std::tuple<AllOfTypes...>) {
			return (
				[]<class T, class... AnyOfTypes>(std::tuple<T>, std::tuple<AnyOfTypes...>) {
					return (std::is_same<T, AnyOfTypes>::value || ...);
				}(std::tuple<AllOfTypes>(), AnyOfList())
				&& ...
			);
		}(AllOfList());
	};
	template<class AllOfList, class AnyOfList>
	constexpr bool is_all_types_any_of_v = is_all_types_any_of<AllOfList, AnyOfList>::value;
} // namespace sale_doc
