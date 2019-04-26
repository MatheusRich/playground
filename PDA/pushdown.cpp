#include <iostream>
#include <algorithm>

using namespace std;
int main() {
    string stack = "";
    while (1) {
        char c = getchar();

        if (c == '\n') {
            if (stack == "") {
                puts("Aceito");
            }
            else {
                puts("Rejeito");
            }
            stack = "";
            c = getchar();
            puts("");

            if (c == EOF) {
                break;
            }
        }

        if (stack == "") {
            stack = (char)toupper(c) + stack;
        }
        else {
            if ((char)toupper(c) == stack[0])
            {
                stack = (char)toupper(c) + stack;
            }
            else
            {
                stack.erase(0, 1);
            }
        }
        if (stack == "") {
            puts("nil");
        }
        else {
            puts(stack.c_str());
        }
    }
    return 0;
}
