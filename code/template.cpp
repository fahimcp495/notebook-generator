struct debug {
#define contPrint { *this << "["; \
        int f = 0; for(auto it : x) { *this << (f?", ":""); *this << it; f = 1;} \
        *this << "]"; return *this;}
 
    ~debug(){cerr << endl;}
    template<class c> debug& operator<<(c x) {cerr << x; return *this;}
    template<class c, class d>
    debug& operator<<(pair<c, d> x) {*this << "(" << x.first << ", " << x.second << ")"; 
        return *this;}
    template<class c> debug& operator<<(vector<c> x) contPrint;
#undef contPrint
};

#define dbg(x) "[" << #x << ": " << x << "]  "
#define Wa() cerr << "[LINE: " << __LINE__ << "] -> "; debug() << 


