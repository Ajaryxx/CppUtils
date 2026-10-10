//MIT License
//
//Copyright(c) 2026 Ajaryxx
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#pragma once
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <cctype>
#include <type_traits>

namespace Utils
{
	enum SpaceRemoveType
	{
		FRONT = 0x01,
		MID = 0x02,
		END = 0x04,
		ALL = 0x08
	};



	class StringUtils final
	{
	public:
		StringUtils() = delete;
		StringUtils(const StringUtils&) = delete;
		StringUtils(StringUtils&&) = delete;

		StringUtils& operator=(const StringUtils&) = delete;


		inline static std::string ToLower(const std::string& str)
		{
			std::string result(str.size(), '\0');
			std::transform(str.begin(), str.end(), result.begin(), [](const unsigned char c) { return static_cast<char>(std::tolower(c)); });
			return result;
		}
		inline static std::string ToUpper(const std::string& str)
		{
			std::string result(str.size(), '\0');
			std::transform(str.begin(), str.end(), result.begin(), [](const unsigned char c) { return static_cast<char>(std::toupper(c)); });
			return result;
		}
		inline static bool IsNegative(const std::string& str)
		{
			if (str.empty())
				return false;

			return str[0] == '-' ? true : false;
		}
		inline static std::string RemoveStringSpaces(const std::string& str, SpaceRemoveType removeType)
		{
			//TODO: continou working on that

			if (str.empty())
				return std::string();

			std::string modifiedString = str;

			if (removeType & SpaceRemoveType::FRONT)
			{
				while (!modifiedString.empty() && modifiedString[0] == ' ')
				{
					modifiedString.erase(0, 1);
				}
			}
			if (removeType & SpaceRemoveType::MID)
			{
				for (size_t i = 0; i < modifiedString.size(); i++)
				{
					
				}
			}
			if (removeType & SpaceRemoveType::END)
			{
				//   asd   asd    
			}
			if (removeType & SpaceRemoveType::ALL)
			{
				for (size_t i = 0; i < modifiedString.size(); i++)
				{
					if (modifiedString[i] == ' ')
						modifiedString.erase(i, 1);
				}
			}

			return std::string();
		}


		//Converts a type like int to string
		template<typename T>
		inline static std::string ValueToString(const T& value);

		//Converts a string to T
		template<typename T>
		inline static T StringToValue(const std::string& value);

	private:
		template<typename T>
		inline static T ConvertStringToIntegral(const std::string& str);

		template<typename T>
		inline static T ConvertToFloatingPoint(const std::string& str);

		template<typename T>
		inline static T ConvertToIntegral(const std::string& str);
	};
}

template<typename T>
std::string Utils::StringUtils::ValueToString(const T& value)
{
	std::stringstream ss;
	if constexpr (std::is_same<T, bool>::value)
	{
		return value ? "true" : "false";
	}
	else if constexpr (std::is_floating_point<T>::value)
	{
		ss << std::setprecision(std::numeric_limits<T>::max_digits10) << value;
	}
	else if constexpr (std::is_integral<T>::value || std::is_same<T, std::string>::value)
	{
		ss << value;
	}
	else
	{
		throw InvalidType("Type: " + std::string(typeid(T).name()) + " is invalid!");
	}
	return ss.str();
}
template<typename T>
inline T Utils::StringUtils::StringToValue(const std::string& str)
{
	T value = T();

	if constexpr (std::is_same<T, bool>::value)
	{
		const std::string lower = ToLower(str);

		if (lower == "true" || lower == "1")
			return true;

		else if (lower == "false" || lower == "0")
			return false;

		else
			throw std::invalid_argument("Couldn't convert string to bool!" + lower);
	}
	else if constexpr (std::is_integral<T>::value)
	{
		value = ConvertToIntegral<T>(str);
	}
	else if constexpr (std::is_floating_point<T>::value)
	{
		value = ConvertToFloatingPoint<T>(str);
	}
	else if constexpr (std::is_same<T, std::string>::value)
	{
		return str;
	}
	else
	{
		std::cerr << "Type: " << typeid(T).name() + " is not supported!\n";
	}

	return value;
}

template<typename T>
inline T Utils::StringUtils::ConvertToFloatingPoint(const std::string& str)
{
	T value = T();
	size_t i = 0;
	if constexpr (std::is_same<T, float>::value)
	{
		value = std::stof(str, &i);
	}
	else if constexpr (std::is_same<T, double>::value)
	{
		value = std::stod(str, &i);
	}
	else if constexpr (std::is_same<T, long double>::value)
	{
		value = std::stold(str, &i);
	}
	if (i != str.size())
		throw std::invalid_argument("Couldn't convert string to: " + std::string(typeid(T).name()));

	return value;
}

template<typename T>
inline T Utils::StringUtils::ConvertToIntegral(const std::string& str)
{
	size_t i = 0;
	T value = T();

	if constexpr (std::is_unsigned<T>::value)
	{
		if (IsNegative(str))
			throw std::out_of_range("Value is out of range!");

		unsigned long long checkValue = std::stoull(str, &i);

		if (checkValue > std::numeric_limits<T>::max())
			throw std::out_of_range("Value is out of range!");

		value = static_cast<T>(checkValue);
	}
	else
	{
		long long checkValue = std::stoll(str, &i);

		if (checkValue < std::numeric_limits<T>::min() || checkValue > std::numeric_limits<T>::max())
			throw std::out_of_range("Value is out of range!");

		value =  static_cast<T>(checkValue);
	}

	if (i != str.size())
		throw std::invalid_argument("Couldn't convert string to: " + std::string(typeid(T).name()));

	return value;
}