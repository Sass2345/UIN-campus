#include "uincampus/calculs.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <span>

namespace uin {

double somme(std::span<const double> valeurs)
{
    return std::accumulate(valeurs.begin(), valeurs.end(), 0.0);
}

double moyenne(std::span<const double> notes)
{
    return somme(notes) / static_cast<double>(notes.size());
}

double moyenne(std::span<const double> notes, std::span<const double> coefficients)
{
    double produit{};
    for (std::size_t i = 0; i < notes.size(); ++i) {
        produit += notes[i] * coefficients[i];
    }
    return produit / somme(coefficients);
}

Statistiques calculerStatistiques(std::span<const double> notes)
{
    const auto [minIt, maxIt] = std::minmax_element(notes.begin(), notes.end());
    const double moy = moyenne(notes);

    double sommeCarres{};
    for (double note : notes) {
        const double ecart = note - moy;
        sommeCarres += ecart * ecart;
    }

    const double variance = sommeCarres / static_cast<double>(notes.size());
    return Statistiques{
        .minimum = *minIt,
        .maximum = *maxIt,
        .moyenne = moy,
        .ecartType = std::sqrt(variance),
    };
}

int compterValidees(std::span<const double> notes, double seuil)
{
    return static_cast<int>(std::count_if(notes.begin(), notes.end(),
                                          [seuil](double note) { return note >= seuil; }));
}

double arrondir(double valeur, int decimales)
{
    const double facteur = std::pow(10.0, decimales);
    return std::round(valeur * facteur) / facteur;
}

} // namespace uin