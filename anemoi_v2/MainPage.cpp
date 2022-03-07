#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include "TableLookup.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::anemoi_v2::variables {
    Lookup::TableLookup table;
}


namespace winrt::anemoi_v2::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        throw hresult_not_implemented();
        //myButton().Content(box_value(L"Clicked"));
    }
}


void winrt::anemoi_v2::implementation::MainPage::inputButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
    if (inputValue().Text().empty()) {
        validationMessage().Text(L"Input Invalid !");
        return;
    }
    validationMessage().Text(L"");

    const auto propertyType = propertiesType().SelectedItem().as<Controls::ComboBoxItem>().Content().as<winrt::hstring>();
    const auto propertyValue = std::stod(to_string(inputValue().Text()));

    std::vector<std::string> properties{ "Temperature", "Enthalpy", "Relative Pressure", "Internal Energy", "Relative Volume", "Entropy" };
    Lookup::PropertyNames Pn = Lookup::PropertyNames::T;
    for (int i = 0; i < properties.size(); ++i) {
        if (properties[i] == to_string(propertyType))
            Pn = static_cast<Lookup::PropertyNames>(i);
    }

    try
    {
        const auto [temperature, enthalpy, relativePressure, internalEnergy, relativeVolume, entropy] = winrt::anemoi_v2::variables::table.Lookup(Pn, propertyValue);

        TemperatureValue().Text(to_hstring(temperature));
        EnthalpyValue().Text(to_hstring(enthalpy));
        RelativePressureValue().Text(to_hstring(relativePressure));
        InternalEnergyValue().Text(to_hstring(internalEnergy));
        RelativeVolumeValue().Text(to_hstring(relativeVolume));
        EntropyValue().Text(to_hstring(entropy));
    }
    catch (const std::invalid_argument& except)
    {
        validationMessage().Text(to_hstring(except.what()) );
    }

     
}


