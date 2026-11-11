#include <print>

#include "uincampus/version.hpp"

int main() {
    std::println("UIN-Campus - Système de gestion académique");
    std::println("Version {}", uin::version());
}