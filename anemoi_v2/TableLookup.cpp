#include "pch.h"
#include "TableLookup.h"
#include "AirProperties.h"
#include <stdexcept>

namespace Lookup
{

    PropertyValue TableLookup::Lookup(PropertyNames Pn, double value)
    {
        const auto numData = 121;
        int propertyOffset = as_int(Pn) * numData;
        int index = 0;
        if (Pn == PropertyNames::vr) {
            for (index; propertyOffset + index < propertyOffset + numData; ++index) {
                if (airProperties[propertyOffset + index] < value)
                    break;
            }
            if (index >= numData || !index) {
                printf("Value is outside table");
                throw std::invalid_argument("Value is outside table");
            }
        }
        else {
            for (index; propertyOffset + index < propertyOffset + numData; ++index) {
                if (airProperties[propertyOffset + index] > value)
                    break;
            }
            if (index >= numData || !index) {
                printf("Value is outside table");
                throw std::invalid_argument("Value is outside table");
            }
        }
        

        double difference = (airProperties[propertyOffset + index] - airProperties[propertyOffset + index - 1]);
        double fraction = (double)(value - airProperties[propertyOffset + index - 1]) / difference;

        double temperature = getValueFromIndex(PropertyNames::T, index, fraction);
        double enthalpy = getValueFromIndex(PropertyNames::h, index, fraction);
        double relativePressure = getValueFromIndex(PropertyNames::pr, index, fraction);
        double internalEnergy = getValueFromIndex(PropertyNames::u, index, fraction);
        double relativeVolume = getValueFromIndex(PropertyNames::vr, index, fraction);
        double entropy = getValueFromIndex(PropertyNames::s, index, fraction);

        return PropertyValue{ temperature, enthalpy, relativePressure, internalEnergy, relativeVolume, entropy };
    }

    inline double TableLookup::getValueFromIndex(PropertyNames Pn, int index, double fraction)
    {
        const auto numData = 121;
        return airProperties[as_int(Pn) * numData + index - 1] + fraction * (airProperties[as_int(Pn) * numData + index] - airProperties[as_int(Pn) * numData + index - 1]);
    }

    std::array<double, 726>& TableLookup::airProperties = tables::airTable;

}
