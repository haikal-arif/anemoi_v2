#pragma once

#include <array>

namespace Lookup {

	enum class PropertyNames
	{
		T, h, pr, u, vr, s, numProperties
	};

	template <typename Enumeration>
	auto as_int(Enumeration const value)
		-> typename std::underlying_type<Enumeration>::type
	{
		return static_cast<typename std::underlying_type<Enumeration>::type>(value);
	}

	struct PropertyValue
	{
		double temperature;
		double enthalpy;
		double relativePressure;
		double internalEnergy;
		double relativeVolume;
		double entropy;
	};


	class TableLookup
	{
	public:
		PropertyValue Lookup(PropertyNames Pn, double value);


	private:
		static std::array<double, 726>& airProperties;
		double getValueFromIndex(PropertyNames Pn, int index, double fraction);


	};

}