#pragma once
#include <iostream>
#include <string>
#include "saledocumentsfwd.hpp"

namespace sale_doc
{
	/**
	 * @brief класс, который создает size_t из строки
	 *
	 */
	class size_t_from_string
	{
		size_t m_value = 0;

	public:
		size_t_from_string(const string_type &value)
		{
			try
			{
				m_value = value.empty() ? 0 : std::stoul(value);
			}
			catch (std::exception &err)
			{
				std::wcout << "Error: " << err.what() << " (value: " << value << ")\n";
				throw err;
			}
		}
		size_t_from_string(size_t value)
			: m_value(value)
		{}
		size_t_from_string() = default;

		// лень переопределять все операторы, поэтому пусть будет get и set
		void set(size_t value)
		{
			m_value = value;
		}
		const size_t &get() const
		{
			return m_value;
		}
	};
	inline std::wostream &operator<<(std::wostream &os, const size_t_from_string &value)
	{
		return os << value.get();
	}
} // namespace sale_doc
