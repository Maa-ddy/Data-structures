
ull prime = 31;
ull mod = 1000004123;

//ull mod = 1000000009; // these are the usual used values, but sometimes they construct tests to make hashing with this mod fail
//ull mod = 1000000007; // better use the first mod, or other values > billion. check this url: http://compoasso.free.fr/primelistweb/page/prime/liste_online_en.php

void largest_prefix_equal_suffix() {
  string s; cin >> s;
  ull n = s.length();
  ull pref_hash[n]; pref_hash[0] = s[0] - 'a' + 1;
  ull pow = prime;
  ull pref_pow[n]; pref_pow[0] = 1;
  for (int left = 1; left < n; left++) {
    pref_hash[left] = pref_hash[left - 1] + ((s[left] - 'a' + 1) * pow) % mod;
    pref_hash[left] %= mod;

    pref_pow[left] = pow;
    pow = (pow * prime) % mod;
  }

  ull ans = -1;
  for (int k = 0; k < n; k++) {
    if (n - 1 - k < 0) break;
    if (n - 1 - k < 1) break;
    ull prev = (n - 1 - k - 1 < 0) ? 0 : pref_hash[n - 1 - k - 1];
    ull suf_hash = (((pref_hash[n - 1] - prev + mod) % mod) * modInverse(pref_pow[n - 1 - k], mod)) % mod;
    if (pref_hash[k] == suf_hash) ans = k;
  }

  if (ans == -1) {
    cout << "NO\n";
  } else {
    cout << "YES\n" << s.substr(0, ans + 1) << endl;
 }

}