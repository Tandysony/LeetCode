// Time:  O(4^n)
// Space: O(n)

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> result;
        vector<string> expr;
        addOperatorsDFS(num, target, 0, 0, 0, &expr, &result);
        return result;
    }

    void addOperatorsDFS(const string& s, const int& target, const int& pos,
                         const int& operand1, const int& operand2, vector<string> *expr,
                         vector<string> *result) {
        if (pos == s.length()) {
            if (operand1 + operand2 == target) {
                result->emplace_back(move(join(*expr)));
            }
            return;
        }
    
        int num = 0;
        string num_str;
        for (int i = pos; i < s.length(); ++i) {
            num = num * 10 + s[i] - '0';
            num_str.push_back(s[i]);
            // Avoid overflow and "00...".
            if (to_string(num) != num_str) {
                break;
            }

            // Case '+':
            expr->emplace_back("+"), expr->emplace_back(num_str);
            addOperatorsDFS(s, target, i + 1, operand1 + operand2, num, expr, result);
            expr->pop_back(), expr->pop_back();

            // '-' and '*' could be used only if the expression is not empty.
            if (!expr->empty()) {
                // Case '-':
                expr->emplace_back("-"), expr->emplace_back(num_str);
                addOperatorsDFS(s, target, i + 1, operand1 + operand2, -num, expr, result);
                expr->pop_back(), expr->pop_back();
        
                // Case '*':
                expr->emplace_back("*"), expr->emplace_back(num_str);
                addOperatorsDFS(s, target, i + 1, operand1, operand2 * num, expr, result);
                expr->pop_back(), expr->pop_back();
            }
        }
    }
    
    string join(const vector<string>& expr) {
        string e;
        for (int i = 0; i < expr.size(); ++i) {
            if (i == 0 && expr[i] == "+") {  // Skip '+' at the beginning of the string.
                continue;
            }
            e.append(expr[i]);
        }
        return e;
    }
};
