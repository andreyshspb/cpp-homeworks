#include <iosfwd>

// ================== INT ==================

class write_le_int32 {
public:
    explicit write_le_int32(int data) : data_(data) {};
    std::ostream &operator()(std::ostream &out) const;
private:
    int data_;
};

std::ostream &operator <<(std::ostream &out, write_le_int32 const &data);


class read_le_int32 {
public:
    explicit read_le_int32(int &data);
    std::istream &operator()(std::istream &in);
private:
    int *data_;
};

std::istream &operator >>(std::istream &in, read_le_int32 data);

// ================== BOOL ==================

class write_bool {
public:
    explicit write_bool(bool data) : data_(data) {};
    std::ostream &operator()(std::ostream &out) const;
private:
    bool data_;
};

std::ostream &operator <<(std::ostream &out, write_bool const &data);


class read_bool {
public:
    explicit read_bool(bool &data);
    std::istream &operator()(std::istream &in);
private:
    bool *data_;
};

std::istream &operator >>(std::istream &in, read_bool data);

// ================== C-STRING ==================

class write_c_str {
public:
    explicit write_c_str(char *data) : data_(data) {};
    std::ostream &operator()(std::ostream &out) const;
private:
    char *data_;
};

std::ostream &operator <<(std::ostream &out, write_c_str const &data);


class read_c_str {
public:
    explicit read_c_str(char *data) : data_(data) {};
    std::istream &operator()(std::istream &in);
private:
    char *data_;
};

std::istream &operator >>(std::istream &in, read_c_str data);
