#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <stack>

enum TYPE {
    INTEGER, // 0
    INTEGER_SPECIAL_WORD, // 1
    TEXT, // 2
    EQUAL_OPERATOR, // 3
    SEMICOLON, // 4
    WHITE_SPACE, // 5
    ERR // 6
};

enum TokenType {
    PRIMAL,
    COMPLEX
};

struct Token {
    TYPE type;
    std::string data;
};

bool is_char_in_string(char c, const std::string& str) {
    for (int i = 0; i < str.length(); ++i) {
        if (c == str.at(i))
            return true;
    }
    return false;
}

bool is_valid_integer(const std::string& data) {
    for (int i = 0; i < data.length(); ++i) {
        if (data.at(i) < 48 || data.at(i) > 57)
            return false;
    }
    return true;
}

bool is_valid_text(const std::string& data) { // 97-122 : a-z | 65-90 : A-Z
    for (char i : data) {
      bool is_a_z = i < 97 || i > 122;
      bool is_A_Z = i < 65 || i > 90;

      if (!is_a_z && !is_A_Z)
          return false;
    }
    return true;
}

TYPE get_token_type(const std::string& data) {
    if (data == "=") return EQUAL_OPERATOR;
    else if (data == ";") return SEMICOLON;
    else if (data == " ") return WHITE_SPACE;
    else if (data == "int") return INTEGER_SPECIAL_WORD;
    else if (is_valid_integer(data)) return INTEGER;
    else if (is_valid_text(data)) return TEXT;
    else return ERR;
}


int main() {
    const std::string code{"int abc = 5;"};

    std::stack<char> code_stack;
    std::vector<Token> tokens;

    for (int i = code.length() - 1; i >= 0; --i) {
        code_stack.push(code.at(i));
    }

    std::string data;

    while (!code_stack.empty()) {
        Token token;
        TokenType tokenType;

        char c = code_stack.top();
        code_stack.pop();

        if (is_char_in_string(c, "=;+-*|_-&%7(){}[]! ")) {
            tokenType = PRIMAL;
        } else {
            tokenType = COMPLEX;
        }

        if (tokenType == PRIMAL) {
            if (!data.empty()) {
                token.type = get_token_type(data);
                token.data = data;
                data.clear();
            } else {
                token.type = get_token_type(std::string(1, c));
                token.data = c;
            }
            tokens.push_back(token);
        } else {
            data += c;
        }
    }

    for (int i = tokens.size() - 1; i >= 0; --i) {
        std::cout << "DATA: " << tokens.at(i).data << " TYPE: " << tokens.at(i).type << std::endl;
    }

    return 0;
}
