SUMMERY
========

it has 4 classes wich use inheritance:
- `GENOME`
- `CELL`
- `ANIMAL` 
- `VIRUS`

PROJECT ALGORITHMS
========

<font color="blue">MANACHER for finding all pallindroms:

</font>
The algorithm works by using two arrays, P and C, where P[i] stores the length of the palindrome centered at index i, and C[i] stores the center of the palindrome for that index. The algorithm scans each character of the string and expands around it to check if it is part of a palindrome or not. If the palindrome can be extended, the values of P[i] and C[i] are updated accordingly. 
 
The Manacher algorithm runs in O(n) time and requires O(n) space, making it very efficient for finding palindromes in a given string.

example:
```
void cell::printAllPalindromeSubstr(string s) {
    int n = s.length();
    if (n == 0) return;
     // Preprocessing
    string t = "^#";
    for (int i = 0; i < n; i++) {
        t += s[i];
        t += "#";
    }
    t += "$";
    n = t.length();
     vector<int> P(n, 0);
    int center = 0, right = 0;
    for (int i = 1; i < n-1; i++) {
        int mirror = 2*center - i;
        if (right > i) P[i] = min(right-i, P[mirror]);
        while (t[i+(1+P[i])] == t[i-(1+P[i])]) P[i]++;
        if (i+P[i] > right) {
            center = i;
            right = i + P[i];
        }
    }
     // Print all palindromic substrings
    for (int i = 1; i < n-1; i++) {
        int len = P[i];
        if (P[i] > 0 && len %2==0 && len>2) {
            int start = (i - 1 - len) / 2;
            cout << s.substr(start, len) << endl;
        }
    }
}
```
<font color="blue">KMP for finding a special pattern in a string:

</font>

The Knuth–Morris–Pratt (KMP) algorithm is an efficient string matching algorithm that uses pattern preprocessing to reduce the number of character comparisons required during the search process. The algorithm preprocesses the pattern to determine how many characters to skip over in the text when a mismatch occurs during the search. 
 
To implement the KMP algorithm, we first preprocess the pattern and construct an array  lps  (longest proper prefix that is also a suffix) of the pattern string. The  lps  array is calculated using dynamic programming and is used to determine the number of characters to skip while searching the text.  
 
The KMP algorithm then performs a search from left to right in the text string with the help of the  lps  array. Whenever a character mismatch occurs, the algorithm skips over the characters that have already been matched by using the  lps  array.  
 
The KMP algorithm has a time complexity of O(n + m) where n is the length of the text and m is the length of the pattern. The space complexity of the algorithm is also O(m), where m is the length of the pattern.  
 
```
vector<int> kmp_preprocess(string pattern)
{
    int m = pattern.length();
    vector<int> lps(m);
    int j = 0;

    for (int i = 1; i < m;)
    {
        if (pattern[i] == pattern[j])
        {
            lps[i] = j + 1;
            i++;
            j++;
        }
        else
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

vector<int> kmp_search(string text, string pattern)
{
    vector<int> lps = kmp_preprocess(pattern);
    vector<int> indices;

    int n = text.length();
    int m = pattern.length();
    int i = 0;
    int j = 0;

    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }
        if (j == m)
        {
            indices.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < n && text[i] != pattern[j])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return indices;
}
```

<font color="blue"> longest common non-consecutive for definition of similarity:
</font>
```
double animal::similarity_percentage_2string(string X, string Y, int m, int n)
{
	// Initializing a matrix of size (m+1)*(n+1)
	double L[m + 1][n + 1];

	// Following steps build L[m+1][n+1] in bottom up
	// fashion. Note that L[i][j] contains length of LCS of
	// X[0..i-1] and Y[0..j-1]
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			if (i == 0 || j == 0)
				L[i][j] = 0;

			else if (X[i - 1] == Y[j - 1])
				L[i][j] = L[i - 1][j - 1] + 1;

			else
				L[i][j] = max(L[i - 1][j], L[i][j - 1]);
		}
	}

	// L[m][n] contains length of LCS for X[0..n-1]
	// and Y[0..m-1]
	return L[m][n]/max(m,n);
}
```
:)
