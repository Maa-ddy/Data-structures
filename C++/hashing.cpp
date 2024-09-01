// prefix, suffix hashing

string s; cin >> s;
  ll n = s.length();
  ll pref_hash[n]; pref_hash[0] = s[0] - 'a' + 1;
  ll suf_hash[n]; suf_hash[n - 1] = s[n - 1] - 'a' + 1;
  ll pow = prime;
  for (int left = 1, right = n - 2; left < n; left++, right--) {
    pref_hash[left] = (pref_hash[left - 1] + s[left] - 'a' + 1) * pow;
    pref_hash[left] %= mod;

    suf_hash[right] = (suf_hash[right + 1] + s[right] - 'a' + 1 ) * pow;
    suf_hash[right] %= mod;
    
    pow = (pow * prime) % mod;
  }
