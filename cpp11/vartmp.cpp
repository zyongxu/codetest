#include <iostream>
using namespace std;

template <typename... Values>
class tuple {
    /*
     * A template which will take ANY number (even zero!) of
     * typenames as its template parameters.
     *
     * the ellipsis operator (...): http://www.cplusplus.com/articles/EhvU7k9E/
     */
};

template <typename First, typename... Rest>
class tuple2 {
    /*
     * A template which will take AT LEAST one typename (for typename First)
     */
};

template <typename First = int, typename... Rest>
class tuple3 {
    /*
     * Since typename First has a default type, So tuple3 could 
     * have zero type arguments!
     */
};

template <typename... Params>
void printf (Params... agrus) {
}

int main() {
    return 0;
}
