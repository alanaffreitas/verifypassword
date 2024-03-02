#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>

class PasswordEvaluator {
public:
    // Método para avaliar a complexidade da senha e fornecer feedback
    static std::tuple<std::string, std::vector<std::string>> evaluatePasswordComplexity(const std::string& password) {
        const std::vector<std::pair<std::string, std::function<bool(const std::string&)>>> criteria = {
            {"Critério Comprimento (>= 8 caracteres)", [](const std::string& pw) { return pw.length() >= 8; }},
            {"Critério Letras Minúsculas", [](const std::string& pw) { return std::any_of(pw.begin(), pw.end(), ::islower); }},
            {"Critério Letras Maiúsculas", [](const std::string& pw) { return std::any_of(pw.begin(), pw.end(), ::isupper); }},
            {"Critério Números", [](const std::string& pw) { return std::any_of(pw.begin(), pw.end(), ::isdigit); }},
            {"Critério Caracteres Especiais", [](const std::string& pw) { return std::any_of(pw.begin(), pw.end(), ::ispunct); }}
        };

        int totalScore = 0;
        std::vector<std::string> feedback;

        for (const auto& [description, evaluator] : criteria) {
            if (evaluator(password)) {
                totalScore += 2; // Considerando 2 pontos por critério atendido
                feedback.push_back(description + " atendido.");
            } else {
                feedback.push_back(description + " NÃO atendido.");
            }
        }

        return {classifyPassword(totalScore), feedback};
    }

private:
    static std::string classifyPassword(int totalScore) {
        if(totalScore >= 8) return "Forte";
        else if(totalScore >= 4) return "Média";
        else return "Fraca";
    }
};

int main() {
    std::string password;
    std::cout << "Digite a senha para avaliação: ";
    std::cin >> password;

    auto [complexity, feedback] = PasswordEvaluator::evaluatePasswordComplexity(password);
    std::cout << "Avaliação da Senha: " << complexity << "\nFeedback:\n";

    for (const auto& f : feedback) {
        std::cout << "- " << f << std::endl;
    }

    return 0;
}
