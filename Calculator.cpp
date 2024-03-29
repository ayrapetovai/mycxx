#include<memory>
#include<iostream>
#include<variant>

struct Expr;
struct Neg {
    std::shared_ptr<Expr> expr;
};
struct Add {
    std::shared_ptr<Expr> lhs, rhs;
};
struct Mul {
    std::shared_ptr<Expr> lhs, rhs;
};
struct Expr : std::variant<int, Neg, Add, Mul> {
    using variant::variant;
};
int eval(const Expr& expr) {
    struct visitor {
        int operator()(int i) const {
            return i;
        }
        int operator()(const Neg& n) const {
            return -eval(*n.expr);
        }
        int operator()(const Add& a) const {
            return eval(*a.lhs) + eval(*a.rhs);
        }
        int operator()(const Mul& m) const {
            // Optimize multiplication by 0.
            if (int* i = std::get_if<int>(m.lhs.get()); i && *i == 0) {
                return 0;
            }
            if (int* i = std::get_if<int>(m.rhs.get()); i && *i == 0) {
                return 0; }
            return eval(*m.lhs) * eval(*m.rhs);
        }
    };
    return std::visit(visitor{}, expr);
}
int main() {
    // 2 + 3
    auto expr = Expr{Add{std::make_shared<Expr>(2), std::make_shared<Expr>(3)}};
    auto res = eval(expr);
    std::cout << res << std::endl;
    // prints "5"
}