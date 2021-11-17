#include <iostream>
#include <vector>
#include <string>

std::vector<int> zFunction (std::string s) {
    int n = (int) s.length();
    std::vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r)
            z[i] = std::min (r - i + 1, z[i-l]);
        while (i + z[i] < n && s[z[i]] == s[i+z[i]])
            z[i]++;
        if (i + z[i] - 1 > r){
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    std::string s, t, forZ;
    std::vector<int> res;
    std::cin >> s >> t;
    if (s.length() != t.length())
        std::cout << "NO";
    else {
        forZ = s + "#" + t + t;
        res = zFunction( forZ );
        for (auto &i: res)
            std::cout << i << " ";
        for (auto &i: res)
            if (i == s.length()){
                std::cout << "YES";
                return 0;
            }
        std::cout << "NO";
    }

    return 0;
}