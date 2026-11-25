#include "uincampus/calculs.hpp"
#include "uincampus/regles.hpp"

#include <array>
#include <format>
#include <iostream>
#include <span>

int main()
{
    constexpr std::array<double, 5> notesAlgorithme{14.5, 16.0, 12.0, 15.5, 13.0};
    constexpr std::array<double, 5> coefficients{2.0, 2.0, 1.5, 2.0, 1.0};

    static_assert(notesAlgorithme.size() == coefficients.size(),
                  "Les tableaux de notes et de coefficients doivent avoir la même taille");

    const std::span<const double> vueNotes{notesAlgorithme};
    const std::span<const double> vueCoeffs{coefficients};

    const uin::Statistiques stats = uin::calculerStatistiques(vueNotes);
    const double moyPonderee = uin::moyenne(vueNotes, vueCoeffs);
    const double moyArrondie = uin::arrondir(moyPonderee, 2);
    const uin::Mention mention = uin::mentionPour(moyArrondie);
    const int validees = uin::compterValidees(vueNotes);

    // Exemple de sous-tranche sans copie mémoire : les 3 premières évaluations
    const std::span<const double> premieresNotes = vueNotes.first(3);
    const double moyPremieres = uin::arrondir(uin::moyenne(premieresNotes), 2);

    std::cout << std::format(
        "UIN-Campus — Synthèse des notes\n"
        "  Min / Max / Écart-type : {:.2f} / {:.2f} / {:.2f}\n"
        "  Moyenne pondérée       : {:.2f} ({})\n"
        "  Épreuves validées      : {} / {}\n"
        "  Moyenne 3 premières    : {:.2f}\n",
        stats.minimum,
        stats.maximum,
        stats.ecartType,
        moyArrondie,
        uin::libelle(mention),
        validees,
        static_cast<int>(vueNotes.size()),
        moyPremieres);

    return 0;
}