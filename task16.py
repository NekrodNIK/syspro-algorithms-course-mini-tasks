from dataclasses import dataclass


@dataclass
class OpDetails:
    left_associativity: bool
    priority: int


ops = {
    "**": OpDetails(False, 1),
    "*": OpDetails(True, 2),
    "/": OpDetails(True, 2),
    "%": OpDetails(True, 2),
    "+": OpDetails(True, 3),
    "-": OpDetails(True, 3),
    "<<": OpDetails(True, 4),
    ">>": OpDetails(True, 4),
    "<": OpDetails(True, 5),
    ">": OpDetails(True, 5),
    "<=": OpDetails(True, 5),
    ">=": OpDetails(True, 5),
    "==": OpDetails(True, 6),
    "!=": OpDetails(True, 6),
    "&": OpDetails(True, 7),
    "^": OpDetails(True, 8),
    "|": OpDetails(True, 9),
    "&&": OpDetails(True, 10),
    "||": OpDetails(True, 11),
}

ops_symbols = {s for i in ops.keys() for s in i}


def infix_to_rpn(infix: str):
    out = []
    stack = []

    i = 0
    while i < len(infix):
        if infix[i].isdigit():
            number = ""
            while i < len(infix) and infix[i].isdigit():
                number += infix[i]
                i += 1

            out.append(number)
            continue

        if infix[i] in ops_symbols:
            key = infix[i]
            if i + 1 < len(infix) and infix[i + 1] in ops_symbols:
                key += infix[i + 1]
                i += 1

            condition = lambda: (
                stack
                and stack[-1] != "("
                and (
                    ops[stack[-1]].priority < ops[key].priority
                    or (
                        ops[stack[-1]].priority == ops[key].priority
                        and ops[key].left_associativity
                    )
                )
            )

            while condition():
                out.append(stack.pop())
            stack.append(key)

            i += 1
            continue

        if infix[i] == "(":
            stack.append(infix[i])

        if infix[i] == ")":
            while stack and stack[-1] != "(":
                out.append(stack.pop())
            stack.pop()

        i += 1

    while stack:
        out.append(stack.pop())

    return " ".join(out)


if __name__ == "__main__":
    assert infix_to_rpn("3+4*2/(1-5)**2**3") == "3 4 2 * 1 5 - 2 3 ** ** / +"
    assert infix_to_rpn("(3 < 4) && (10 > 5)") == "3 4 < 10 5 > &&"
    assert infix_to_rpn("((((100 >> 2) << 3) < (9 && 10) + 1000) / 300) != 10") == "100 2 >> 3 << 9 10 && 1000 + < 300 / 10 !="
    print("All test passed!")
