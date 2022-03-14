//
// Created by Hintay on 2022/3/11.
//

#ifndef CTRANSPORT_ALGORITHM_HPP
#define CTRANSPORT_ALGORITHM_HPP

#include <string>
#include <vector>

enum class endian {
    little = 0,
    big = 1,
    native = little
};

template<class C, typename V, endian Endian = endian::native>
	requires std::integral<V>
class CRCAlgorithm {
public:
    using ValueType = V;

	virtual ~CRCAlgorithm() = default;

	template<typename... T>
    C& add(T... fragments) {
        for (auto frag : { fragments... }) {
            this->add(frag);
        }
        return *static_cast<C*>(this);
    }

    template<typename T>
    requires (
        std::is_same_v<T, std::string> ||
        std::is_same_v < T, std::vector<char>>
        )
    C& add(const T& data)
	{
        this->add(data.data(), data.size());
        return *static_cast<C*>(this);
    }

    template<typename T>
    requires (std::is_integral_v<T>)
    C& add(T data)
    {
        this->add(static_cast<char*>(data), sizeof(data));
        return *static_cast<C*>(this);
    }
    virtual C& add(const char* data, size_t length) = 0;

    virtual bool check_residue() { return this->value_ == 0;  }

	explicit virtual operator ValueType () const { return this->value_; }

    template<typename T>
    requires (std::is_integral_v<T>)
    explicit operator T () const
	{
        return static_cast<T>(this->value_);
	}

    template<typename T>
    requires (
        std::is_same_v<T, std::string> ||
        std::is_same_v<T, std::vector<char>>
        )
    explicit operator T () const
    {
        auto value = static_cast<ValueType>(*this);
        auto first = reinterpret_cast<char*>(&value);
        auto last = first + sizeof value;
        if constexpr (Endian == endian::little)
			return T(first, last);
        else
            return T(std::reverse_iterator(last), std::reverse_iterator(first));
    }

    ValueType value() { return static_cast<ValueType>(*this); }
    std::string value_as_string() { return static_cast<std::string>(*this); }
    std::vector<char> value_as_vector() { return static_cast<std::vector<char>>(*this); }
    
protected:
    ValueType value_ = 0;
};

#endif //CTRANSPORT_ALGORITHM_HPP
