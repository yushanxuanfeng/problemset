#include<bits/stdc++.h>
using namespace std;
using psi = pair<string, int>;
using ull = unsigned long long;

const int maxN = 5e3 + 10;

map<string, psi> mp;

inline void throw_value_error() { throw "ValueError: Cannot declare variable."; }
inline void throw_symbol_error() { throw "SyntaxError: Symbols does not match."; }
inline void throw_overflow_error() { throw "ValueError: Signed integer overflow."; }
inline void throw_type_error() { throw "ValueError: Type does not match."; }
inline void throw_type_error_() { throw "TypeError: Type not supported."; }
inline void throw_name_error() { throw "NameError: Name has been used."; }
inline void throw_name_error_() { throw "NameError: Invalid variable name."; }

void delete_spaces(string& s) { while(s[0] == ' ') s = s.substr(1); while(s.back() == ' ') s.pop_back(); }

inline bool valid_char(char ch) { return isdigit(ch) || isalpha(ch) || ispunct(ch); }
inline bool valid_name(string s) { for(char i: s) if(!isalpha(i)) return false; return true; }
inline bool valid_type(string s) { return s == "int" || s == "long" || s == "char" || s == "comb" || s == "auto"; }

psi basic_type_parse(string s) {
    if(s.length() == 3 && s[0] == '"' && s[2] == '"') {
        if(!valid_char(s[1])) throw_type_error();
        return {"char", 0};
    }
    if(s[0] == '-') s = s.substr(1);
    ull res = 0;
    s = s.substr(1);
    for(char i: s) {
        if(!isdigit(i)) {
            throw_type_error();
        } else {
            ull tmp = res * 10 + (i - '0');
            if(tmp < res) throw_overflow_error();
            else res = tmp;
        }
    }
    if(res < INT_MAX) return {"int", 0};
    if(res < LONG_LONG_MAX) return {"long", 0};
    throw_overflow_error();
    return {"error", 0};
}

psi parse_type(string s) {
    if(mp.find(s) != mp.end()) return mp[s];
    if(s == "") throw_value_error();
    if(s[0] != '{' && s[s.length() - 1] != '}') return basic_type_parse(s);
    if(s[0] != '{' || s[s.length() - 1] != '}') throw_symbol_error();
    s.erase(0, 1), s[s.length() - 1] = ',';
    string now = ""; int _level = 0;
    psi Max = {"", -1};
    for(char i: s) {
        if(i == ' ') continue;
        if(i == '{') _level++; if(i == '}') _level--;
        if(i != ',' || _level) now += i;
        else {
            if(now == "") throw_symbol_error();
            psi tmp = mp.find(now) == mp.end() ? parse_type(now) : mp[now];
            if(tmp.second > Max.second) Max = tmp;
	        now = "";
        }
    }
    return {"comb", Max.second + 1};
}

inline void parse(string s) {
    int i = 0;
    while(s[i] == ' ') i++;
    string type = ""; for(; i < s.length() && s[i] != ' '; i++) type += s[i];
    string name = ""; for(; i < s.length() && s[i] != '='; i++) name += s[i];
    i++;
    string data = ""; for(; i < s.length(); i++) data += s[i];
    delete_spaces(type), delete_spaces(name), delete_spaces(data);
    if(!valid_type(type)) throw_type_error_();
    if(!valid_name(name)) throw_name_error_();
    if(mp.find(name) != mp.end()) throw_name_error();
    psi result = parse_type(data);
    if(type != "auto" && type != result.first) {
        if(type == "long" && result.first == "int") result.first = "long";
        else throw_type_error();
    }
    mp[name] = result;
}

int main() {
    int t; cin >> t;
    while(t-- > 0) {
        mp.clear();
        int n; cin >> n; getchar();
        try {
            vector<string> statements; string now = "";
            for(int i = 1; i <= n; i++) {
                char tmp = getchar(); if(tmp == '\n') tmp = ' ';
                if(tmp == ';') statements.push_back(now), now = "";
                else now += tmp;
                if(i == n && tmp != ';') throw_symbol_error();
            }
            if(now != "") statements.push_back(now);
            for(string i: statements) parse(i);
            for(auto i: mp) {
                cout << i.first << " " << i.second.first << " ";
                if(i.second.first == "comb") cout << i.second.second;
                cout << "\n";
            } 
        } catch(const char* msg) {
            cout << msg << "\n";
        }
    }
}