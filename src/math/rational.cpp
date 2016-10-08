struct rational {
    long long p, q;

    void red() {
        if (q < 0) {
            p = -p;
            q = -q;
        }
        ll t = gcd((p >= 0 ? p : -p), q);
        p /= t;
        q /= t;
    }

    rational(): p(0), q(1) {}
    rational(long long p_): p(p_), q(1) {}
    rational(long long p_, long long q_): p(p_), q(q_) { red(); }

    bool operator==(const rational& rhs) const {
        return p == rhs.p && q == rhs.q;
    }
    bool operator!=(const rational& rhs) const {
        return p != rhs.p || q != rhs.q;
    }
    bool operator<(const rational& rhs) const {
        return p * rhs.q < rhs.p * q;
    }
    rational operator+(const rational& rhs) const {
        ll g = gcd(q, rhs.q);
        return rational(p * (rhs.q / g) + rhs.p * (q / g), (q / g) * rhs.q);
    }
    rational operator-(const rational& rhs) const {
        ll g = gcd(q, rhs.q);
        return rational(p * (rhs.q / g) - rhs.p * (q / g), (q / g) * rhs.q);
    }
    rational operator*(const rational& rhs) const {
        return rational(p * rhs.p, q * rhs.q);
    }
    rational operator/(const rational& rhs) const {
        return rational(p * rhs.q, q * rhs.p);
    }
};
